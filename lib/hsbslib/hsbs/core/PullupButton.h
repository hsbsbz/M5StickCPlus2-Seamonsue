#ifndef _HSBS__CORE__PULLUP_BUTTON_H_INCLUDE_
#define _HSBS__CORE__PULLUP_BUTTON_H_INCLUDE_

#include <Arduino.h>

namespace hsbs {
/**
 * @class PullupButton
 * @brief プルアップボタンの判定を入力判定を行うクラス
 */
class PullupButton {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * @brief ピンアサイン
   */
  uint8_t _pin = 0;

  /**
   * @brief ボタンを押した時のタイムスタンプ
   */
  long _pressTimestamp = 0;

  /**
   * @brief ボタンを離した時のタイムスタンプ
   */
  long _releaseTimestamp = 0;

  /**
   * @brief ボタンが押下判定になっているかどうか
   */
  bool _pressed = false;

  /**
   * @brief ボタンが長押し判定になっているかどうか
   */
  bool _longPressed = false;

  /**
   * @brief ボタンの押下状態が変更されたかどうかを格納
   */
  bool _changed = false;

  /**
   * @brief ボタンの長押し状態が変更されたかどうかを格納
   */
  bool _changedLongPress = false;

  /**
   * @brief チャタリング誤判定防止用のカウンタ
   */
  unsigned int _count = 0;

  /**
   * @brief 長押し判定時間
   */
  unsigned int _longPressDuration = 1000;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief セットアップ
   *
   * @param pin ピン番号
   * @param longPressDuration 長押し判定時間
   */
  void setup(uint8_t pin, unsigned int longPressDuration);

  /**
   * @brief ピンの番号を取得
   * @return ピン番号
   */
  uint8_t getPin();

  /**
   * @brief ボタンの押下状態を取得
   * @return 押下状態（true: 押下, false: 非押下）
   */
  bool pressed();

  /**
   * @brief ボタンの長押し状態を取得
   * @return 長押し状態（true: 長押し, false: 非長押し）
   */
  bool longPressed();

  /**
   * @brief ボタンの押下状態が変更されたかどうかを取得
   * @return 押下状態の変更（true: 変更あり, false: 変更なし）
   */
  bool changed();

  /**
   * @brief ボタンの長押し状態が変更されたかどうかを取得
   * @return 長押し状態の変更（true: 変更あり, false: 変更なし）
   */
  bool changedLongPress();

  /**
   * @brief ボタンの状態を更新
   */
  void update();
};
} // namespace hsbs

#endif