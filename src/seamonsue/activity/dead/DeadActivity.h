

#ifndef _SEAMONSUE__ACTIVITY__DEAD__DEAD_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__DEAD__DEAD_ACTIVITY_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../global.h"
#include "hsbs/app/M5StickCPlust2Activity.h"
#include "hsbs/display/BitmapMono.h"

namespace seamonsue {

class DeadActivity : public hsbs::M5StickCPlust2Activity {
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
    this->_bitmap = new hsbs::BitmapMono(Img::Mono::rip, Img::Mono::ripWidth, Img::Mono::ripHeight);
    this->_bitmap->setPosition(120 - (Img::Mono::ripWidth >> 1) * 4, 8 * 4)->setScale(4, 4);
    this->stage.addChild(this->_bitmap);
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->stage.removeChild(this->_bitmap);
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