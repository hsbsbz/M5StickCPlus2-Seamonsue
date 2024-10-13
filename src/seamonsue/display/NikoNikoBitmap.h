
#ifndef _SEAMONSUE__DISPLAY__NIKO_NIKO_BITMAP_H_INCLUDE_
#define _SEAMONSUE__DISPLAY__NIKO_NIKO_BITMAP_H_INCLUDE_

#include "../../image_progmem.h"
#include "hsbs/display/Canvas.h"

namespace seamonsue {

class NikoNikoBitmap : public hsbs::DisplayObjectContainer {
private:
  //------------------------------
  // Private
  //------------------------------
  hsbs::BitmapMono *_bitmap0;
  hsbs::BitmapMono *_bitmap1;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * コンストラクタ
   */
  NikoNikoBitmap() {
    this->_bitmap0 = new Img::Mono::InfoFace0Bitmap();
    this->_bitmap1 = new Img::Mono::InfoFace3Bitmap();
    this->_bitmap0->y = 1;
    this->addChild(this->_bitmap0);
    this->addChild(this->_bitmap1);
  }

  virtual ~NikoNikoBitmap() {
    this->removeChild(this->_bitmap0);
    delete this->_bitmap0;
    this->removeChild(this->_bitmap1);
    delete this->_bitmap1;
  }

  /**
   * 表情を設定する 0 ~ 4
   * @param value
   * @return NikoNikoBitmap*
   */
  NikoNikoBitmap *setValue(int value) {

    value = value < 0 ? 0 : value;
    value = value > 4 ? 4 : value;

    this->removeChild(this->_bitmap1);
    delete this->_bitmap1;

    switch (value) {
    case 0: this->_bitmap1 = new Img::Mono::InfoFace1Bitmap(); break;
    case 1: this->_bitmap1 = new Img::Mono::InfoFace2Bitmap(); break;
    case 2: this->_bitmap1 = new Img::Mono::InfoFace3Bitmap(); break;
    case 3: this->_bitmap1 = new Img::Mono::InfoFace4Bitmap(); break;
    case 4: this->_bitmap1 = new Img::Mono::InfoFace5Bitmap(); break;
    default: this->_bitmap1 = new Img::Mono::InfoFace3Bitmap(); break;
    }
    this->addChild(this->_bitmap1);

    return this;
  }

  void update() {
    bool frame = ((millis() / 300) % 3) == 0;
    this->_bitmap0->visible = frame;
    this->_bitmap1->visible = !frame;
  }
};

} // namespace seamonsue

#endif