
#ifndef _HSBS__DISPLAY__DISPLAY_OBJECT_H_INCLUDE_
#define _HSBS__DISPLAY__DISPLAY_OBJECT_H_INCLUDE_

#include "../core/ObjectList.h"
#include "../geom/Rectangle.h"
#include "../geom/Transform.h"
#include <Arduino.h>
#include <M5StickCPlus2.h>

namespace hsbs {
/**
 * @class DisplayObject
 * @brief 表示オブジェクト。アフィン変換用の行列を操作するためのプロパティを保有。
 */
class DisplayObject {
private:
  //------------------------------
  // Private
  //------------------------------
protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * @brief アフィン変換用のトランスフォーム(親のコンテナを合算)
   */
  Transform globalTransform;

  /**
   * @brief 描画直前にクリップを適用するための関数
   *
   * @param canvas
   */
  void setClipRectToParentCanvas(M5Canvas *canvas);

  /**
   * @brief 描画直後にクリップを解除するための関数
   *
   * @param canvas
   */
  void resetClipRectToParentCanvas(M5Canvas *canvas);

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief アフィン変換用のトランスフォーム
   */
  Transform transform;

  /**
   * @brief 表示/非表示フラグ
   */
  bool visible = true;

  /**
   * @brief 表示位置 X
   */
  float x = 0;

  /**
   * @brief 表示位置 Y
   */
  float y = 0;

  /**
   * @brief 縮尺 X
   */
  float scaleX = 1;

  /**
   * @brief 縮尺 Y
   */
  float scaleY = 1;

  /**
   * @brief 回転（ラジアン角）
   */
  float rotation = 0;

  /**
   * @brief 基準点X
   */
  float anchorX = 0;

  /**
   * @brief 基準点Y
   */
  float anchorY = 0;

  /**
   * @brief 傾斜X
   */
  float skewX = 0;

  /**
   * @brief 傾斜Y
   */
  float skewY = 0;

  /**
   * @brief 透過ピクセルカラー
   */
  int transparentColor = -1;

  /**
   * @brief 描画領域（親の Canvas 座標）
   */
  Rectangle *clipRect = nullptr;

  /**
   * @brief 親表示オブジェクト
   */
  DisplayObject *parent = nullptr;

  /**
   * @brief 縮尺を設定
   *
   * @param x
   * @param y
   * @return 自身のポインタ
   */
  DisplayObject *setScale(float x, float y);

  /**
   * @brief 位置を設定
   *
   * @param x
   * @param y
   * @return 自身のポインタ
   */
  DisplayObject *setPosition(float x, float y);

  /**
   * @brief 傾きを設定
   *
   * @param x
   * @param y
   * @return 自身のポインタ
   */
  DisplayObject *setSkew(float x, float y);

  /**
   * @brief 回転角度を設定(ラジアン角)
   *
   * @param angle
   * @return 自身のポインタ
   */
  DisplayObject *setRotation(float angle);

  /**
   * @brief 回転角度を設定(360°)
   *
   * @param deg
   * @return 自身のポインタ
   */
  DisplayObject *setDeg(float deg);

  /**
   * @brief 基準点を設定
   *
   * @param x
   * @param y
   * @return 自身のポインタ
   */
  DisplayObject *setAnchor(float x, float y);

  /**
   * @brief トランスフォームを更新する
   *
   * @param parentTransform
   */
  virtual void updateTransform(Transform *parentTransform);

  /**
   * @brief 描画
   */
  virtual void draw(M5Canvas *targetCanvas);

  /**
   * @brief デストラクタ
   */
  virtual ~DisplayObject();
};
} // namespace hsbs

#endif