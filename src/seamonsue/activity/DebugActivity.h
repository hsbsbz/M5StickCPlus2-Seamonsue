#ifndef _SEAMONSUE__ACTIVITY__DEBUG_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__DEBUG_ACTIVITY_H_INCLUDE_

#include "../../image_progmem.h"
#include "../global.h"
#include "esp_heap_caps.h"
#include "hsbs/core/Ticker.h"
#include "hsbs/display/Canvas.h"
#include "./SeamonsueActivity.h"


namespace seamonsue {

class DebugActivity : public SeamonsueActivity {
private:
  hsbs::Canvas *_canvas;

  /**
   * @brief 経過時間を確認用の文字列にする
   *
   * @param label
   * @param totalTime
   * @return String
   */
  String secToString(String label, long totalTime) {
    const int sec = (int)totalTime % S_MINUTE;
    const int minutes = (int)totalTime % S_HOUR / S_MINUTE;
    const int hours = (int)totalTime % S_DAY / S_HOUR;
    const int days = (int)totalTime / S_DAY;
    return label + ">" + String(days) + "D " + String(hours) + ":" + String(minutes) + ":" + String(sec);
  }

  String labelWith(String label, bool value) { return label + ">" + String(value); }
  String labelWith(String label, int value) { return label + ">" + String(value); }
  String labelWith(String label, float value) { return label + ">" + String(value); }
  String labelWith(String label, String value) { return label + ">" + value; }


public:
  DebugActivity() {
    // 描画用の Canvas
    this->_canvas = new hsbs::Canvas(240, 135);
    this->_canvas->transparentColor = 0;
    this->stage.addChild(this->_canvas);
  }

  void onInit() override {
  }

  void onEnterFrame() override {
    // if (globalTicker.checkInterval(400)) {
    int y = 8;
    this->_canvas->canvas.clear();

    // ほぼ空のプログラムだと 271 KB くらいだった
    this->_canvas->canvas.setCursor(6, y);
    this->_canvas->canvas.println("Mem> " + String(esp_get_free_heap_size()) + " B");
    y += 12;

    this->_canvas->canvas.setCursor(6, y);
    this->_canvas->canvas.println(this->secToString("tTotal", timeStore.getTotalSec()));
    y += 12;

    this->_canvas->canvas.setCursor(6, y);
    this->_canvas->canvas.println(this->secToString("tElapsed", timeStore.getElapsedSec()));
    y += 12;

    this->_canvas->canvas.setCursor(6, y);
    this->_canvas->canvas.println(this->labelWith("cFood", petStore.getCountFood()));
    y += 12;

    this->_canvas->canvas.setCursor(6, y);
    this->_canvas->canvas.println(this->labelWith("cGame", petStore.getCountGame()));
    y += 12;

    this->_canvas->canvas.setCursor(6, y);
    this->_canvas->canvas.println(this->labelWith("cClean", petStore.getCountClean()));
    y += 12;

    this->_canvas->canvas.setCursor(6, y);
    this->_canvas->canvas.println(this->labelWith("pFull", petStore.getFullup()));
    y += 12;

    this->_canvas->canvas.setCursor(6, y);
    this->_canvas->canvas.println(this->labelWith("pPleasanty", petStore.getPleasanty()));
    y += 12;

    this->_canvas->canvas.setCursor(6, y);
    this->_canvas->canvas.println(this->labelWith("pPretty", petStore.getPretty()));
    y += 12;

    this->_canvas->canvas.setCursor(6, y);
    MonsPersonalityData *data = createPersonalityFromCount(petStore.getCountFood(), petStore.getCountGame(), petStore.getCountClean());
    this->_canvas->canvas.println(this->labelWith("evo", getMonsIdFromPersonality(data)));
    delete data;

    y += 12;
  }
  // }
};

} // namespace seamonsue

#endif