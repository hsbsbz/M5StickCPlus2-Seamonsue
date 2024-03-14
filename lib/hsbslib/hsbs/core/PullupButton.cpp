

#include "PullupButton.h"

namespace hsbs {

// チャタリング回避用のカウンタ。（２フレーム）
#define BUTTON_PRESS_MAX_COUNT 2

uint8_t PullupButton::getPin() { return this->_pin; }

bool PullupButton::pressed() { return this->_pressed; }

bool PullupButton::changed() { return this->_changed; }

bool PullupButton::longPressed() { return this->_longPressed; }

bool PullupButton::changedLongPress() { return this->_changedLongPress; }

void PullupButton::setup(uint8_t pin, unsigned int longPressDuration) {
  this->_pin = pin;
  this->_longPressDuration = longPressDuration;
  this->_releaseTimestamp = millis();
  pinMode(this->_pin, PULLUP);
}

void PullupButton::update() {
  // 変更があったフラグを折る
  this->_changed = false;
  this->_changedLongPress = false;

  // 値を取得
  bool value = !digitalRead(this->_pin);

  // 状態を更新
  if (value) {                                                 // 押下時
    if (this->_count < BUTTON_PRESS_MAX_COUNT) ++this->_count; // カウントアップ
  } else {                                                     // リリース時
    if (this->_count > 0) --this->_count;                      // カウントダウン
  }
  bool pressed = this->_count == BUTTON_PRESS_MAX_COUNT; // 一定時間の押下判定
  if (this->_pressed != pressed) {
    this->_pressed = pressed; // 状態を変更
    this->_changed = true;    // 押下判定に変更があった
  }
  if (this->_changed) {
    // 押下判定に変更があった場合に
    if (this->_pressed) {
      this->_pressTimestamp = millis(); // タイムスタンプを更新
    } else {
      this->_releaseTimestamp = millis(); // タイムスタンプを更新
    }
  }

  // 長押しの状態を更新
  bool longPressed = false;
  if (this->_pressed) {
    unsigned long elapsedTime = (millis() - this->_pressTimestamp);
    longPressed = elapsedTime >= this->_longPressDuration;
  }

  if (this->_longPressed != longPressed) {
    this->_longPressed = longPressed;
    this->_changedLongPress = true;
  }
}

} // namespace hsbs