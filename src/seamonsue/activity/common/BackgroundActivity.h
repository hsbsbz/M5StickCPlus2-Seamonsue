#ifndef _SEAMONSUE__ACTIVITY__COMMON__BACKGROUND_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__COMMON__BACKGROUND_ACTIVITY_H_INCLUDE_

#include "../../../image_progmem.h"
#include "hsbs/app/M5StickCPlust2Activity.h"
#include "hsbs/core/Ticker.h"
#include "hsbs/display/Bitmap565.h"

namespace seamonsue {

class BackgroundActivity : public hsbs::M5StickCPlust2Activity {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * 背景画像
   */
  hsbs::Bitmap565 *_bgBitmap;
  /**
   * バッテリーの矩形
   */
  hsbs::Canvas *_batteryCanvas;

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {
    // 背景画像を生成
    this->_bgBitmap = new hsbs::Bitmap565(Img::Rgb565::bg, Img::Rgb565::bgWidth, Img::Rgb565::bgHeight);
    this->stage.addChild(this->_bgBitmap);
    // バッテリー
    this->_batteryCanvas = new hsbs::Canvas(1, 1);
    this->_batteryCanvas->canvas.setColorDepth(1);
    this->_batteryCanvas->setPosition(213, 7)->setScale(0, 8);
    this->stage.addChild(this->_batteryCanvas);
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->stage.removeChild(this->_bgBitmap);
    delete this->_bgBitmap;
    this->stage.removeChild(this->_batteryCanvas);
    delete this->_batteryCanvas;
  }

  /**
   * フレーム更新時
   */
  void onEnterFrame() override {
    // 一定間隔でバッテリーの表示を更新
    if (globalTicker.checkInterval(3000)) {
      this->_batteryCanvas->scaleX = StickCP2.Power.getBatteryLevel() * 0.2;
    }
  }
};

} // namespace seamonsue

#endif