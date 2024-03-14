#ifndef _SEAMONSUE__GLOBAL_H_INCLUDE_
#define _SEAMONSUE__GLOBAL_H_INCLUDE_

#include "../image_progmem.h"
#include "data/MonsData.h"
#include "hsbs/core/Ticker.h"
#include "hsbs/geom/Rectangle.h"
#include "media/SoundUtil.h"
#include "store/GameStore.h"
#include "store/PetStore.h"
#include "store/TimeStore.h"

static const int S_MINUTE = 60;
static const int S_HOUR = 3600;
static const int S_DAY = 86400;

/**
 * 一定の間隔を開けて実行するためのユーティリティ
 */
static hsbs::Ticker globalTicker;

/**
 * 音を鳴らすユーティリティ
 */
static seamonsue::SoundUtil soundUtil;

/**
 * ゲームの状態
 */
static seamonsue::GameStore gameStore;

/**
 * @brief モンスの状態
 *
 */
static seamonsue::PetStore petStore;

/**
 * @brief 経過時間
 */
static seamonsue::TimeStore timeStore;

/**
 * @brief 液晶の領域
 */
static hsbs::Rectangle dotAreaRect(34, 0, 172, 135);

#endif