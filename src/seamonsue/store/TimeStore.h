#ifndef _SEAMONSUE__STORE__TIME_STORE_H_INCLUDE_
#define _SEAMONSUE__STORE__TIME_STORE_H_INCLUDE_

#include "Preferences.h"

namespace seamonsue {

class TimeStore {
private:
  Preferences _preferences;

  /**
   * @brief 名前空間
   */

  const char *_namespace = "seamons_time_v1";

  /**
   * @brief ゲーム開始時刻
   */
  long _gameStartTimeStamp;

  /**
   * @brief スリープ時刻
   */
  long _sleepTimeStamp;

  /**
   * @brief 復帰時刻
   */
  long _wakeupTimeStamp;

  /**
   * @brief 前回の計測時刻
   *
   */
  long _lastTimeStamp;

  /**
   * @brief 経過時間
   *
   */
  long _elapsedSec;

  /**
   * @brief 時刻合わせオフセット(sec)
   *
   */
  int _clockOffsetSec = 0;

  /**
   * 現在時刻
   */
  unsigned long getNow();

public:
  /**
   * @brief 時刻合わせオフセットの値を追加(sec)
   *
   * @return int
   */
  int appendClockSec(int deltaSec);

  /**
   * @brief 時刻合わせオフセット値を取得(sec)
   *
   * @return int
   */
  int getClockSec();

  /**
   * @brief 総プレイ時間(sec)
   *
   * @return unsigned long
   */
  unsigned long getTotalSec();

  /**
   * @brief 経過時間(sec)
   *
   * @return unsigned long
   */
  unsigned long getElapsedSec();

  /**
   * @brief 経過時間をリセット
   */
  void resetElapsedSec();

  /**
   * @brief セーブデータを削除
   */
  void clear();

  /**
   * @brief ストレージからデータを読み出す
   */
  void restore();

  /**
   * @brief 更新
   */
  void update();

  /**
   * @brief ストレージにデータを書き込む
   */
  void save();

  /**
   * @brief デバッグ用に総時間を追加
   */
  void appendAge(float day);

  /**
   * @brief デバッグ用に経過時間を追加
   */
  void appendElapsed(float day);
};

} // namespace seamonsue

#endif
