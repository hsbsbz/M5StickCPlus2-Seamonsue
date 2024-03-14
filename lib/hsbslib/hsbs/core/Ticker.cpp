

#include "Ticker.h"

namespace hsbs {

void Ticker::update() {
  for (int i = 0; i < this->_list.size(); ++i) {
    this->_list[i]->update();
  }
}

void Ticker::setupInterval(long interval) {
  Interval *object = new Interval(interval);
  this->_list.push_back(object);
}

bool Ticker::checkInterval(long interval) {
  // 該当のインターバルオブジェクトがある場合
  for (int i = 0; i < this->_list.size(); ++i) {
    if (this->_list[i]->interval == interval) {
      return this->_list[i]->value;
    }
  }
  // 新規作成
  Interval *object = new Interval(interval);
  this->_list.push_back(object);
  object->update();
  return true; // 新規作成時の最初のフレームは必ず発火
}

} // namespace hsbs