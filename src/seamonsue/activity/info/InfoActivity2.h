#ifndef _SEAMONSUE__ACTIVITY__INFO__INFO_ACTIVITY2_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__INFO__INFO_ACTIVITY2_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../display/NikoNikoBitmap.h"
#include "../../display/PagerContainer.h"
#include "../../global.h"
#include "hsbs/app/M5StickCPlust2Activity.h"

namespace seamonsue {

class InfoActivity2 : public hsbs::M5StickCPlust2Activity {
private:
  //------------------------------
  // Private
  //------------------------------
  hsbs::BitmapMono *_gameBitmap;
  hsbs::BitmapMono *_gameDotBitmap;
  NikoNikoBitmap *_gameValueBitmap;
  hsbs::BitmapMono *_cleanBitmap;
  hsbs::BitmapMono *_cleanDotBitmap;
  NikoNikoBitmap *_cleanValueBitmap;
  PagerContainer * _pager;

public:
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

    this->_gameBitmap = new hsbs::BitmapMono(Img::Mono::info_game, Img::Mono::info_gameWidth, Img::Mono::info_gameHeight);
    this->_gameBitmap->setPosition(x1, y1)->setScale(4, 4);
    this->stage.addChild(this->_gameBitmap);

    this->_gameDotBitmap = new hsbs::BitmapMono(Img::Mono::info_dot, Img::Mono::info_dotWidth, Img::Mono::info_dotHeight);
    this->_gameDotBitmap->setPosition(x2, y1 + (4 * 5))->setScale(4, 4);
    this->stage.addChild(this->_gameDotBitmap);

    this->_gameValueBitmap = new NikoNikoBitmap();
    this->_gameValueBitmap->setValue(std::ceil(petStore.getPleasanty()))->setPosition(x3, y1)->setScale(4, 4);
    this->stage.addChild(this->_gameValueBitmap);

    this->_cleanBitmap = new hsbs::BitmapMono(Img::Mono::info_clean, Img::Mono::info_cleanWidth, Img::Mono::info_cleanHeight);
    this->_cleanBitmap->setPosition(x1, y2)->setScale(4, 4);
    this->stage.addChild(this->_cleanBitmap);

    this->_cleanDotBitmap = new hsbs::BitmapMono(Img::Mono::info_dot, Img::Mono::info_dotWidth, Img::Mono::info_dotHeight);
    this->_cleanDotBitmap->setPosition(x2, y2 + (4 * 5))->setScale(4, 4);
    this->stage.addChild(this->_cleanDotBitmap);

    this->_cleanValueBitmap = new NikoNikoBitmap();
    this->_cleanValueBitmap->setValue(std::ceil(petStore.getPretty()))->setPosition(x3, y2)->setScale(4, 4);
    this->stage.addChild(this->_cleanValueBitmap);
    
    this->_pager = new PagerContainer(3, 2);
    this->stage.addChild(this->_pager);
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->stage.removeChild(this->_gameBitmap);
    delete this->_gameBitmap;
    this->stage.removeChild(this->_gameDotBitmap);
    delete this->_gameDotBitmap;
    this->stage.removeChild(this->_gameValueBitmap);
    delete this->_gameValueBitmap;
    this->stage.removeChild(this->_cleanBitmap);
    delete this->_cleanBitmap;
    this->stage.removeChild(this->_cleanDotBitmap);
    delete this->_cleanDotBitmap;
    this->stage.removeChild(this->_cleanValueBitmap);
    delete this->_cleanValueBitmap;
    this->stage.removeChild(this->_pager);
    delete this->_pager;
  }

  /**
   * フレーム更新時
   */
  void onEnterFrame() override {
    this->_gameValueBitmap->update();
    this->_cleanValueBitmap->update();
  }

  /**
   * Aボタン押下
   */
  void onPressButtonA() override {
    if (this->isExact()) { // パスの完全一致
      soundUtil.pressButton();
      // 1ページ目へ
      this->go("/info/page3");
    }
  }

  /**
   * Bボタン押下
   */
  void onPressButtonB() override {
    if (this->isExact()) { // パスの完全一致
      soundUtil.pressButton();
      // 1ページ目へ
      this->go("/info/page3");
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