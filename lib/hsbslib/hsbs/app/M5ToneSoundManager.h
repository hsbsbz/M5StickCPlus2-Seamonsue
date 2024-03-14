#ifndef _HSBS__APP__M5TONE_SOUND_MANAGER_H_INCLUDE_
#define _HSBS__APP__M5TONE_SOUND_MANAGER_H_INCLUDE_

#include "hsbs/core/ObjectList.h"
#include "hsbs/tween/Ease.h"
#include <M5Unified.h>

namespace hsbs {

/**
 * @private
 */
class M5ToneSoundQueue {
public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief 周波数
   */
  float frequency = 0;
  /**
   * @brief 鳴らす時間
   */
  int duration = 0;

  /**
   * @brief 仮想チャンネル番号 (省略された場合、利用可能なチャンネルを使用)
   */
  int channel = -1;

  /**
   * @brief 現在の出力の終了を待たずに、新しい出力を開始
   */
  int stopCurrentSound = true;
  /**
   * @brief 終了時間
   */
  long endTime = 0;
  /**
   * @brief 再生中か
   */
  bool playing = false;
};

/**
 * @class M5ToneSoundManager
 * @brief M5.Speaker.tone をも少し触りやすくラップしたクラス。
 */
class M5ToneSoundManager {

private:
  //------------------------------
  // Private
  //------------------------------
  hsbs::ObjectList<M5ToneSoundQueue *> _list;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief トーン音を追加
   *
   * @param frequency 周波数
   * @param duration 鳴らす時間
   * @param channel 仮想チャンネル番号 (省略された場合、利用可能なチャンネルを使用)
   */
  void pushTone(float frequency, int duration, int channel = 0);

  /**
   * @brief 待機時間を追加
   * @param duration
   */
  void pushWait(int duration);

  /**
   * @brief 更新
   */
  void update();

  /**
   * @brief 音を停止する
   */
  void stop();

  /**
   * @brief トーン音の音量の体感がずいぶん違うのでバイアスをかけてみる。
   *
   * @param frequency
   * @return float
   */
  uint8_t getVolumeBiasByFrequency(float frequency);
};

} // namespace hsbs

#endif
