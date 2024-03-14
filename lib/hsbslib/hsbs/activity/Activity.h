#ifndef _HSBS__ACTIVITY__ACTIVITY_H_INCLUDE_
#define _HSBS__ACTIVITY__ACTIVITY_H_INCLUDE_

#include <Arduino.h>
#include <M5StickCPlus2.h>

#include "../display/DisplayObjectContainer.h"
#include "../tween/Tween.h"

namespace hsbs {

// 前方宣言
class ActivityRooter;

/**
 * @class Activity
 * @brief ActivityRooter に登録して使用する。アクティブ時、非アクティブ時、毎フレーム時のコールバック関数。トランジション用のトゥイーンプロパティを保有。
 */
class Activity {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * アクティブ状態
   */
  bool _isActive = false;

  /**
   * 実行中かどうかを示すフラグ
   */
  bool _running = false;

  /**
   * @brief 一度でもアクティブになったか
   */
  bool _inited = false;

  /**
   * 自身のパス
   */
  String _path = "";

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * @brief 所属する親のルーター
   */
  ActivityRooter *root = nullptr;

  /**
   * @brief 初回アクティブ時（onActive の直前）のコールバック関数
   */
  virtual void onInit();

  /**
   * @brief アクティブ時のコールバック関数
   */
  virtual void onActive();

  /**
   * @brief 非アクティブ時のコールバック関数
   */
  virtual void onDeactive();

  /**
   * @brief フレーム更新時のコールバック関数
   *
   */
  virtual void onEnterFrame();

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief 表示リストの親コンテナ
   */
  DisplayObjectContainer stage;

  /**
   * @brief トランジションが実行中か評価
   *
   * @return 実行中なら true そうでなければ false を返却する
   */
  bool running();

  /**
   * @brief アクティブ状態か評価
   *
   * @return アクティブ状態なら true そうでなければ false を返却する
   */
  bool isActive();

  /**
   * @brief パスが正確に一致しているか評価
   *
   * @return 一致なら true そうでなければ false を返却する
   */
  bool isExact();

  /**
   * @brief アクティブにする
   */
  void active();

  /**
   * @brief 非アクティブにする
   */
  void deactive();

  /**
   * @brief トランジションの状態を更新する
   */
  void updateTransition();

  /**
   * @brief フレームを更新する
   */
  void update();

  /**
   * @brief 設定されている自身のパスを取得する

   * @return 設定されている文字列
   */
  String getPath();

  /**
   * @brief 自身のパスを設定する
   *
   * @param path 設定するパス
   */
  void setPath(String path);

  /**
   * @brief 所属するルーターの参照を設定する
   *
   * @param root 設定する親ルーター
   */
  void setRoot(ActivityRooter *root);

  /**
   * @brief 表示状態を取得する。
   * @return アクティブ時、または非アクティブ時のトランジション中は true
   */
  bool visiblity();

  /**
   * @brief 遷移する
   *
   * @param path 遷移先のパス
   */
  void go(String path);

  /**
   * @brief ルーターの現在のパスを取得する
   *
   * @return String
   */
  String getRootPath();

  /**
   * @brief アクティブ時のトランジション
   */
  Tween activeTransition;

  /**
   * @brief 非アクティブ時のトランジション
   */
  Tween deactiveTransition;
};
} // namespace hsbs

#endif