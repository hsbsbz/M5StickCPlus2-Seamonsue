
#ifndef _HSBS__TWEEN__TWEEN_LIST_OBJECT_H_INCLUDE_
#define _HSBS__TWEEN__TWEEN_LIST_OBJECT_H_INCLUDE_

#include "../core/ObjectList.h"
#include "ITweenObject.h"

namespace hsbs {

/**
 * @class TweenListObject
 * @brief 複数のトゥイーンをリストに格納するクラス。
 */
class TweenListObject : public ITweenObject {
public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief コンストラクタ
   */
  TweenListObject();

  /**
   * @brief デストラクタ
   */
  virtual ~TweenListObject();

  /**
   * @brief 登録されている数を取得
   * @return 登録されている数
   */
  unsigned int length();

  /**
   * @brief 状態を取得
   * @return 状態
   */
  virtual TweenState getState() override;

  /**
   * @brief 進行状況を取得
   * @return 進行状況
   */
  virtual float getProgress() override;

  /**
   * @brief リセットする
   * @return リセット後のオブジェクト
   */
  virtual TweenListObject *reset() override;

  /**
   * @brief 開始する
   * @return 開始後のオブジェクト
   */
  virtual TweenListObject *start() override;

  /**
   * @brief 更新する
   * @return 更新後のオブジェクト
   */
  virtual TweenListObject *update() override;

  /**
   * @brief 完了する
   * @return 完了後のオブジェクト
   */
  virtual TweenListObject *complete() override;

  TweenListObject *add(ITweenObject *first) {
    this->_list.add(first);
    return this;
  }

  template <typename... Args>
  TweenListObject *add(ITweenObject *first, Args... rest) {
    this->_list.add(first);
    this->add(rest...);
    return this;
  }

protected:
  /**
   * @brief アニメーションするプロパティリスト
   */
  ObjectList<ITweenObject *> _list;

  /**
   * @brief 状態
   */
  TweenState _state = STANDBY;
};

} // namespace hsbs

#endif
