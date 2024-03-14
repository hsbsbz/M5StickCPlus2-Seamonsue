
#include "TweenCallback.h"

namespace hsbs {

/**
 * @brief コンストラクタ
 */
TweenCallback::TweenCallback(TweenCallbackFunction callback) {
  this->_callback = callback;
}

/**
 * @brief デストラクタ
 * プロパティリストをクリアします
 */
TweenCallback::~TweenCallback() {
  this->_callback = nullptr;
}

/**
 * @brief トゥイーンの状態を取得
 * @return TweenState トゥイーンの現在の状態
 */
TweenState TweenCallback::getState() { return this->_state; }

/**
 * @brief トゥイーンの進行状況を取得
 * @return float 進行状況（0.0f ~ 1.0f）
 */
float TweenCallback::getProgress() { return (this->_state == STANDBY) ? 0 : 1; }

/**
 * @brief トゥイーンをリセット
 * @return TweenCallback* このオブジェクトへのポインタ
 */
TweenCallback *TweenCallback::reset() {
  return this;
}

/**
 * @brief トゥイーンを開始
 * @return TweenCallback* このオブジェクトへのポインタ
 */
TweenCallback *TweenCallback::start() {
  this->_state = RUNNING;
  return this;
}

/**
 * @brief トゥイーンを更新
 * @return TweenCallback* このオブジェクトへのポインタ
 */
TweenCallback *TweenCallback::update() {
  // 実行中でない場合は何もしない
  if (this->_state != RUNNING) return this;
  this->_callback();
  this->complete();
  return this;
}

/**
 * @brief トゥイーンを完了
 * @return TweenCallback* このオブジェクトへのポインタ
 */
TweenCallback *TweenCallback::complete() {
  this->_state = COMPLETE;
  return this;
}

} // namespace hsbs