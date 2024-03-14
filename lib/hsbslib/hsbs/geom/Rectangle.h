#ifndef _HSBS__GEOM__RECTANGLE_H_INCLUDE_
#define _HSBS__GEOM__RECTANGLE_H_INCLUDE_

#include "Point.h"

namespace hsbs {

/**
 * @class Rectangle
 * @brief 矩形情報
 */
class Rectangle : public Point {
public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief 幅
   */
  float width;
  /**
   * @brief 高さ
   */
  float height;

  /**
   * コンストラクタ
   */
  Rectangle(float x = 0, float y = 0, float width = 0, float height = 0);
};

} // namespace hsbs

#endif