
#ifndef _HSBS__DISPLAY__BITMAP565_H_INCLUDE_
#define _HSBS__DISPLAY__BITMAP565_H_INCLUDE_

#include "DisplayObject.h"
#include <M5StickCPlus2.h>

namespace hsbs {
/**
 * @class Bitmap565
 * @brief RGB565 Bitmap を表示リストで扱うためのラッパー
 */
class Bitmap565 : public DisplayObject {

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
   */
  M5Canvas canvas;

  /**
   * @brief 画像サイズ横
   */
  uint16_t width;

  /**
   * @brief 画像サイズ高さ
   */
  uint16_t height;

  /**
   * @brief Construct a new Bitmap 5 6 5 object
   *
   * @param data
   * @param width
   * @param height
   */
  Bitmap565(const unsigned short *data, uint16_t width, uint16_t height);

  /**
   * @brief 描画
   */
  virtual void draw(M5Canvas *targetCanvas) override;

  /**
   * @brief デストラクタ
   *
   */
  virtual ~Bitmap565();
};
} // namespace hsbs

#endif