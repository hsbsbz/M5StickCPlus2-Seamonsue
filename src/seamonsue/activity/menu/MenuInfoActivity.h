#ifndef _SEAMONSUE__ACTIVITY__MENU__MENU_INFO_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__MENU__MENU_INFO_ACTIVITY_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../global.h"
#include "hsbs/app/M5StickCPlust2Activity.h"
#include "hsbs/display/Bitmap565.h"

namespace seamonsue {

class MenuInfoActivity : public hsbs::M5StickCPlust2Activity {
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
    this->_bitmap = new hsbs::Bitmap565(Img::Rgb565::icon_info, Img::Rgb565::icon_infoWidth, Img::Rgb565::icon_infoHeight);
    this->_bitmap->setPosition(4, 26);
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
    if (this->isExact()) { // パスの完全一致
      soundUtil.pressButton();
      this->go("/info/page1");
    }
  }

  /**
   * Bボタン押下
   */
  void onPressButtonB() override {
    if (this->isExact()) { // パスの完全一致
      soundUtil.pressButton();
      this->go("/home/food");
    }
  }

  /**
   * Cボタン押下
   */
  void onPressButtonC() override {
    if (this->isExact()) { // パスの完全一致
      soundUtil.pressButton();
      this->go("/home");
    }
  }
};

} // namespace seamonsue

#endif