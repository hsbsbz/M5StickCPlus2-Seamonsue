
#ifndef _HSBS__TWEEN__TWEEN_PARALLEL_LIST_OBJECT_H_INCLUDE_
#define _HSBS__TWEEN__TWEEN_PARALLEL_LIST_OBJECT_H_INCLUDE_

#include "TweenListObject.h"

namespace hsbs {

/**
 * @class TweenParallelListObject
 * @brief リストに追加したトゥイーンを並列に実行するクラス
 */
class TweenParallelListObject : public TweenListObject {
public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief 更新する
   * @return 自身のポインタ
   */
  virtual TweenParallelListObject *update() override;
};

} // namespace hsbs

#endif
