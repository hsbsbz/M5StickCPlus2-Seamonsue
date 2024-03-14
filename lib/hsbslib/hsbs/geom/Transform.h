
#ifndef _HSBS__GEOM__TRANSFORM_H_INCLUDE_
#define _HSBS__GEOM__TRANSFORM_H_INCLUDE_

#include <algorithm>
#include <cmath>

namespace hsbs {

/**
 * @class Transform
 * @brief アフィン変換用の行列を操作するラッパー
 */
class Transform {
private:
  //------------------------------
  // Private
  //------------------------------
public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief 行列
   *
   */
  float matrix[6] = {1, 0, 0, 0, 1, 0};

  /**
   * @brief 行列を初期化
   *
   * @return 自身のポインタ
   */
  Transform *identity();

  /**
   * @brief 縮尺を反映
   *
   * @param x
   * @param y
   * @return 自身のポインタ
   */
  Transform *scale(float x, float y);

  /**
   * @brief 傾きを反映
   *
   * @param x
   * @param y
   * @return 自身のポインタ
   */
  Transform *skew(float x, float y);

  /**
   * @brief 位置を反映
   *
   * @param x
   * @param y
   * @return 自身のポインタ
   */
  Transform *translate(float x, float y);

  /**
   * @brief 回転を反映
   *
   * @param angle ラジアン角
   * @return 自身のポインタ
   */
  Transform *rotate(float angle);

  /**
   * @brief Transform を合算
   *
   * @param Transform
   * @return 自身のポインタ
   */
  Transform *multiply(Transform *transform);
};

} // namespace hsbs

#endif