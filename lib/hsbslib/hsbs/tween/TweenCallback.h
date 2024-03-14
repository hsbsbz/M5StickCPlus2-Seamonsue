

#ifndef _HSBS__TWEEN__TWEEN_CALLBACK_H_INCLUDE_
#define _HSBS__TWEEN__TWEEN_CALLBACK_H_INCLUDE_

#include "../core/ObjectList.h"
#include "../tween/Ease.h"
#include "../tween/ITweenObject.h"
#include <functional>

namespace hsbs {

using TweenCallbackFunction = std::function<void()>;

/**
 * @class TweenCallback
 * @brief 実行中のトゥイーンリストでコールバックを行うクラス
 */
class TweenCallback : public ITweenObject {
public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief コンストラクタ
   */
  TweenCallback(TweenCallbackFunction callback);

  /**
   * @brief デストラクタ
   */
  virtual ~TweenCallback();

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
   * @return リセット後のトゥイーンオブジェクト
   */
  TweenCallback *reset() override;

  /**
   * @brief トゥイーンを開始
   * @return 開始後のトゥイーンオブジェクト
   */
  TweenCallback *start() override;

  /**
   * @brief トゥイーンを更新
   * @return 更新後のトゥイーンオブジェクト
   */
  TweenCallback *update() override;

  /**
   * @brief トゥイーンを完了
   * @return 完了後のトゥイーンオブジェクト
   */
  TweenCallback *complete() override;

  //------------------------------
  // Protected
  //------------------------------
protected:
  /**
   * @brief トゥイーンの状態
   */
  TweenState _state = STANDBY;

  /**
   * @brief
   *
   */
  TweenCallbackFunction _callback;
};

} // namespace hsbs

#endif