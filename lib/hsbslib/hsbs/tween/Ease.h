
#ifndef _HSBS__TWEEN__EASE_H_INCLUDE_
#define _HSBS__TWEEN__EASE_H_INCLUDE_

#include <Arduino.h>
#include <cmath>

namespace hsbs {

/**
 * @enum Enum
 */
enum Ease {
  /**
   * @brief 直線
   */
  LINEAR,
  /**
   * @brief 減速（弱）
   */
  OUT_SINE,
  /**
   * @brief 減速（中）
   */
  OUT_CUBIC,
  /**
   * @brief 減速（強）
   */
  OUT_EXPO,

  /**
   * @brief 加速（弱）
   */
  IN_SINE,
  /**
   * @brief 加速（中）
   */
  IN_CUBIC,
  /**
   * @brief 加速（強）
   */
  IN_EXPO,
  /**
   * @brief 減速＆加速（弱）
   */
  IN_OUT_SINE,
  /**
   * @brief 減速＆加速（中）
   */
  IN_OUT_CUBIC,
  /**
   * @brief 減速＆加速（強）
   */
  IN_OUT_EXPO
};

/**
 * @brief イージング関数を適用する
 *
 * @param ease イージング関数の種類
 * @param position 0-1　
 * @return イージング後の値
 */
float applyEaseFunction(Ease ease, float position);

namespace EaseFunction {

namespace In {
float sine(float t);
float cubic(float t);
float expo(float t);
} // namespace In

namespace Out {
float sine(float t);
float cubic(float t);
float expo(float t);
} // namespace Out

namespace InOut {
float sine(float t);
float cubic(float t);
float expo(float t);
} // namespace InOut

} // namespace EaseFunction
} // namespace hsbs

#endif
