#ifndef _SEAMONSUE__ACTIVITY__MENU__MENU_GAME_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__MENU__MENU_GAME_ACTIVITY_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../global.h"
#include "hsbs/app/M5StickCPlust2Activity.h"
#include "hsbs/display/Bitmap565.h"

namespace seamonsue {

class MenuGameActivity : public hsbs::M5StickCPlust2Activity {
private:
  //------------------------------
  // Private
  //------------------------------
  hsbs::Bitmap565 *_bitmap;


protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {
    this->_bitmap = new hsbs::Bitmap565(Img::Rgb565::icon_game, Img::Rgb565::icon_gameWidth, Img::Rgb565::icon_gameHeight);
    this->_bitmap->setPosition(210, 41);
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
   * Aボタン押下
   */
  void onPressButtonA() override {
    if (this->isExact()) {// パスの完全一致
      soundUtil.pressButton();
      this->go("/game/page1");
    }
  }

  /**
   * Bボタン押下
   */
  void onPressButtonB() override {
    if (this->isExact()) {// パスの完全一致
      soundUtil.pressButton();
      this->go("/home/clean");
    }
  }

  /**
   * Cボタン押下
   */
  void onPressButtonC() override {
    if (this->isExact()) {// パスの完全一致
      soundUtil.pressButton();
      this->go("/home");
    }
  }
};

} // namespace seamonsue

#endif