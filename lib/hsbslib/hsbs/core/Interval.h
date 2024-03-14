#ifndef _HSBS__CORE__INTERVAL_H_INCLUDE_
#define _HSBS__CORE__INTERVAL_H_INCLUDE_

#include <Arduino.h>

namespace hsbs {

/**
 * @brief 一定以上の間隔をあけて実行したい場合に使う
 */
class Interval {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * @brief 経過時間
   */
  long _time = -1;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief インターバル時間
   */
  long interval;

  /**
   * @brief 指定の時間を跨いだフレームで true になる
   *
   */
  bool value;

  /**
   * @brief コンストラクタ
   *
   * @param interval インターバル時間
   */
  Interval(long interval);

  /**
   * @brief 更新処理

   * @return 指定の時間を跨いだフレームの場合 true を返却する
   */
  bool update();
};

} // namespace hsbs

#endif