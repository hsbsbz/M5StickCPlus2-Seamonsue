#ifndef _HSBS__DISPLAY__DISPLAY_OBJECT_CONTAINER_H_INCLUDE_
#define _HSBS__DISPLAY__DISPLAY_OBJECT_CONTAINER_H_INCLUDE_

#include "../core/ObjectList.h"
#include "DisplayObject.h"

namespace hsbs {
/**
 * @class DisplayObjectContainer
 * @brief 表示オブジェクトコンテナ。子表示オブジェクトに再帰的にアフィン変換用の行列を適用する。
 */
class DisplayObjectContainer : public DisplayObject {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * @brief 子表示リスト
   */
  ObjectList<DisplayObject *> _childList;

protected:
  //------------------------------
  // Protected
  //------------------------------

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief 子表示オブジェクトの追加
   *
   * @param child 追加する子表示オブジェクト
   * @return 追加した子表示オブジェクト
   */
  DisplayObjectContainer *addChild(DisplayObject *child);

  /**
   * @brief 子表示オブジェクトの削除
   *
   * @param child 削除する子表示オブジェクト
   * @return 削除した子表示オブジェクト
   */
  DisplayObjectContainer *removeChild(DisplayObject *child);

  /**
   * @brief 指定した子表示オブジェクトが登録されているか評価
   *
   * @param child 評価する子表示オブジェクト
   * @return 子表示オブジェクトが登録されている場合はtrue、そうでない場合はfalse
   */
  bool contains(DisplayObject *child);

  /**
   * @brief トランスフォームを更新する
   *
   * @param parentTransform
   */
  virtual void updateTransform(Transform *parentTransform) override;

  /**
   * @brief 描画
   */
  virtual void draw(M5Canvas *targetCanvas) override;

  /**
   * @brief デストラクタ
   */
  virtual ~DisplayObjectContainer();
};
} // namespace hsbs

#endif