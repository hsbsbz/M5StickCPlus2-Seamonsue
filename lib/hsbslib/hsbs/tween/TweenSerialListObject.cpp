

#include "TweenSerialListObject.h"

namespace hsbs {

/**
 * @brief 更新する
 * @return TweenSerialListObject* 自身のポインタ
 */
TweenSerialListObject *TweenSerialListObject::update() {
  // 実行中でない場合は何もしない
  if (this->_state != RUNNING) return this;

  // ループ
  unsigned int length = this->_list.length();
  for (int i = 0; i < length; i++) {
    ITweenObject *child = this->_list.getAt(i);
    TweenState state = child->getState();
    if (state == STANDBY) {
      child->start();
    }
    if (state == RUNNING) {
      child->update();
    }
    if (child->getState() != COMPLETE) {
      return this;
    }
  }

  // 子が全て完了したら自身を完了
  this->complete();

  return this;
}

} // namespace hsbs
