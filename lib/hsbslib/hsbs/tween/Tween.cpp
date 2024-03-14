
#include "Tween.h"

namespace hsbs {

Tween::~Tween() {
  while (this->_instanceList.length()) {
    delete this->_instanceList.pop();
  }
}

TweenObject *Tween::wait(long duration) {
  TweenObject *object = new TweenObject(duration, Ease::LINEAR);
  this->_instanceList.add(object);
  return object;
}

TweenObject *Tween::tween(long duration, Ease ease) {
  TweenObject *object = new TweenObject(duration, ease);
  this->_instanceList.add(object);
  return object;
}

TweenCallback *Tween::callback(TweenCallbackFunction callback) {
  TweenCallback *object = new TweenCallback(callback);
  this->_instanceList.add(object);
  return object;
}

void Tween::clear() {
  while (this->_instanceList.length()) {
    ITweenObject *object = this->_instanceList.pop();
    delete object;
  }
  this->_list.clear();
}

} // namespace hsbs