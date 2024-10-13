#ifndef _SEAMONSUE__ACTIVITY__TITLE__TITLE_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__TITLE__TITLE_ACTIVITY_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../global.h"
#include "hsbs/display/BitmapMono.h"
#include "hsbs/tween/Ease.h"
#include "../SeamonsueActivity.h"

namespace seamonsue {

class TitleActivity : public SeamonsueActivity {
private:
  /**
   * タイトル画像
   */
  hsbs::BitmapMono *_bitmap;

  /**
   * ゲームを開始する
   */
  void _enter() {
    soundUtil.pressButton();
    gameStore.startGame(); // ゲームを開始
    petStore.clear();      // ペットのセーブデータを削除
    timeStore.clearExceptClock();     // タイマーのセーブデータを削除
    this->go("/home");     // 遷移
  }

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {
    // タイトル画像
    this->_bitmap = new Img::Mono::TitleBitmap();
    this->_bitmap->setPosition(120, -56)->setScale(2, 2)->setAnchor(Img::Mono::titleWidth >> 1, Img::Mono::titleHeight >> 1);
    this->stage.addChild(this->_bitmap);

    // トランジションの設定
    this->activeTransition.add(
        // 音を鳴らす
        this->activeTransition.callback([this]() { soundUtil.title(); }),
        // 上からアニメーション
        this->activeTransition.tween(2000, hsbs::Ease::LINEAR)->add(&this->_bitmap->y, -56, 64));
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->activeTransition.clear();
    this->stage.removeChild(this->_bitmap);
    delete this->_bitmap;
  }

  /**
   * フレーム更新時
   */
  void onEnterFrame() override {
    // 2px で吸着
    this->_bitmap->y = ((int)this->_bitmap->y >> 1) << 1;
  }

  /**
   * Aボタンをリリース
   */
  void onReleaseButtonA() override {
    this->_enter();
  }

  /**
   * Bボタンをリリース
   */
  void onReleaseButtonB() override {
    this->_enter();
  }

  /**
   * Cボタンをリリース
   */
  void onReleaseButtonC() override {
    this->_enter();
  }
};

} // namespace seamonsue

#endif