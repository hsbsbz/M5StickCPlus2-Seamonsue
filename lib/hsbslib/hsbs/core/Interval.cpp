

#include "Interval.h"

namespace hsbs {

Interval::Interval(long interval) {
  this->interval = interval;
}

bool Interval::update() {
  // 更新フラグを折っておく
  this->value = false;
  // 現在時刻
  unsigned long now = millis();
  // 経過時間
  unsigned long elapsed = (now - this->_time);
  // 設定した時間経過した。
  if (elapsed >= this->interval || this->_time == -1) {
    this->_time = now;  // 時間をリセット
    this->value = true; // 更新フラグを立てる
  }
  // 返却
  return this->value;
}
} // namespace hsbs