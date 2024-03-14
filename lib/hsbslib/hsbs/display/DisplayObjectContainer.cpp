
#include "DisplayObjectContainer.h"

namespace hsbs {

DisplayObjectContainer::~DisplayObjectContainer() { this->_childList.clear(); }

DisplayObjectContainer *DisplayObjectContainer::addChild(DisplayObject *child) {
  child->parent = this;
  this->_childList.add(child);
  return this;
}

DisplayObjectContainer *DisplayObjectContainer::removeChild(DisplayObject *child) {
  child->parent = nullptr;
  this->_childList.remove(child);
  return this;
}

bool DisplayObjectContainer::contains(DisplayObject *child) {
  return this->_childList.includes(child);
}

void DisplayObjectContainer::updateTransform(Transform *parentTransform) {
  if (!this->visible) return;
  DisplayObject::updateTransform(parentTransform);
  // 子表示オブジェクトに伝達
  unsigned int length = this->_childList.length();
  for (int i = 0; i < length; ++i) {
    DisplayObject *child = this->_childList.getAt(i);
    if (child->visible) {
      child->updateTransform(&this->globalTransform);
    }
  }
}

void DisplayObjectContainer::draw(M5Canvas *targetCanvas) {
  if (!this->visible) return;
  DisplayObject::draw(targetCanvas);
  // 子表示オブジェクトに伝達
  unsigned int length = this->_childList.length();
  for (int i = 0; i < length; ++i) {
    DisplayObject *child = this->_childList.getAt(i);
    if (child->visible) {
      child->draw(targetCanvas);
    }
  }
}

} // namespace hsbs