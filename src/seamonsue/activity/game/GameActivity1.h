#ifndef _SEAMONSUE__ACTIVITY__GAME__GAME_ACTIVITY1_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__GAME__GAME_ACTIVITY1_H_INCLUDE_

#include "../../display/GameContainer.h"
#include "hsbs/core/Ticker.h"
#include "hsbs/display/BitmapMono.h"
#include "../SeamonsueActivity.h"

namespace seamonsue {

class GameActivity1 : public SeamonsueActivity {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * カウントダウン１画像
   */
  hsbs::BitmapMono *_countDownBitmap1;
  /**
   * カウントダウン２画像
   */
  hsbs::BitmapMono *_countDownBitmap2;
  /**
   * カウントダウン３画像
   */
  hsbs::BitmapMono *_countDownBitmap3;
  /**
   * ゲームコンテンツ
   */
  GameContainer *gameContainer;

  /**
   * カウントダウン中か
   *
   */
  bool _countdown = true;

  /**
   * ストアを更新したら false になるフラグ
   */
  bool _execFlg = true;

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {

    // フラグ
    this->_countdown = true;
    this->_execFlg = true;

    // ゲームコンテンツ
    this->gameContainer = new GameContainer();
    this->dotStage.addChild(this->gameContainer);

    // 1
    this->_countDownBitmap1 = new Img::Mono::GameN1Bitmap();
    this->_countDownBitmap1->visible = false;
    this->dotStage.addChild(this->_countDownBitmap1->setPosition(12, 5));

    // 2
    this->_countDownBitmap2 = new Img::Mono::GameN2Bitmap();
    this->_countDownBitmap2->visible = false;
    this->dotStage.addChild(this->_countDownBitmap2->setPosition(12, 5));

    // 3
    this->_countDownBitmap3 = new Img::Mono::GameN3Bitmap();
    this->_countDownBitmap3->visible = false;
    this->dotStage.addChild(this->_countDownBitmap3->setPosition(12, 5));

    // トランジション
    this->activeTransition.add(
        // やや待ち時間
        this->activeTransition.wait(400),
        // カウントダウン開始
        // 3
        this->activeTransition.callback([this]() {
          this->_countDownBitmap3->visible = true;
          soundUtil.gameContdown();
        }),
        // 2
        this->activeTransition.tween(100, hsbs::Ease::IN_SINE)->add(&this->_countDownBitmap3->y, 5, 7),
        this->activeTransition.tween(300, hsbs::Ease::OUT_SINE)->add(&this->_countDownBitmap3->y, 5, 4),
        this->activeTransition.callback([this]() {
          this->_countDownBitmap2->visible = true;
          this->_countDownBitmap3->visible = false;
          soundUtil.gameContdown();
        }),
        // 1
        this->activeTransition.tween(100, hsbs::Ease::IN_SINE)->add(&this->_countDownBitmap2->y, 5, 7),
        this->activeTransition.tween(300, hsbs::Ease::OUT_SINE)->add(&this->_countDownBitmap2->y, 7, 5),
        this->activeTransition.callback([this]() {
          this->_countDownBitmap1->visible = true;
          this->_countDownBitmap2->visible = false;
          soundUtil.gameContdown();
        }),
        // 0
        this->activeTransition.tween(100, hsbs::Ease::IN_SINE)->add(&this->_countDownBitmap1->y, 5, 7),
        this->activeTransition.tween(300, hsbs::Ease::OUT_SINE)->add(&this->_countDownBitmap1->y, 7, 5),
        this->activeTransition.callback([this]() {
          this->_countDownBitmap1->visible = false;
          this->_countdown = false;
          soundUtil.gameStart();
        }),
        // やや待ち時間
        this->activeTransition.wait(200));
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->activeTransition.clear();
    this->dotStage.removeChild(this->gameContainer);
    delete this->gameContainer;
    this->dotStage.removeChild(this->_countDownBitmap1);
    delete this->_countDownBitmap1;
    this->dotStage.removeChild(this->_countDownBitmap2);
    delete this->_countDownBitmap2;
    this->dotStage.removeChild(this->_countDownBitmap3);
    delete this->_countDownBitmap3;
  }

  /**
   * フレーム更新時
   */
  void onEnterFrame() override {
    this->resetSleepTimestamp(); // 自動スリープをリセット

    // カウントダウン中
    if (this->_countdown) {
      this->_countDownBitmap1->y = ((int)this->_countDownBitmap1->y >> 0); // ドットに吸着
      this->_countDownBitmap2->y = ((int)this->_countDownBitmap2->y >> 0); // ドットに吸着
      this->_countDownBitmap3->y = ((int)this->_countDownBitmap3->y >> 0); // ドットに吸着
      return;
    }

    // ゲーム中
    this->gameContainer->update();
    if (this->gameContainer->completed()) {
      // ゲーム終了
      if (this->_execFlg) {
        this->_execFlg = false; // （直後に遷移するけど、念のため多重コールされないようにフラグで防いでおく）
        // ストアを更新
        petStore.execGame();
      }
      // 遷移
      this->go("game/page2");
    }
  }

  /**
   * C ボタン押下
   */
  void onPressButtonC() override {
    this->go("/home");
  }
};

} // namespace seamonsue

#endif