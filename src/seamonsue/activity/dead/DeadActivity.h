

#ifndef _SEAMONSUE__ACTIVITY__DEAD__DEAD_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__DEAD__DEAD_ACTIVITY_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../global.h"
#include "hsbs/display/BitmapMono.h"
#include "../SeamonsueActivity.h"

namespace seamonsue {

class DeadActivity : public SeamonsueActivity {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * 墓画像
   */
  hsbs::BitmapMono *_bitmap;

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {
    this->_bitmap = new Img::Mono::RipBitmap();
    this->_bitmap->setPosition(21 - (Img::Mono::ripWidth >> 1), 8);
    this->dotStage.addChild(this->_bitmap);
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->dotStage.removeChild(this->_bitmap);
    delete this->_bitmap;
  }

  /**
   * Aボタンをリリース
   */
  void onReleaseButtonA() override {
    // ゲームをリセットしてタイトルへ
    soundUtil.pressButton();
    this->go("/reset");
  }

  /**
   * Bボタンをリリース
   */
  void onReleaseButtonB() override {
    // ゲームをリセットしてタイトルへ
    soundUtil.pressButton();
    this->go("/reset");
  }
};

} // namespace seamonsue

#endif