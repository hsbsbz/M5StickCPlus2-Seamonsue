
#ifndef _SEAMONSUE__DISPLAY__BROOM_BITMAP_H_INCLUDE_
#define _SEAMONSUE__DISPLAY__BROOM_BITMAP_H_INCLUDE_

#include "../../image_progmem.h"
#include "../global.h"
#include "hsbs/display/BitmapMono.h"
#include "hsbs/display/DisplayObjectContainer.h"

namespace seamonsue {

class BroomBitmap : public hsbs::DisplayObjectContainer {

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * コマアニメ１フレーム
   */
  Img::Mono::Clean0Bitmap *_bitmap0;
  /**
   * コマアニメ２フレーム
   */
  Img::Mono::Clean1Bitmap *_bitmap1;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * コンストラクタ
   */
  BroomBitmap() {
    this->_bitmap0 = new Img::Mono::Clean0Bitmap();
    this->_bitmap0->clipRect = &dotAreaRect;
    this->_bitmap0->setPosition(-6, 5);
    this->addChild(this->_bitmap0);
    this->_bitmap1 = new  Img::Mono::Clean1Bitmap();
    this->_bitmap1->clipRect = &dotAreaRect;
    this->addChild(this->_bitmap1);
  }

  /**
   * フレームを更新する
   */
  void update() {
    bool flg = (bool)((millis() / 400) % 2);
    this->_bitmap0->visible = flg;
    this->_bitmap1->visible = !flg;
  }

  /**
   * デストラクタ
   */
  virtual ~BroomBitmap() {
    this->removeChild(this->_bitmap0);
    delete this->_bitmap0;
    this->removeChild(this->_bitmap1);
    delete this->_bitmap1;
  }
};

} // namespace seamonsue

#endif