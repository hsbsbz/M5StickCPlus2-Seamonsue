
#include "Transform.h"

// もしかしたら、怪しいところがあるかもしれない。

namespace hsbs {

Transform *Transform::identity() {
  this->matrix[0] = 1; // ScaleX
  this->matrix[3] = 0; // skew X or Y ?
  this->matrix[2] = 0; // x
  this->matrix[1] = 0; // skew X or Y ?
  this->matrix[4] = 1; // ScaleY
  this->matrix[5] = 0; // y
  return this;
}

Transform *Transform::skew(float skewX, float skewY) {
  float tanSkewX = std::tan(skewX);
  float tanSkewY = std::tan(skewY);
  float a = this->matrix[0];
  float b = this->matrix[1];
  float c = this->matrix[3];
  float d = this->matrix[4];
  this->matrix[0] = a + b * tanSkewY;
  this->matrix[1] = b + a * tanSkewX;
  this->matrix[3] = c + d * tanSkewY;
  this->matrix[4] = d + c * tanSkewX;

  return this;
}

Transform *Transform::scale(float x, float y) {
  this->matrix[0] *= x;
  this->matrix[1] *= y;
  this->matrix[3] *= x;
  this->matrix[4] *= y;
  return this;
}

Transform *Transform::translate(float x, float y) {
  this->matrix[2] += (this->matrix[0] * x) + (this->matrix[1] * y);
  this->matrix[5] += (this->matrix[3] * x) + (this->matrix[4] * y);
  return this;
}

Transform *Transform::rotate(float angle) {
  float sineValue = std::sin(angle);
  float cosineValue = std::cos(angle);
  float a = this->matrix[0];
  float b = this->matrix[3];
  float c = this->matrix[1];
  float d = this->matrix[4];
  this->matrix[0] = a * cosineValue + c * sineValue;
  this->matrix[3] = b * cosineValue + d * sineValue;
  this->matrix[1] = a * -sineValue + c * cosineValue;
  this->matrix[4] = b * -sineValue + d * cosineValue;
  return this;
}

Transform *Transform::multiply(Transform *transform) {
  float a[6];
  float b[6];
  std::copy(transform->matrix, transform->matrix + 6, a);
  std::copy(this->matrix, this->matrix + 6, b);
  this->matrix[0] = b[0] * a[0] + b[1] * a[3];
  this->matrix[1] = b[0] * a[1] + b[1] * a[4];
  this->matrix[2] = b[0] * a[2] + b[1] * a[5] + b[2];
  this->matrix[3] = b[3] * a[0] + b[4] * a[3];
  this->matrix[4] = b[3] * a[1] + b[4] * a[4];
  this->matrix[5] = b[3] * a[2] + b[4] * a[5] + b[5];
  return this;
}

} // namespace hsbs