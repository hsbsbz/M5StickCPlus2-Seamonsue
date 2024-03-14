#ifndef _HSBS__TWEEN__TWEEN_OBJECT_H_INCLUDE_
#define _HSBS__TWEEN__TWEEN_OBJECT_H_INCLUDE_

#include "Ease.h"
#include "ITweenObject.h"
#include <vector>

namespace hsbs {

//==============================
// Struct
//==============================
/**
 * @struct TweenProperty
 * @brief トゥイーンを行うプロパティ構造体
 */
struct TweenProperty {
  /**
   * @brief 値へのポインタ
   */
  float *valuePtr;
  /**
   * @brief 開始値
   */
  float from;
  /**
   * @brief 終了値
   */
  float to;
};

/**
 * @class TweenObject
 * @brief トゥイーンアニメーションを行うクラス
 */
class TweenObject : public ITweenObject {
public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief コンストラクタ
   * @param duration トゥイーンの時間
   * @param ease イージング関数
   */
  TweenObject(long duration, Ease ease);

  /**
   * @brief デストラクタ
   */
  virtual ~TweenObject();

  /**
   * @brief トゥイーンの状態を取得
   * @return トゥイーンの状態
   */
  TweenState getState() override;

  /**
   * @brief トゥイーンの進行状況を取得
   * @return 進行状況
   */
  float getProgress() override;

  /**
   * @brief トゥイーンをリセット
   * @return 自身のポインタ
   */
  TweenObject *reset() override;

  /**
   * @brief トゥイーンを開始
   * @return 自身のポインタ
   */
  TweenObject *start() override;

  /**
   * @brief トゥイーンを更新
   * @return 自身のポインタ
   */
  TweenObject *update() override;

  /**
   * @brief トゥイーンを完了
   * @return 自身のポインタ
   */
  TweenObject *complete() override;

  /**
   * @brief 遅延時間を設定
   * @return 自身のポインタ
   */
  TweenObject *setDelay(long time);

  /**
   * @brief トゥイーンを行うプロパティを追加
   * @param valuePtr トゥイーンを行う値のポインタ
   * @param from 開始値
   * @param to 終了値
   * @return 自身のポインタ
   */
  TweenObject *add(float *valuePtr, float from, float to);

  /**
   * @brief トゥイーンを行うプロパティを追加
   * @param valuePtr トゥイーンを行う値のポインタ
   * @param to 終了値
   * @return 自身のポインタ
   */
  TweenObject *add(float *valuePtr, float to);

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * @brief イージング関数
   */
  Ease _ease = Ease::LINEAR;

  /**
   * @brief トゥイーンの進行状況
   */
  float _progress = 0.0f;

  /**
   * @brief トゥイーンの時間
   */
  long _duration = 0;

  /**
   * @brief 開始時間
   */
  long _startTime = 0;

  /**
   * @brief 経過時間
   */
  long _elapsedTime = 0;

  /**
   * @brief 遅延時間
   */
  long _delay = 0;

  /**
   * @brief アニメーションするプロパティのリスト
   */
  std::vector<TweenProperty *> _properties;

  /**
   * @brief トゥイーンの状態
   */
  TweenState _state = STANDBY;
};

} // namespace hsbs

#endif