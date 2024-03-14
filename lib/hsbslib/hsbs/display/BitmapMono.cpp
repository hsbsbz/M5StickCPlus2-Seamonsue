#include "BitmapMono.h"

namespace hsbs {

BitmapMono::BitmapMono(const uint8_t *data, uint16_t width, uint16_t height) {
  this->width = width;
  this->height = height;
  this->transparentColor = 1;
  this->canvas.setColorDepth(1);
  this->canvas.createSprite(width, height);
  this->canvas.setBuffer((void *)data, width, height, 1);
}

void BitmapMono::draw(M5Canvas *targetCanvas) {
  this->setClipRectToParentCanvas(targetCanvas);
  this->canvas.pushAffine(targetCanvas, this->globalTransform.matrix, this->transparentColor);
  this->resetClipRectToParentCanvas(targetCanvas);
}

BitmapMono::~BitmapMono() {
  // スプライトを破棄
  this->canvas.deleteSprite();
  this->clipRect = nullptr;
}

} // namespace hsbs