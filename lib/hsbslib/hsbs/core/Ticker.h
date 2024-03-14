

#ifndef _HSBS__CORE__TICKER_H_INCLUDE_
#define _HSBS__CORE__TICKER_H_INCLUDE_

#include "Interval.h"
#include "ObjectList.h"

namespace hsbs {

/**
 * @brief 一定以上の間隔をあけて実行したい場合に使う。Ticker だと本来 Ticker 側から発火すべきな気がするけど一旦いいや。
 */
class Ticker {
private:
  //------------------------------
  // Private
  //------------------------------
  std::vector<Interval *> _list;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief 内部の Interval を更新する
   */
  void update();

  /**
   * @brief インターバルを作成
   *
   * @param interval
   */
  void setupInterval(long interval);

  /**
   * @brief インターバルの状態を確認
   *
   * @param interval
   * @return true
   * @return false
   */
  bool checkInterval(long interval);
};

} // namespace hsbs

#endif