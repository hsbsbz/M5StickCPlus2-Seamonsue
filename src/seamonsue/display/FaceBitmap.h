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
    this->_face0 = new hsbs::BitmapMono(Img::Mono::face0, Img::Mono::face0Width, Img::Mono::face0Height);
    this->_face0->y = 1;
    this->addChild(this->_face0);
    if (smile) {
      this->_face1 = new hsbs::BitmapMono(Img::Mono::face1, Img::Mono::face1Width, Img::Mono::face1Height);
    } else {
      this->_face1 = new hsbs::BitmapMono(Img::Mono::face2, Img::Mono::face2Width, Img::Mono::face2Height);
    }
    this->addChild(this->_face1);

    this->_face0->anchorX = Img::Mono::face0Width;
    this->_face0->anchorY = Img::Mono::face0Height;

    this->_face1->anchorX = Img::Mono::face1Width;
    this->_face1->anchorY = Img::Mono::face1Height;
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