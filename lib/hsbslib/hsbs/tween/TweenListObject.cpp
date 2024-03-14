
#include "TweenListObject.h"

namespace hsbs {

TweenListObject::TweenListObject() {}

TweenListObject::~TweenListObject() {
  this->_list.clear();
}

unsigned int TweenListObject::length() { return this->_list.length(); }

TweenState TweenListObject::getState() { return this->_state; }

float TweenListObject::getProgress() {
  float progress = 0.0f;
  unsigned int length = this->_list.length();
  for (int i = 0; i < length; i++) {
    progress += this->_list.getAt(i)->getProgress();
  }
  return progress /= (float)length;
}

TweenListObject *TweenListObject::reset() {
  this->_state = STANDBY;
  unsigned int length = this->_list.length();
  for (int i = 0; i < length; i++) {
    this->_list.getAt(i)->reset();
  }
  return this;
}

TweenListObject *TweenListObject::start() {
  unsigned int length = this->_list.length();

  if (length == 0) {
    this->_state = COMPLETE;
    return this;
  }

  this->_state = RUNNING;
  for (int i = 0; i < length; i++) {
    ITweenObject *child = this->_list.getAt(i);
    if (child->getState() == COMPLETE) {
      child->reset();
    }
  }
  return this;
}

TweenListObject *TweenListObject::update() {
  // 実行中でない場合は何もしない
  if (this->_state != RUNNING) return this;
  return this;
}

TweenListObject *TweenListObject::complete() {
  this->_state = COMPLETE;
  return this;
}

} // namespace hsbs
