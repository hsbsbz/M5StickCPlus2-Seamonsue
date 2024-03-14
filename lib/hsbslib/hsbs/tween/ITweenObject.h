
#ifndef _HSBS__TWEEN__ITWEEN_OBJECT_H_INCLUDE_
#define _HSBS__TWEEN__ITWEEN_OBJECT_H_INCLUDE_

namespace hsbs {

//==============================
// Enum
//==============================
/**
 * @enum TweenState
 * @brief トゥイーンの状態
 */
enum TweenState {
  /**
   * @brief 待機中
   */
  STANDBY = 0,
  /**
   * @brief 実行中
   */
  RUNNING = 1,
  /**
   * @brief 完了
   */
  COMPLETE = 2
};

/**
 * @class ITweenObject
 * @brief トゥイーンオブジェクトのインターフェース
 */
class ITweenObject {
public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief コンストラクタ
   */
  ITweenObject(){};

  /**
   * @brief デストラクタ
   */
  virtual ~ITweenObject(){};

  /**
   * @brief トゥイーンの状態を取得
   * @return TweenState トゥイーンの状態
   */
  virtual TweenState getState();

  /**
   * @brief トゥイーンの進行状況を取得
   * @return float 進行状況（0.0 ~ 1.0）
   */
  virtual float getProgress();

  /**
   * @brief トゥイーンをリセット
   * @return 自身のポインタ
   */
  virtual ITweenObject *reset();

  /**
   * @brief トゥイーンを開始
   * @return 自身のポインタ
   */
  virtual ITweenObject *start();

  /**
   * @brief トゥイーンを更新
   * @return 自身のポインタ
   */
  virtual ITweenObject *update();

  /**
   * @brief トゥイーンを完了
   * @return 自身のポインタ
   */
  virtual ITweenObject *complete();
};

} // namespace hsbs

#endif