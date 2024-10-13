#ifndef _SEAMONSUE__ACTIVITY__MENU__MENU_CLEAN_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__MENU__MENU_CLEAN_ACTIVITY_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../global.h"
#include "hsbs/display/Bitmap565.h"
#include "../SeamonsueActivity.h"

namespace seamonsue {

class MenuCleanActivity : public SeamonsueActivity {
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
    this->_bitmap = new Img::Rgb565::IconCleanBitmap();
    this->_bitmap->setPosition(210, 91);
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
      this->go("/clean/page1");
    }
  }

  /**
   * Bボタン押下
   */
  void onPressButtonB() override {
    if (this->isExact()) { // パスの完全一致
      soundUtil.pressButton();
      this->go("/home");
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