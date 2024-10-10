#ifndef _SEAMONSUE__ACTIVITY__INFO__INFO_ACTIVITY1_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__INFO__INFO_ACTIVITY1_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../display/NikoNikoBitmap.h"
#include "../../display/PagerContainer.h"
#include "../../global.h"
#include "hsbs/app/M5StickCPlust2Activity.h"
#include "hsbs/display/BitmapMono.h"
#include "hsbs/display/Canvas.h"
#include "hsbs/tween/Ease.h"

namespace seamonsue {

class InfoActivity1 : public hsbs::M5StickCPlust2Activity {
private:
  //------------------------------
  // Private
  //------------------------------
  hsbs::Canvas *_ageCanvas;
  hsbs::BitmapMono *_ageBitmap;
  hsbs::BitmapMono *_ageDotBitmap;
  hsbs::BitmapMono *_foodBitmap;
  hsbs::BitmapMono *_foodDotBitmap;
  NikoNikoBitmap *_foodValueBitmap;
  PagerContainer * _pager;

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {

    int x1 = 34 + (4 * 6);
    int x2 = 34 + (4 * 20);
    int x3 = 34 + (4 * 28);

    int y1 = (4 * 3);
    int y2 = (4 * 16);

    this->_ageBitmap = new hsbs::BitmapMono(Img::Mono::info_age, Img::Mono::info_ageWidth, Img::Mono::info_ageHeight);
    this->_ageBitmap->setPosition(x1 - (4 * 2), y1 + (4 * 3))->setScale(4, 4);
    this->stage.addChild(this->_ageBitmap);

    this->_ageDotBitmap = new hsbs::BitmapMono(Img::Mono::info_dot, Img::Mono::info_dotWidth, Img::Mono::info_dotHeight);
    this->_ageDotBitmap->setPosition(x2, y1 + (4 * 5))->setScale(4, 4);
    this->stage.addChild(this->_ageDotBitmap);

    int age = timeStore.getTotalSec() / 86400; // 86400 は １日分の秒
    String ageStr = String(age);
    this->_ageCanvas = new hsbs::Canvas(12, 8);
    this->_ageCanvas->transparentColor = TFT_WHITE;
    this->_ageCanvas->canvas.fillScreen(TFT_WHITE);
    this->_ageCanvas->canvas.setTextColor(0);
    this->_ageCanvas->setPosition(x3 + (4 * 6), y1 + (4 * 2))->setScale(4, 4);
    this->_ageCanvas->canvas.print(ageStr);
    this->_ageCanvas->x -= ((this->_ageCanvas->canvas.textWidth(ageStr) * 4) >> 1);
    this->stage.addChild(this->_ageCanvas);

    this->_foodBitmap = new hsbs::BitmapMono(Img::Mono::info_food, Img::Mono::info_foodWidth, Img::Mono::info_foodHeight);
    this->_foodBitmap->setPosition(x1, y2)->setScale(4, 4);
    this->stage.addChild(this->_foodBitmap);

    this->_foodDotBitmap = new hsbs::BitmapMono(Img::Mono::info_dot, Img::Mono::info_dotWidth, Img::Mono::info_dotHeight);
    this->_foodDotBitmap->setPosition(x2, y2 + (4 * 5))->setScale(4, 4);
    this->stage.addChild(this->_foodDotBitmap);

    this->_foodValueBitmap = new NikoNikoBitmap();
    this->_foodValueBitmap->setValue(std::ceil(petStore.getFullup()))->setPosition(x3, y2)->setScale(4, 4);
    this->stage.addChild(this->_foodValueBitmap);

    this->_pager = new PagerContainer(3, 1);
    this->stage.addChild(this->_pager);
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->stage.removeChild(this->_ageBitmap);
    delete this->_ageBitmap;
    this->stage.removeChild(this->_ageDotBitmap);
    delete this->_ageDotBitmap;
    this->stage.removeChild(this->_ageCanvas);
    delete this->_ageCanvas;
    this->stage.removeChild(this->_foodBitmap);
    delete this->_foodBitmap;
    this->stage.removeChild(this->_foodDotBitmap);
    delete this->_foodDotBitmap;
    this->stage.removeChild(this->_foodValueBitmap);
    delete this->_foodValueBitmap;
    this->stage.removeChild(this->_pager);
    delete this->_pager;
  }

  /**
   * フレーム更新時
   */
  void onEnterFrame() override {
    this->_foodValueBitmap->update();
  }

  /**
   * Aボタン押下
   */
  void onPressButtonA() override {
    if (this->isExact()) { // パスの完全一致
      soundUtil.pressButton();
      // 2ページ目へ
      this->go("/info/page2");
    }
  }

  /**
   * Bボタン押下
   */
  void onPressButtonB() override {
    if (this->isExact()) { // パスの完全一致
      soundUtil.pressButton();
      // 2ページ目へ
      this->go("/info/page2");
    }
  }

  /**
   * Cボタン押下
   */
  void onPressButtonC() override {
    if (this->isExact()) { // パスの完全一致
      soundUtil.pressButton();
      // ホームへ
      this->go("/home");
    }
  }
};

} // namespace seamonsue

#endif