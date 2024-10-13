#ifndef _SEAMONSUE__ACTIVITY__INFO__INFO_ACTIVITY2_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__INFO__INFO_ACTIVITY2_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../display/NikoNikoBitmap.h"
#include "../../display/PagerContainer.h"
#include "../../global.h"
#include "../SeamonsueActivity.h"

namespace seamonsue {

class InfoActivity2 : public SeamonsueActivity {
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

    int x1 = 6;
    int x2 = 20;
    int x3 = 28;

    int y1 = 3;
    int y2 = 16;

    this->_gameBitmap = new Img::Mono::InfoGameBitmap();
    this->_gameBitmap->setPosition(x1, y1);
    this->dotStage.addChild(this->_gameBitmap);

    this->_gameDotBitmap = new Img::Mono::InfoDotBitmap();
    this->_gameDotBitmap->setPosition(x2, y1 + 5);
    this->dotStage.addChild(this->_gameDotBitmap);

    this->_gameValueBitmap = new NikoNikoBitmap();
    this->_gameValueBitmap->setValue(std::ceil(petStore.getPleasanty()))->setPosition(x3, y1);
    this->dotStage.addChild(this->_gameValueBitmap);

    this->_cleanBitmap = new Img::Mono::InfoCleanBitmap();
    this->_cleanBitmap->setPosition(x1, y2);
    this->dotStage.addChild(this->_cleanBitmap);

    this->_cleanDotBitmap = new Img::Mono::InfoDotBitmap();
    this->_cleanDotBitmap->setPosition(x2, y2 + 5);
    this->dotStage.addChild(this->_cleanDotBitmap);

    this->_cleanValueBitmap = new NikoNikoBitmap();
    this->_cleanValueBitmap->setValue(std::ceil(petStore.getPretty()))->setPosition(x3, y2);
    this->dotStage.addChild(this->_cleanValueBitmap);
    
    this->_pager = new PagerContainer(3, 2);
    this->dotStage.addChild(this->_pager);
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->dotStage.removeChild(this->_gameBitmap);
    delete this->_gameBitmap;
    this->dotStage.removeChild(this->_gameDotBitmap);
    delete this->_gameDotBitmap;
    this->dotStage.removeChild(this->_gameValueBitmap);
    delete this->_gameValueBitmap;
    this->dotStage.removeChild(this->_cleanBitmap);
    delete this->_cleanBitmap;
    this->dotStage.removeChild(this->_cleanDotBitmap);
    delete this->_cleanDotBitmap;
    this->dotStage.removeChild(this->_cleanValueBitmap);
    delete this->_cleanValueBitmap;
    this->dotStage.removeChild(this->_pager);
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