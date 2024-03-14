#include "Bitmap565.h"

namespace hsbs {

Bitmap565::Bitmap565(const unsigned short *data, uint16_t width, uint16_t height) {
  this->width = width;
  this->height = height;
  this->canvas.createSprite(width, height);
  this->canvas.setBuffer((void *)data, width, height, 16);
}

void Bitmap565::draw(M5Canvas *targetCanvas) {
  this->setClipRectToParentCanvas(targetCanvas);
  this->canvas.pushAffine(targetCanvas, this->globalTransform.matrix, this->transparentColor);
  this->resetClipRectToParentCanvas(targetCanvas);
}

Bitmap565::~Bitmap565() {
  // スプライトを破棄
  this->canvas.deleteSprite();
}

} // namespace hsbs