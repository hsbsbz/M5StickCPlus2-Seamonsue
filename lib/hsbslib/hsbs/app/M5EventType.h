#ifndef _HSBS__APP__M5EVENT_TYPE_H_INCLUDE_
#define _HSBS__APP__M5EVENT_TYPE_H_INCLUDE_

#include "hsbs/core/ObjectList.h"
#include "hsbs/tween/Ease.h"
#include <M5Unified.h>

namespace hsbs {

/**
 * @brief スリープの直前
 */
static const char *EVENT_BEFORE_SLEEP = "m5_before_sleep";

/**
 * @brief Aボタンを押下
 */
static const char *EVENT_BUTTON_PRESS_A = "m5_button_press_a";

/**
 * @brief Bボタンを押下
 */
static const char *EVENT_BUTTON_PRESS_B = "m5_button_press_b";

/**
 * @brief Cボタンを押下
 */
static const char *EVENT_BUTTON_PRESS_C = "m5_button_press_c";

/**
 * @brief Aボタンを離した
 */
static const char *EVENT_BUTTON_RELEASE_A = "m5_button_release_a";

/**
 * @brief Bボタンを離した
 */
static const char *EVENT_BUTTON_RELEASE_B = "m5_button_release_b";

/**
 * @brief Cボタンを離した
 */
static const char *EVENT_BUTTON_RELEASE_C = "m5_button_release_c";

/**
 * @brief Aボタンを長押し
 */
static const char *EVENT_BUTTON_LONG_PRESS_A = "m5_button_long_press_a";

/**
 * @brief Bボタンを長押し
 */
static const char *EVENT_BUTTON_LONG_PRESS_B = "m5_button_long_press_b";

/**
 * @brief Cボタンを長押し
 */
static const char *EVENT_BUTTON_LONG_PRESS_C = "m5_button_long_press_c";

/**
 * @brief 毎フレーム
 */
static const char *EVENT_ENTER_FRAME = "m5_enterframe";

} // namespace hsbs

#endif
