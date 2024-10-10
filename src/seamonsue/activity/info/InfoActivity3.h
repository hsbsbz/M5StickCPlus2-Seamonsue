#ifndef _SEAMONSUE__ACTIVITY__INFO__INFO_ACTIVITY3_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__INFO__INFO_ACTIVITY3_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../display/NikoNikoBitmap.h"
#include "../../display/PagerContainer.h"
#include "../../global.h"
#include "hsbs/app/M5StickCPlust2Activity.h"
#include "hsbs/display/BitmapMono.h"

namespace seamonsue {

class InfoActivity3 : public hsbs::M5StickCPlust2Activity {
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
    this->_label->setScale(4, 4);
    this->_label->setPosition(4 * 13, 4 * 4);
    this->stage.addChild(this->_label);

    this->_pager = new PagerContainer(3, 3);
    this->stage.addChild(this->_pager);

    MonsPersonalityData *personality = createPersonalityFromCount(petStore.getCountFood(), petStore.getCountGame(), petStore.getCountClean());


    Serial.println(
       ">" + String(personality->food) + " " + String(personality->game) + " " + String(personality->clean)
    );

    int space = 4 * 3;
    int x = 0;
    int y = 4 * 14;
    if (personality->food > 0) {
      hsbs::BitmapMono *foodBitmap = new hsbs::BitmapMono(Img::Mono::info_food, Img::Mono::info_foodWidth, Img::Mono::info_foodHeight);
      foodBitmap->setScale(4, 4);
      foodBitmap->setPosition(x, y);
      this->stage.addChild(foodBitmap);
      this->_bitmapList.add(foodBitmap);
      x += Img::Mono::info_foodWidth * 4;
      x += space;
    }
    if (personality->game > 0) {
      hsbs::BitmapMono *gameBitmap = new hsbs::BitmapMono(Img::Mono::info_game, Img::Mono::info_gameWidth, Img::Mono::info_gameHeight);
      gameBitmap->setScale(4, 4);
      gameBitmap->setPosition(x, y);
      this->stage.addChild(gameBitmap);
      this->_bitmapList.add(gameBitmap);
      x += Img::Mono::info_gameWidth * 4;
      x += space;
    }
    if (personality->clean > 0) {
      hsbs::BitmapMono *cleanBitmap = new hsbs::BitmapMono(Img::Mono::info_clean, Img::Mono::info_cleanWidth, Img::Mono::info_cleanHeight);
      cleanBitmap->setScale(4, 4);
      cleanBitmap->setPosition(x, y);
      this->stage.addChild(cleanBitmap);
      this->_bitmapList.add(cleanBitmap);
      x += Img::Mono::info_cleanWidth * 4;
      x += space;
    }
    x -= space;
    int length = this->_bitmapList.length();
    for (int i = 0; i < length; i++) {
      hsbs::BitmapMono *bitmap =  this->_bitmapList.getAt(i);
      bitmap->x += 120;
      bitmap->x -= (x >> 1);
    }

    delete personality;
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->stage.removeChild(this->_label);
    delete this->_label;
    this->stage.removeChild(this->_pager);
    delete this->_pager;
    while (this->_bitmapList.length()) {
      hsbs::BitmapMono *bitmap = this->_bitmapList.pop();
      this->stage.removeChild(bitmap);
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