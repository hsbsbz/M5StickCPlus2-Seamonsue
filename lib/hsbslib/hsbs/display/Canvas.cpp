#include "Canvas.h"

namespace hsbs {
Canvas::Canvas(uint16_t width, uint16_t height) {
  this->canvas.createSprite(width, height);
  this->width = width;
  this->height = height;
}

void Canvas::draw(M5Canvas *targetCanvas) {
  this->setClipRectToParentCanvas(targetCanvas);
  this->canvas.pushAffine(targetCanvas, this->globalTransform.matrix, this->transparentColor);
  this->resetClipRectToParentCanvas(targetCanvas);
}

Canvas::~Canvas() {
  // スプライトを破棄
  this->canvas.deleteSprite();
}

} // namespace hsbs