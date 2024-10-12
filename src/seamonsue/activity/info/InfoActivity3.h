#ifndef _SEAMONSUE__ACTIVITY__INFO__INFO_ACTIVITY3_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__INFO__INFO_ACTIVITY3_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../display/NikoNikoBitmap.h"
#include "../../display/PagerContainer.h"
#include "../../global.h"
#include "hsbs/display/BitmapMono.h"
#include "../SeamonsueActivity.h"

namespace seamonsue {

class InfoActivity3 : public SeamonsueActivity {
private:
  //------------------------------
  // Private
  //------------------------------
  hsbs::BitmapMono *_label;
  hsbs::ObjectList<hsbs::BitmapMono *> _bitmapList;
  PagerContainer *_pager;

public:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {

    this->_label = new hsbs::BitmapMono(Img::Mono::info_fav, Img::Mono::info_favWidth, Img::Mono::info_favHeight);
    this->_label->setPosition(5, 4);
    this->dotStage.addChild(this->_label);

    this->_pager = new PagerContainer(3, 3);
    this->dotStage.addChild(this->_pager);

    MonsPersonalityData *personality = createPersonalityFromCount(petStore.getCountFood(), petStore.getCountGame(), petStore.getCountClean());


    Serial.println(
       ">" + String(personality->food) + " " + String(personality->game) + " " + String(personality->clean)
    );

    int space = 3;
    int x = 0;
    int y = 14;
    if (personality->food > 0) {
      hsbs::BitmapMono *foodBitmap = new hsbs::BitmapMono(Img::Mono::info_food, Img::Mono::info_foodWidth, Img::Mono::info_foodHeight);
      foodBitmap->setPosition(x, y);
      this->dotStage.addChild(foodBitmap);
      this->_bitmapList.add(foodBitmap);
      x += Img::Mono::info_foodWidth;
      x += space;
    }
    if (personality->game > 0) {
      hsbs::BitmapMono *gameBitmap = new hsbs::BitmapMono(Img::Mono::info_game, Img::Mono::info_gameWidth, Img::Mono::info_gameHeight);
      gameBitmap->setPosition(x, y);
      this->dotStage.addChild(gameBitmap);
      this->_bitmapList.add(gameBitmap);
      x += Img::Mono::info_gameWidth;
      x += space;
    }
    if (personality->clean > 0) {
      hsbs::BitmapMono *cleanBitmap = new hsbs::BitmapMono(Img::Mono::info_clean, Img::Mono::info_cleanWidth, Img::Mono::info_cleanHeight);
      cleanBitmap->setPosition(x, y);
      this->dotStage.addChild(cleanBitmap);
      this->_bitmapList.add(cleanBitmap);
      x += Img::Mono::info_cleanWidth;
      x += space;
    }
    x -= space;
    int length = this->_bitmapList.length();
    for (int i = 0; i < length; i++) {
      hsbs::BitmapMono *bitmap =  this->_bitmapList.getAt(i);
      bitmap->x += 21;
      bitmap->x -= (x >> 1);
    }

    delete personality;
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->dotStage.removeChild(this->_label);
    delete this->_label;
    this->dotStage.removeChild(this->_pager);
    delete this->_pager;
    while (this->_bitmapList.length()) {
      hsbs::BitmapMono *bitmap = this->_bitmapList.pop();
      this->dotStage.removeChild(bitmap);
      delete bitmap;
    }
  }

  /**
   * Aボタン押下
   */
  void onPressButtonA() override {
    if (this->isExact()) { // パスの完全一致
      soundUtil.pressButton();
      // 1ページ目へ
      this->go("/info/page1");
    }
  }

  /**
   * Bボタン押下
   */
  void onPressButtonB() override {
    if (this->isExact()) { // パスの完全一致
      soundUtil.pressButton();
      // 1ページ目へ
      this->go("/info/page1");
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