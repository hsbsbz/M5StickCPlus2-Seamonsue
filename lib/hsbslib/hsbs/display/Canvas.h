

#ifndef _HSBS__DISPLAY__CANVAS_H_INCLUDE_
#define _HSBS__DISPLAY__CANVAS_H_INCLUDE_

#include "DisplayObject.h"
#include <M5StickCPlus2.h>

namespace hsbs {

/**
 * @class Canvas
 * @brief M5Canvas を表示リストで扱うためのラッパー
 */
class Canvas : public DisplayObject {

protected:
  //------------------------------
  // Protected
  //------------------------------
public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief 描画用のキャンバス
   *
   */
  M5Canvas canvas;
  uint16_t width;
  uint16_t height;

  /**
   * @brief 透過ピクセルカラー
   *
   */
  int transparentColor = -1;

  /**
   * @brief Construct a new Canvas object
   *
   * @param width
   * @param height
   */
  Canvas(uint16_t width, uint16_t height);
  virtual ~Canvas();

  /**
   * @brief 描画
   */
  virtual void draw(M5Canvas *targetCanvas) override;
};
} // namespace hsbs

#endif