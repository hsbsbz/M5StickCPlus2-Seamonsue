
#include "TweenObject.h"

namespace hsbs {

/**
 * @brief コンストラクタ
 * @param duration トゥイーンの期間
 * @param ease イージング関数
 */
TweenObject::TweenObject(long duration, Ease ease) {
  this->_duration = duration;
  this->_ease = ease;
}

/**
 * @brief デストラクタ
 * プロパティリストをクリアします
 */
TweenObject::~TweenObject() {
  for (int i = 0; i < this->_properties.size(); i++) {
    this->_properties[i]->valuePtr = nullptr;
    delete this->_properties[i];
  }
  this->_properties.clear();
}

/**
 * @brief トゥイーンの状態を取得
 * @return TweenState トゥイーンの現在の状態
 */
TweenState TweenObject::getState() { return this->_state; }

/**
 * @brief トゥイーンの進行状況を取得
 * @return float 進行状況（0.0f ~ 1.0f）
 */
float TweenObject::getProgress() { return this->_progress; }

/**
 * @brief トゥイーンをリセット
 * @return TweenObject* このオブジェクトへのポインタ
 */
TweenObject *TweenObject::reset() {
  this->_startTime = 0;
  this->_elapsedTime = 0;
  this->_progress = 0;
  this->_state = STANDBY;
  return this;
}

/**
 * @brief トゥイーンを開始
 * @return TweenObject* このオブジェクトへのポインタ
 */
TweenObject *TweenObject::start() {
  this->_startTime = millis();
  this->_elapsedTime = 0;
  this->_progress = 0;
  this->_state = RUNNING;

  // 1フレームのちらつきが発生しないように from の位置をセット
  unsigned int length = this->_properties.size();
  for (int i = 0; i < length; i++) {
    TweenProperty *p = this->_properties[i];
    *p->valuePtr = p->from;
  }

  return this;
}

/**
 * @brief トゥイーンを更新
 * @return TweenObject* このオブジェクトへのポインタ
 */
TweenObject *TweenObject::update() {
  // 実行中でない場合は何もしない
  if (this->_state != RUNNING) return this;

  // 開始時刻から経過時間を計算
  long now = millis();
  this->_elapsedTime = now - this->_startTime - this->_delay;
  this->_elapsedTime = this->_elapsedTime < 0 ? 0 : this->_elapsedTime;

  // 経過位置を 0.0f ~ 1.0f で計算
  this->_progress = ((float)this->_elapsedTime / (float)this->_duration);
  this->_progress = this->_progress < 0 ? 0 : this->_progress;
  this->_progress = this->_progress > 1 ? 1 : this->_progress;

  // 0 ~ 1 に丸め込む
  float easeValue = applyEaseFunction(this->_ease, this->_progress);

  // 登録されているプロパティの値を更新
  unsigned int length = this->_properties.size();
  for (int i = 0; i < length; i++) {
    TweenProperty *p = this->_properties[i];
    *p->valuePtr = (p->to - p->from) * easeValue + p->from;
  }

  // 完了していたら状態を完了にする
  if (this->_progress == 1.0f) {
    this->complete();
  }
  return this;
}

/**
 * @brief トゥイーンを完了
 * @return TweenObject* このオブジェクトへのポインタ
 */
TweenObject *TweenObject::complete() {
  this->_state = COMPLETE;
  return this;
}

TweenObject *TweenObject::setDelay(long time) {
  this->_delay = time;
  return this;
}

/**
 * @brief トゥイーンを行うプロパティを追加
 * @param valuePtr 値のポインタ
 * @param from 開始値
 * @param to 終了値
 * @return TweenObject* このオブジェクトへのポインタ
 */
TweenObject *TweenObject::add(float *valuePtr, float from, float to) {
  TweenProperty *p = new TweenProperty();
  p->valuePtr = valuePtr;
  p->from = from;
  p->to = to;
  this->_properties.push_back(p);
  return this;
}

/**
 * @brief トゥイーンを行うプロパティを追加
 * @param valuePtr 値のポインタ
 * @param from 開始値
 * @param to 終了値
 * @return TweenObject* このオブジェクトへのポインタ
 */
TweenObject *TweenObject::add(float *valuePtr, float to) {
  TweenProperty *p = new TweenProperty();
  p->valuePtr = valuePtr;
  p->from = *valuePtr;
  p->to = to;
  this->_properties.push_back(p);
  return this;
}

} // namespace hsbs