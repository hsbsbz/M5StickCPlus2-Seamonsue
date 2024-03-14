#ifndef _HSBS__APP__M5STICK_CPLUST2ACTIVITY_H_INCLUDE_
#define _HSBS__APP__M5STICK_CPLUST2ACTIVITY_H_INCLUDE_

#include "../activity/Activity.h"
#include "../display/Canvas.h"

namespace hsbs {
/**
 * @class M5StickCPlust2Activity
 * @brief M5StickC Plus2 専用の Activity サブクラス。ボタン入力のコールバックを追加
 */
class M5StickCPlust2Activity : public Activity {
protected:
  /**
   * @brief 自動スリープのタイムスタンプをリセットする
   */
  void resetSleepTimestamp();

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief ボタンAが長押しされたときの処理
   */
  virtual void onLongPressButtonA() {}

  /**
   * @brief ボタンAが押されたときの処理
   */
  virtual void onPressButtonA() {}

  /**
   * @brief ボタンAが離されたときの処理
   */
  virtual void onReleaseButtonA() {}

  /**
   * @brief ボタンBが長押しされたときの処理
   */
  virtual void onLongPressButtonB() {}

  /**
   * @brief ボタンBが押されたときの処理
   */
  virtual void onPressButtonB() {}

  /**
   * @brief ボタンBが離されたときの処理
   */
  virtual void onReleaseButtonB() {}

  /**
   * @brief ボタンCが長押しされたときの処理
   */
  virtual void onLongPressButtonC() {}

  /**
   * @brief ボタンCが押されたときの処理
   */
  virtual void onPressButtonC() {}

  /**
   * @brief ボタンCが離されたときの処理
   */
  virtual void onReleaseButtonC() {}

  /**
   * @brief スリープ直前の処理
   */
  virtual void onSleepBefore() {}
};

} // namespace hsbs

#endif