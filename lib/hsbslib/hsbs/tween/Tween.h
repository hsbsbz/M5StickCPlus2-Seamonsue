

#ifndef _HSBS__TWEEN__TWEEN_H_INCLUDE_
#define _HSBS__TWEEN__TWEEN_H_INCLUDE_

#include "../core/ObjectList.h"
#include "ITweenObject.h"
#include "TweenCallback.h"
#include "TweenObject.h"
#include "TweenParallelListObject.h"
#include "TweenSerialListObject.h"

namespace hsbs {
/**
 * @class Tween
 * @brief トゥイーンの親クラス。トゥイーンに関する機能はこのクラスを通して使用する。
 */
class Tween : public TweenSerialListObject {
public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief 直列に実行するトゥイーンリストを作成
   *
   * @tparam Args
   * @param first
   * @param args
   * @return TweenSerialListObject*
   *
   */
  template <typename... Args>
  TweenSerialListObject *serial(ITweenObject *first, Args... args) {
    TweenSerialListObject *serialList = new TweenSerialListObject();
    serialList->add(first);
    serialList->add(args...);
    this->_instanceList.add(serialList);
    return serialList;
  }

  /**
   * @brief 並列に実行するトゥイーンリストを作成
   *
   * @tparam Args
   * @param first
   * @param args
   * @return TweenParallelListObject*
   */
  template <typename... Args>
  TweenParallelListObject *parallel(ITweenObject *first, Args... args) {
    TweenParallelListObject *parallelList = new TweenParallelListObject();
    parallelList->add(first);
    parallelList->add(args...);
    this->_instanceList.add(parallelList);
    return parallelList;
  }

  /**
   * @brief トゥイーンを作成
   *
   * @param duration
   * @param ease
   * @return TweenObject*
   */
  TweenObject *tween(long duration, Ease ease);

  /**
   * @brief 待機用の空のトゥイーンを作成
   *
   * @param duration
   * @param ease
   * @return TweenObject*
   */
  TweenObject *wait(long duration);

  /**
   * @brief コールバックを作成
   *
   * @param duration
   * @param ease
   * @return TweenObject*
   */
  TweenCallback *callback(TweenCallbackFunction callback);

  /**
   * @brief 作成したトゥイーンオブジェクトを破棄、登録されているトゥイーンオブジェクトを空にする。
   */
  void clear();

  virtual ~Tween();

private:
  ObjectList<ITweenObject *> _instanceList;
};

} // namespace hsbs
#endif