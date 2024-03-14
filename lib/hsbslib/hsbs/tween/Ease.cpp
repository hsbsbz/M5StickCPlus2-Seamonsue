
#include "Ease.h"

namespace hsbs {

/**
 * @brief イージング関数を適用します。
 *
 * @param ease イージングの種類
 * @param t 0-1
 * @return 適用後の値を返します。
 */
float applyEaseFunction(Ease ease, float position) {
  // イージングを適用
  switch (ease) {
  case OUT_SINE: return EaseFunction::Out::sine(position);
  case OUT_CUBIC: return EaseFunction::Out::cubic(position);
  case OUT_EXPO: return EaseFunction::Out::expo(position);
  case IN_SINE: return EaseFunction::In::sine(position);
  case IN_CUBIC: return EaseFunction::In::cubic(position);
  case IN_EXPO: return EaseFunction::In::expo(position);
  case IN_OUT_SINE: return EaseFunction::InOut::sine(position);
  case IN_OUT_CUBIC: return EaseFunction::InOut::cubic(position);
  case IN_OUT_EXPO: return EaseFunction::InOut::expo(position);
  }
  // 例外
  return position;
}

namespace EaseFunction {

namespace In {

float sine(float t) { return 1 - std::cos(t * HALF_PI); }

float cubic(float t) { return t * t * t; }

float expo(float t) {
  if (t == 0) return 0;
  return std::pow(2, 10 * (t - 1));
}

} // namespace In

namespace Out {

float sine(float t) { return std::sin(t * HALF_PI); }

float cubic(float t) {
  --t;
  return t * t * t + 1;
}

float expo(float t) {
  if (t == 1) return 1;
  return 1 - std::pow(2, -10 * t);
}

} // namespace Out
namespace InOut {

float sine(float t) { return -0.5 * (std::cos(PI * t) - 1); }

float cubic(float t) {
  t *= 2;
  if (t < 1) return t * t * t / 2;
  t -= 2;
  return (t * t * t + 2) / 2;
}

float expo(float t) {
  if (t == 0 || t == 1) return t;
  t *= 2;
  if (t < 1) {
    return std::pow(2, 10 * (t - 1)) / 2;
  }
  return (2 - std::pow(2, -10 * (t - 1))) / 2;
}
} // namespace InOut
} // namespace EaseFunction
} // namespace hsbs
