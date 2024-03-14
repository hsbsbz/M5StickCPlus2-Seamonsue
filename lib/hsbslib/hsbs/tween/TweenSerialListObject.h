
#ifndef _HSBS__TWEEN__TWEEN_SERIAL_LIST_OBJECT_H_INCLUDE_
#define _HSBS__TWEEN__TWEEN_SERIAL_LIST_OBJECT_H_INCLUDE_

#include "TweenListObject.h"

namespace hsbs {

/**
 * @class TweenSerialListObject
 * @brief リストに追加したトゥイーンを直接に実行するクラス
 */
class TweenSerialListObject : public TweenListObject {
public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief 更新する
   * @return 自身のポインタ
   */
  virtual TweenSerialListObject *update() override;
};

} // namespace hsbs

#endif
