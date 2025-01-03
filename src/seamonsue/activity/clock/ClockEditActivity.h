#ifndef _SEAMONSUE__ACTIVITY__CLOCK__CLOCK_EDIT_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__CLOCK__CLOCK_EDIT_ACTIVITY_H_INCLUDE_

#include "../SeamonsueActivity.h"
#include "hsbs/display/BitmapMono.h"
#include <M5StickCPlus2.h>

namespace seamonsue {

class ClockEditActivity : public SeamonsueActivity {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * @brief 編集中のテキスト画像
   */
  hsbs::BitmapMono *_textBitmap;

  /**
   * @brief Aボタンを押下しているかを保持
   */
  bool _pressedA = false;

  /**
   * @brief Bボタンを押下しているかを保持
   */
  bool _pressedB = false;

  /**
   * @brief Cボタンを押下しているかを保持
   */
  bool _pressedC = false;

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {
    // 押下状態を false に設定
    this->_pressedA = false;
    this->_pressedB = false;
    this->_pressedC = false;
    // 編集中画像
    this->_textBitmap = new Img::Mono::ClockEditBitmap();
    this->_textBitmap->setPosition(9, 17);
    this->_textBitmap->visible = false;
    this->dotStage.addChild(this->_textBitmap);
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->dotStage.removeChild(this->_textBitmap);
    delete this->_textBitmap;
  }

  /**
   * フレーム更新時
   */
  void onEnterFrame() override {
    // スリープ禁止
    this->resetSleepTimestamp();

    // 加速度センサを更新
    StickCP2.Imu.update();
    auto data = StickCP2.Imu.getImuData();
    float accel = data.accel.y;
    float absAccel = std::abs(accel);
    float direction = accel > 0 ? 1 : -1;

    // ３段階のスピード変更
    if (absAccel > 0.6) {
      timeStore.appendClockSec(direction * S_MINUTE * 10);
    } else if (absAccel > 0.4) {
      timeStore.appendClockSec(direction * S_MINUTE * 0.5);
    } else if (absAccel > 0.2) {
      timeStore.appendClockSec(direction * S_MINUTE * 0.1);
    }

    // 編集中のテキストを点滅させる
    int t = (int)(millis() / 250);
    this->_textBitmap->visible = ((t % 4) > 0);
  }

  void onPressButtonA() override { this->_pressedA = true; }
  void onPressButtonB() override { this->_pressedB = true; }
  void onPressButtonC() override { this->_pressedC = true; }

  void onReleaseButtonA() override {
    if (!this->_pressedA) return;
    this->_pressedA = false;
    this->endEdit();
  }

  void onReleaseButtonB() override {
    if (!this->_pressedB) return;
    this->_pressedB = false;
    this->endEdit();
  }

  void onReleaseButtonC() override {
    if (!this->_pressedC) return;
    this->_pressedC = false;
    this->endEdit();
  }

  /**
   * @brief 編集を終了する
   */
  void endEdit() {
    soundUtil.endClockEdit();
    this->go("/clock");
  }
};

} // namespace seamonsue

#endif