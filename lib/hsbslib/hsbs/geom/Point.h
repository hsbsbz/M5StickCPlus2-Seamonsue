

#ifndef _HSBS__GEOM__POINT_H_INCLUDE_
#define _HSBS__GEOM__POINT_H_INCLUDE_

namespace hsbs {

/**
 * @class Point
 * @brief 点情報
 */
class Point {
public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief座標 X
   */
  float x;

  /**
   * @brief 座標 Y
   */
  float y;

  /**
   * @brief コンストラクタ
   *
   * @param x
   * @param y
   */
  Point(float x = 0, float y = 0);
};

} // namespace hsbs

#endif