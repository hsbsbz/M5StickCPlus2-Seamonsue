#ifndef _SEAMONSUE__ACTIVITY__CLOCK__CLOCK_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__CLOCK__CLOCK_ACTIVITY_H_INCLUDE_

#include "../../display/ClockContainer.h"
#include "../../display/MonsBitmap.h"
#include "../../global.h"
#include "hsbs/app/M5StickCPlust2Activity.h"
#include "hsbs/display/BitmapMono.h"
#include <M5StickCPlus2.h>

namespace seamonsue {

/**
 * @brief 時計画面でもミュートボタンの切り替えができるように Press ではなく Release で操作しる。、
 * 
 */
class ClockActivity : public hsbs::M5StickCPlust2Activity {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * @brief デジタル時計の表示オブジェクトコンテナ
   *
   */
  ClockContainer *_clockContainer;

  /**
   * @brief モンス画像
   */
  MonsBitmap *_monsBitmap;

  /**
   * @brief ミュートの状態をバックアップしておく変数
   */
  bool _bkMuted;

  /**
   * @brief Aボタンを押下しているかを保持
   */
  bool _pressedA = false;

  /**
   * @brief Bボタンを押下しているかを保持
   */
  bool _pressedB = false;

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {

    this->_pressedA = false;
    this->_pressedB = false;

    // モンス画像
    this->_monsBitmap = new MonsBitmap();
    this->_monsBitmap->setPosition(119, 135)->setScale(4, 4);
    this->stage.addChild(this->_monsBitmap);
    this->_monsBitmap->update();

    // デジタル時計
    this->_clockContainer = new ClockContainer();
    this->_clockContainer->setPosition(0, 12);
    this->stage.addChild(this->_clockContainer);

    // トランジション
    if (!gameStore.getClockMode()) {
      // ホームから遷移した場合は、スクロールアニメーション
      gameStore.toggleClockMode();
      this->activeTransition.add(this->activeTransition.tween(300, hsbs::Ease::OUT_SINE)->add(&this->_clockContainer->y, 12 - 48, 12));
    }
    this->deactiveTransition.add(
        this->deactiveTransition.callback([this] {
          // 時計の画面を表示していることをストアに記録（スリープから復帰したら時計を直接表示するため）
          if (gameStore.getClockMode()) {
            gameStore.toggleClockMode();
          }
        }),
        this->deactiveTransition.tween(300, hsbs::Ease::IN_SINE)->add(&this->_clockContainer->y, 12, 12 - 48));
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->activeTransition.clear();
    this->deactiveTransition.clear();
    this->stage.removeChild(this->_monsBitmap);
    delete this->_monsBitmap;
    this->stage.removeChild(this->_clockContainer);
    delete this->_clockContainer;
  }

  /**
   * フレーム更新時
   */
  void onEnterFrame() override {
    // 時計の表示を更新
    this->_clockContainer->update();
    // モンスの表示を更新
    this->_monsBitmap->update();

    // 時計とモンスがかぶる場合は、モンスを下にずらす
    int clockBottom = this->_clockContainer->y + 46;
    int monsY = 135 - ((this->_monsBitmap->monsH - this->_monsBitmap->monsY) << 2);
    int delta = clockBottom - monsY;
    delta = delta < 0 ? 0 : delta;
    this->_monsBitmap->y = 135 + delta;

    // ピクセル吸着
    this->_clockContainer->y = ((int)this->_clockContainer->y >> 2) << 2;
    this->_monsBitmap->y = ((int)this->_monsBitmap->y >> 2) << 2;

    // 編集中に非表示
    bool exact = this->isExact() || (this->deactiveTransition.getState() == hsbs::TweenState::RUNNING);
    this->_clockContainer->blinkFlg = exact;
    this->_monsBitmap->visible = exact;
  }


  void onPressButtonA() override {
    this->_bkMuted = gameStore.getMuted(); // ミュートの状態を保持（長押しのミュート切り替え時に処理のバッティングを防ぐため）
    this->_pressedA = true;
    // AB同時押しで編集開始
    if (this->isExact()) {
      if (this->_pressedA && this->_pressedB) {
        this->goToEdit();
      }
    }
  }

  void onReleaseButtonA() override {
    this->_pressedA = false;
    if (this->isExact()) {
      this->goToHome();
    }
  }

  void onPressButtonB() override {
    this->_pressedB = true;
    // AB同時押しで編集開始
    if (this->isExact()) {
      if (this->_pressedA && this->_pressedB) {
        this->goToEdit();
      }
    }
  }

  void onReleaseButtonB() override {
    this->_pressedB = false;
    if (this->isExact()) {
      this->goToHome();
    }
  }

  /**
   * @brief 時刻の修正を開始
   */
  void goToEdit() {
    soundUtil.startClockEdit();
    this->go("/clock/edit");
  }

  /**
   * @brief ホームに遷移
   */
  void goToHome() {
    if (this->_bkMuted != gameStore.getMuted()) return;// 長押しでミュートの切り替えがあったら遷移しない
    soundUtil.pressButton();
    this->go("/home");
  }
};

} // namespace seamonsue

#endif