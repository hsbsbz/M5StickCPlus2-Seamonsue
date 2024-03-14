#include "DisplayObject.h"

namespace hsbs {

DisplayObject::~DisplayObject() {
  this->parent = nullptr;
  this->clipRect = nullptr;
}

void DisplayObject::setClipRectToParentCanvas(M5Canvas *canvas) {
  if (this->clipRect != nullptr) {
    canvas->setClipRect(
        this->clipRect->x,
        this->clipRect->y,
        this->clipRect->width,
        this->clipRect->height);
  }
}

void DisplayObject::resetClipRectToParentCanvas(M5Canvas *canvas) {
  if (this->clipRect != nullptr) {
    canvas->clearClipRect();
  }
}

void DisplayObject::updateTransform(Transform *parentTransform) {
  if (!this->visible) return;

  // ローカルトランスフォーム

  // 初期化
  this->transform.identity();

  // 位置
  if (this->x != 0 || this->y != 0) {
    this->transform.translate(this->x, this->y);
  }

  // 縮尺
  if (this->scaleX != 1 || this->scaleY != 1) {
    this->transform.scale(this->scaleX, this->scaleY);
  }

  // 回転
  if (this->rotation != 0) {
    this->transform.rotate(this->rotation);
  }

  // 傾斜
  if (this->skewX != 0 || this->skewY != 0) {
    this->transform.skew(this->skewX, this->skewY);
  }

  // 基準点
  if (this->anchorX != 0 || this->anchorY != 0) {
    this->transform.translate(-this->anchorX, -this->anchorY);
  }

  // 親コンテナを合算したトランスフォーム

  // 初期化
  this->globalTransform.identity();

  // 親のトランスフォームを合算
  if (parentTransform != nullptr) {
    this->globalTransform.multiply(parentTransform);
  }

  // ローカルトランスフォームを合算
  this->globalTransform.multiply(&this->transform);
}

void DisplayObject::draw(M5Canvas *targetCanvas) {}

DisplayObject *DisplayObject::setPosition(float x, float y) {
  this->x = x;
  this->y = y;
  return this;
}

DisplayObject *DisplayObject::setAnchor(float x, float y) {
  this->anchorX = x;
  this->anchorY = y;
  return this;
}

DisplayObject *DisplayObject::setScale(float x, float y) {
  this->scaleX = x;
  this->scaleY = y;
  return this;
}

DisplayObject *DisplayObject::setSkew(float x, float y) {
  this->skewX = x;
  this->skewY = y;
  return this;
}

DisplayObject *DisplayObject::setRotation(float angle) {
  this->rotation = angle;
  return this;
}

DisplayObject *DisplayObject::setDeg(float deg) {
  this->rotation = DEG_TO_RAD * deg;
  return this;
}

} // namespace hsbs