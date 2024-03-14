#ifndef _HSBS__APP__M5STICK_CPLUST2APP_H_INCLUDE_
#define _HSBS__APP__M5STICK_CPLUST2APP_H_INCLUDE_

#include "../activity/ActivityRooter.h"
#include "../core/PullupButton.h"
#include "../event/EventDispatcher.h"
#include "M5EventType.h"
#include "M5StickCPlust2Activity.h"
#include <Arduino.h>
#include <M5StickCPlus2.h>

namespace hsbs {

/**
 * @class M5StickCPlust2App
 * @brief M5StickC Plus2 専用のアプリケーションクラス
 */
class M5StickCPlust2App : public ActivityRooter, public EventDispatcher {

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * @brief プルアップボタン A
   */
  PullupButton _buttonA;

  /**
   * @brief プルアップボタン B
   */
  PullupButton _buttonB;

  /**
   * @brief プルアップボタン C
   */
  PullupButton _buttonC;

  /**
   * @brief 最後にスリープをリセットした時刻
   */
  unsigned long _sleepTimestamp = 0;

  /**
   * @brief 自動でスリープする時間（ms）
   */
  unsigned long _autoSleepTime = 30000; // 30sec

  /**
   * @brief ボタンイベント＞遷移、の流れでボタンイベントの伝達を停止するために必要
   *
   */
  String _path2 = "";

  /**
   * @brief フレームの待機時間
   */
  TickType_t _intrevalTicks;

  /**
   * @brief フレームの待機時間
   */
  unsigned int _intrevaMicros;

  /**
   * @brief 遷移中かどうか。
   *
   * @return true
   * @return false
   */
  bool transitioning();

  /**
   * @brief ボタンAが長押しされたときの処理
   */
  void onLongPressButtonA();

  /**
   * @brief ボタンAが押されたときの処理
   */
  void onPressButtonA();

  /**
   * @brief ボタンAが離されたときの処理
   */
  void onReleaseButtonA();

  /**
   * @brief ボタンBが長押しされたときの処理
   */
  void onLongPressButtonB();

  /**
   * @brief ボタンBが押されたときの処理
   */
  void onPressButtonB();

  /**
   * @brief ボタンBが離されたときの処理
   */
  void onReleaseButtonB();

  /**
   * @brief ボタンCが長押しされたときの処理
   */
  void onLongPressButtonC();

  /**
   * @brief ボタンCが押されたときの処理
   */
  void onPressButtonC();

  /**
   * @brief ボタンCが離されたときの処理
   */
  void onReleaseButtonC();

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief タイムスタンプをリセットする
   */
  void resetSleepTimestamp();

  /**
   * @brief アプリケーションのセットアップ
   */
  void setup();

  /**
   * @brief アプリケーションの更新
   */
  void update();

  /**
   * @brief 即座にスリープ状態にする
   */
  void sleepNow();

  /**
   * @brief 即座にスリープして復帰する
   */
  void restart();

  /**
   * @brief フレームレートを設定
   *
   */
  void setFps(unsigned int fps);

  /**
   * @brief 更新サイクル
   *
   * @return unsigned int
   */
  unsigned int getIntrevalTicks();

  /**
   * @brief 自動でスリープに入るまでの時間（ms）
   *
   * @param ms
   */
  void setAutoSleepTime(unsigned int ms);
};

} // namespace hsbs

#endif