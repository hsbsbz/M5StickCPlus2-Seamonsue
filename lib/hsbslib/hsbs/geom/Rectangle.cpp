
#include "Rectangle.h"

namespace hsbs {

Rectangle::Rectangle(float x, float y, float width, float height) : Point(x, y) {
  this->width = width;
  this->height = height;
}

} // namespace hsbs
