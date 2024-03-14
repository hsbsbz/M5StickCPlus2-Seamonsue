#ifndef _HSBS__DISPLAY__BITMAP_MONO_H_INCLUDE_
#define _HSBS__DISPLAY__BITMAP_MONO_H_INCLUDE_

#include "DisplayObject.h"
#include <M5StickCPlus2.h>

namespace hsbs {
/**
 * @class BitmapMono
 * @brief モノクロのビットマップを表示リストで扱うためのラッパー
 */
class BitmapMono : public DisplayObject {

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
   * @brief Construct a new Bitmap Mono object
   *
   * @param data
   * @param width
   * @param height
   */
  BitmapMono(const uint8_t *data, uint16_t width, uint16_t height);

  /**
   * @brief 描画
   */
  virtual void draw(M5Canvas *targetCanvas) override;

  /**
   * @brief デストラクタ
   *
   */
  virtual ~BitmapMono();
};
} // namespace hsbs

#endif