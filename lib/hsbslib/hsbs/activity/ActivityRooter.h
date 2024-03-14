
#ifndef _HSBS__ACTIVITY__ACTIVITY_ROOTER_H_INCLUDE_
#define _HSBS__ACTIVITY__ACTIVITY_ROOTER_H_INCLUDE_

#include <Arduino.h>
#include <M5Unified.h>

#include "../core/ObjectList.h"
#include "../display/DisplayObjectContainer.h"
#include "Activity.h"

namespace hsbs {

/**
 * @class ActivityRooter
 * @brief Activity を登録して操作する。
 */
class ActivityRooter {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * 実行中かどうかを示すフラグ
   */
  bool _running = false;

  /**
   * 自身の設定されているパス
   */
  String _path = "";

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * @brief アクティビティのリストを登録しておくリスト
   */
  ObjectList<Activity *> activityList;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief オフスクリーンレンダリング用の Canvas 。
   */
  M5Canvas canvas;

  /**
   * @brief コンストラクタ
   */
  ActivityRooter();

  /**
   * @brief 現在のパス
   *
   * @return String
   */
  String getPath();

  /**
   * @brief 実行中かどうか評価する
   *
   * @return 実行中なら true そうでなければ false を返却する
   */
  bool running();

  /**
   * @brief アクティビティを追加する
   *
   * @param path アクティビティに設定するパス
   * @param activity 追加するアクティビティ
   */
  void add(String path, Activity *activity);

  /**
   * @brief 遷移する
   *
   * @param path 遷移先のパス
   */
  void go(String path);

  /**
   * @brief 状態を更新する
   */
  void update();

  /**
   * @brief アクティビティの状態を更新する
   */
  void updateActivity();

  /**
   * @brief 描画を更新する
   */
  void draw();

  /**
   * @brief 描画を更新する
   */
  void renderScreen();
};
} // namespace hsbs

#endif