#ifndef _SEAMONSUE__ACTIVITY__INFO__INFO_ACTIVITY1_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__INFO__INFO_ACTIVITY1_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../display/NikoNikoBitmap.h"
#include "../../display/PagerContainer.h"
#include "../../global.h"
#include "hsbs/display/BitmapMono.h"
#include "hsbs/display/Canvas.h"
#include "hsbs/tween/Ease.h"
#include "../SeamonsueActivity.h"

namespace seamonsue {

class InfoActivity1 : public SeamonsueActivity {
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

    int x1 = 6;
    int x2 = 20;
    int x3 = 28;

    int y1 = 3;
    int y2 = 16;

    this->_ageBitmap = new Img::Mono::InfoAgeBitmap();
    this->_ageBitmap->setPosition(x1 - 2, y1 + 3);
    this->dotStage.addChild(this->_ageBitmap);

    this->_ageDotBitmap = new Img::Mono::InfoDotBitmap();
    this->_ageDotBitmap->setPosition(x2, y1 + 5);
    this->dotStage.addChild(this->_ageDotBitmap);

    int age = timeStore.getTotalSec() / 86400; // 86400 は １日分の秒
    String ageStr = String(age);
    this->_ageCanvas = new hsbs::Canvas(12, 8);
    this->_ageCanvas->transparentColor = TFT_WHITE;
    this->_ageCanvas->canvas.fillScreen(TFT_WHITE);
    this->_ageCanvas->canvas.setTextColor(0);
    this->_ageCanvas->setPosition(x3 + 6, y1 + 2);
    this->_ageCanvas->canvas.print(ageStr);
    this->_ageCanvas->x -= (this->_ageCanvas->canvas.textWidth(ageStr) >> 1);
    this->dotStage.addChild(this->_ageCanvas);

    this->_foodBitmap = new Img::Mono::InfoFoodBitmap();
    this->_foodBitmap->setPosition(x1, y2);
    this->dotStage.addChild(this->_foodBitmap);

    this->_foodDotBitmap = new Img::Mono::InfoDotBitmap();
    this->_foodDotBitmap->setPosition(x2, y2 + 5);
    this->dotStage.addChild(this->_foodDotBitmap);

    this->_foodValueBitmap = new NikoNikoBitmap();
    this->_foodValueBitmap->setValue(std::ceil(petStore.getFullup()))->setPosition(x3, y2);
    this->dotStage.addChild(this->_foodValueBitmap);

    this->_pager = new PagerContainer(3, 1);
    this->dotStage.addChild(this->_pager);
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->dotStage.removeChild(this->_ageBitmap);
    delete this->_ageBitmap;
    this->dotStage.removeChild(this->_ageDotBitmap);
    delete this->_ageDotBitmap;
    this->dotStage.removeChild(this->_ageCanvas);
    delete this->_ageCanvas;
    this->dotStage.removeChild(this->_foodBitmap);
    delete this->_foodBitmap;
    this->dotStage.removeChild(this->_foodDotBitmap);
    delete this->_foodDotBitmap;
    this->dotStage.removeChild(this->_foodValueBitmap);
    delete this->_foodValueBitmap;
    this->dotStage.removeChild(this->_pager);
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