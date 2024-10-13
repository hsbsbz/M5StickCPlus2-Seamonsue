#ifndef _SEAMONSUE__DISPLAY__FACE_BITMAP_H_INCLUDE_
#define _SEAMONSUE__DISPLAY__FACE_BITMAP_H_INCLUDE_

#include "../../image_progmem.h"
#include "../global.h"
#include "hsbs/display/BitmapMono.h"
#include "hsbs/display/DisplayObjectContainer.h"

namespace seamonsue {

class FaceBitmap : public hsbs::DisplayObjectContainer {

private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * 顔アイコン画像フレーム１
   */
  hsbs::BitmapMono *_face0;
  /**
   * 顔アイコン画像フレーム２
   */
  hsbs::BitmapMono *_face1;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * コンストラクタ
   *
   * @param smile
   */
  FaceBitmap(bool smile = true) {
    this->_face0 = new Img::Mono::Face0Bitmap();
    this->_face0->y = 1;
    this->addChild(this->_face0);
    if (smile) {
      this->_face1 = new Img::Mono::Face1Bitmap();
    } else {
      this->_face1 = new Img::Mono::Face2Bitmap();
    }
    this->addChild(this->_face1);

    this->_face0->anchorX = this->_face0->width;
    this->_face0->anchorY = this->_face0->height;

    this->_face1->anchorX = this->_face1->width;
    this->_face1->anchorY = this->_face1->height;
  }

  /**
   * フレームの更新
   */
  void update() {
    int t = (int)(millis() / 500);
    bool frame = (t % 2) == 0;
    this->_face0->visible = frame;
    this->_face1->visible = !frame;
  }

  /**
   * デストラクタ
   */
  virtual ~FaceBitmap() {
    this->removeChild(this->_face0);
    delete this->_face0;
    this->removeChild(this->_face1);
    delete this->_face1;
  }
};

} // namespace seamonsue

#endif