#ifndef _SEAMONSUE__ACTIVITY__MENU__MENU_INFO_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__MENU__MENU_INFO_ACTIVITY_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../global.h"
#include "../SeamonsueActivity.h"

namespace seamonsue {

class MenuInfoActivity : public SeamonsueActivity {
private:
  //------------------------------
  // Private
  //------------------------------
  Img::Rgb565::IconInfoBitmap *_bitmap;

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {
    this->_bitmap = new Img::Rgb565::IconInfoBitmap();
    this->_bitmap->setPosition(3, 36);
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