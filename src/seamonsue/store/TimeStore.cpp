
#include "TimeStore.h"

namespace seamonsue {

const float debugTimeScale = 1;

void TimeStore::restore() {
  const unsigned long now = this->getNow();
  this->_preferences.begin(this->_namespace, true);
  this->_gameStartTimeStamp = this->_preferences.getULong("start", now);
  this->_sleepTimeStamp = this->_preferences.getULong("sleep", now);
  this->_elapsedSec = this->_preferences.getULong("elapsed", 0);
  this->_clockOffsetSec = this->_preferences.getInt("clock", this->_clockOffsetSec);
  this->_preferences.end();
  this->_wakeupTimeStamp = now;
  this->_lastTimeStamp = now;
  this->_elapsedSec += (now - this->_sleepTimeStamp);
}

void TimeStore::update() {
  const unsigned long now = this->getNow();
  this->_elapsedSec += (now - this->_lastTimeStamp);
  this->_lastTimeStamp = now;
}

void TimeStore::save() {
  const unsigned long now = this->getNow();
  this->_preferences.begin(this->_namespace, false);
  this->_preferences.putULong("start", this->_gameStartTimeStamp);
  this->_preferences.putULong("sleep", now);
  this->_preferences.putULong("elapsed", this->_elapsedSec);
  this->_preferences.putInt("clock", this->_clockOffsetSec);
  this->_preferences.end();
}

int TimeStore::appendClockSec(int deltaSec) {
  this->_clockOffsetSec += deltaSec;
  if (this->_clockOffsetSec < 0) this->_clockOffsetSec += 86400;
  this->_clockOffsetSec = this->_clockOffsetSec % 86400;
  return this->_clockOffsetSec;
}

int TimeStore::getClockSec() {
  return this->getTotalSec() + this->_clockOffsetSec;
}

unsigned long TimeStore::getTotalSec() {
  const unsigned long now = this->getNow();
  return (now - this->_gameStartTimeStamp) * debugTimeScale;
}

unsigned long TimeStore::getElapsedSec() {
  return this->_elapsedSec * debugTimeScale;
}

void TimeStore::resetElapsedSec() {
  this->_elapsedSec = 0;
}

unsigned long TimeStore::getNow() {
  return (unsigned long)time(nullptr) % 100000000;
}

void TimeStore::clear() {
  this->_preferences.begin(this->_namespace, false);
  this->_preferences.clear();
  this->_preferences.end();
  this->restore(); // 変数の値も初期値に
}

void TimeStore::clearExceptClock() {
  unsigned long clockTime = (this->_clockOffsetSec + this->getTotalSec()) % 86400;
  this->_preferences.begin(this->_namespace, false);
  this->_preferences.clear();
  this->_preferences.putInt("clock", clockTime);// 時刻設定だけ再び書き込む
  this->_preferences.end();
  this->restore(); // 変数の値も初期値に
}

void TimeStore::appendAge(float day) {
  this->_gameStartTimeStamp -= 86400 * day;
  Serial.println("appendAge");
  Serial.println(day);
}

void TimeStore::appendElapsed(float day) {
  this->_elapsedSec += 86400 * day;
  Serial.println("appendElapsed");
  Serial.println(day);
}

} // namespace seamonsue
