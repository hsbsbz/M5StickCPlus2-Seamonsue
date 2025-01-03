

#ifndef _SEAMONSUE__DISPLAY__CLOCK_CONTAINER_H_INCLUDE_
#define _SEAMONSUE__DISPLAY__CLOCK_CONTAINER_H_INCLUDE_

#include "../../image_progmem.h"
#include "../global.h"
#include "hsbs/core/ObjectList.h"
#include "hsbs/display/BitmapMono.h"
#include "hsbs/display/Canvas.h"
#include "hsbs/display/DisplayObjectContainer.h"
#include <Arduino.h>

namespace seamonsue {

class ClockContainer : public hsbs::DisplayObjectContainer {

private:
  void _draw(unsigned int hour,  unsigned int min) {

    // 白ベタ
    this->_canvas->canvas.fillScreen(TFT_WHITE);

    // 時
    if (hour >= 10) {
      // 二桁
      hsbs::BitmapMono *bmp0 = this->_numBitmapList.getAt((int)(hour / 10));
      bmp0->x = 0;
      bmp0->updateTransform(nullptr);
      bmp0->canvas.pushAffine(&this->_canvas->canvas, bmp0->transform.matrix, bmp0->transparentColor);
      hsbs::BitmapMono *bmp1 = this->_numBitmapList.getAt((int)(hour % 10));
      bmp1->x = 9;
      bmp1->updateTransform(nullptr);
      bmp1->canvas.pushAffine(&this->_canvas->canvas, bmp1->transform.matrix, bmp1->transparentColor);
    } else {
      // 一桁
      hsbs::BitmapMono *bmp0 = this->_numBitmapList.getAt((int)(hour));
      bmp0->x = 7;
      bmp0->updateTransform(nullptr);
      bmp0->canvas.pushAffine(&this->_canvas->canvas, bmp0->transform.matrix, bmp0->transparentColor);
    }

    // 秒
    hsbs::BitmapMono *bmp0 = this->_numBitmapList.getAt((int)(min / 10));
    bmp0->x = 24;
    bmp0->updateTransform(nullptr);
    bmp0->canvas.pushAffine(&this->_canvas->canvas, bmp0->transform.matrix, bmp0->transparentColor);
    hsbs::BitmapMono *bmp1 = this->_numBitmapList.getAt((int)(min % 10));
    bmp1->x = 34;
    bmp1->updateTransform(nullptr);
    bmp1->canvas.pushAffine(&this->_canvas->canvas, bmp1->transform.matrix, bmp1->transparentColor);

    // 仕切り
    int t = (int)(millis() / 250);
    if (!this->blinkFlg || (t % 4) > 0) {
      this->_canvas->canvas.setColor(0);
      this->_canvas->canvas.fillRect(19, 1, 2, 2);
      this->_canvas->canvas.fillRect(19, 6, 2, 2);
    }
  }

protected:
  //------------------------------
  // Protected
  //------------------------------
  hsbs::ObjectList<hsbs::BitmapMono *> _numBitmapList;
  hsbs::Canvas *_canvas;

public:
  //------------------------------
  // Public
  //------------------------------
  bool blinkFlg = true;

  /**
   * @brief コンストラクタ
   */
  ClockContainer() {
    // 数字のビットマップを生成
    this->_numBitmapList.add(new Img::Mono::ClockN0Bitmap());
    this->_numBitmapList.add(new Img::Mono::ClockN1Bitmap());
    this->_numBitmapList.add(new Img::Mono::ClockN2Bitmap());
    this->_numBitmapList.add(new Img::Mono::ClockN3Bitmap());
    this->_numBitmapList.add(new Img::Mono::ClockN4Bitmap());
    this->_numBitmapList.add(new Img::Mono::ClockN5Bitmap());
    this->_numBitmapList.add(new Img::Mono::ClockN6Bitmap());
    this->_numBitmapList.add(new Img::Mono::ClockN7Bitmap());
    this->_numBitmapList.add(new Img::Mono::ClockN8Bitmap());
    this->_numBitmapList.add(new Img::Mono::ClockN9Bitmap());

    // 一時キャンバスを生成
    this->_canvas = new hsbs::Canvas(43, 9);
    this->_canvas->transparentColor = TFT_WHITE;
    this->addChild(this->_canvas);
  }

  /**
   * @brief デストラクタ
   */
  virtual ~ClockContainer() {
    // 数字のビットマップを削除
    while (this->_numBitmapList.length()) {
      delete this->_numBitmapList.pop();
    }
    this->_numBitmapList.clear();
    // 一時キャンバスを削除
    this->removeChild(this->_canvas);
    delete this->_canvas;
  }

  /**
   * @brief
   */
  void update() {
    unsigned long totalSec = timeStore.getClockSec();
    unsigned int min = (totalSec / S_MINUTE) % 60; // 分
    unsigned int hour = (totalSec / S_HOUR) % 24;  // 時
    this->_draw(hour, min);
  }
};

} // namespace seamonsue

#endif