#ifndef _SEAMONSUE__DATA__MONS_DATA_H_INCLUDE_
#define _SEAMONSUE__DATA__MONS_DATA_H_INCLUDE_

#include "../../image_progmem.h"
#include <Arduino.h>

namespace seamonsue {

struct ImgData {
  const uint8_t *data;
  u_int8_t width;
  u_int8_t height;
  int8_t x;
  int8_t y;
};

struct MonsPersonalityData {
  unsigned char food;
  unsigned char game;
  unsigned char clean;
};

struct MonsData {
  ImgData walk0;
  ImgData walk1;
  ImgData action;
  MonsPersonalityData personality;
};

} // namespace seamonsue

/**
 * @brief モンス情報
 */
static seamonsue::MonsData monsDataList[13] = {
    // 0 卵
    {{Img::Mono::c0_0, Img::Mono::c0_0Width, Img::Mono::c0_0Height, 0, -10},
     {Img::Mono::c0_1, Img::Mono::c0_1Width, Img::Mono::c0_1Height, 0, -12},
     {Img::Mono::c0_1, Img::Mono::c0_1Width, Img::Mono::c0_1Height, 0, -12},
     {0, 0, 0}}, // food, game, clean

    // 1 赤ちゃん 1
    {{Img::Mono::c1_0, Img::Mono::c1_0Width, Img::Mono::c1_0Height, 0, -8},
     {Img::Mono::c1_1, Img::Mono::c1_1Width, Img::Mono::c1_1Height, 0, -8},
     {Img::Mono::c1_2, Img::Mono::c1_2Width, Img::Mono::c1_2Height, 0, -10},
     {0, 0, 0}}, // food, game, clean

    // 2 赤ちゃん 2
    {{Img::Mono::c2_0, Img::Mono::c2_0Width, Img::Mono::c2_0Height, 0, -7},
     {Img::Mono::c2_1, Img::Mono::c2_1Width, Img::Mono::c2_1Height, 0, -8},
     {Img::Mono::c2_2, Img::Mono::c2_2Width, Img::Mono::c2_2Height, 0, -9},
     {0, 0, 0}}, // food, game, clean

    // 3 子供 1
    {{Img::Mono::c3_0, Img::Mono::c3_0Width, Img::Mono::c3_0Height, 0, -5},
     {Img::Mono::c3_1, Img::Mono::c3_1Width, Img::Mono::c3_1Height, 0, -6},
     {Img::Mono::c3_2, Img::Mono::c3_2Width, Img::Mono::c3_2Height, 0, -7},
     {0, 0, 0}}, // food, game, clean

    // 4 子供 2
    {{Img::Mono::c4_0, Img::Mono::c4_0Width, Img::Mono::c4_0Height, 0, -4},
     {Img::Mono::c4_1, Img::Mono::c4_1Width, Img::Mono::c4_1Height, 0, -5},
     {Img::Mono::c4_2, Img::Mono::c4_2Width, Img::Mono::c4_2Height, 0, -8},
     {0, 0, 0}}, // food, game, clean

    // 5 大人 (ノーマル)
    // 平均的なやつ
    {{Img::Mono::c5_0, Img::Mono::c5_0Width, Img::Mono::c5_0Height, 0, -2},
     {Img::Mono::c5_1, Img::Mono::c5_1Width, Img::Mono::c5_1Height, 0, -3},
     {Img::Mono::c5_2, Img::Mono::c5_2Width, Img::Mono::c5_2Height, 0, -4},
     {0, 0, 0}},

    // 6 大人（マッチョ）
    // ゲームに一番偏ったやつ
    {{Img::Mono::c6_0, Img::Mono::c6_0Width, Img::Mono::c6_0Height, 0, -1},
     {Img::Mono::c6_1, Img::Mono::c6_1Width, Img::Mono::c6_1Height, 0, -1},
     {Img::Mono::c6_2, Img::Mono::c6_2Width, Img::Mono::c6_2Height, 0, -2},
     {0, 1, 0}}, // food, game, clean

    // 7 大人（斜め）
    {{Img::Mono::c7_0, Img::Mono::c7_0Width, Img::Mono::c7_0Height, 0, -4},
     {Img::Mono::c7_1, Img::Mono::c7_1Width, Img::Mono::c7_1Height, 0, -4},
     {Img::Mono::c7_2, Img::Mono::c7_2Width, Img::Mono::c7_2Height, 0, -5},
     {1, 0, 1}}, // food, game, clean

    // 8 大人（肥満）
    {{Img::Mono::c8_0, Img::Mono::c8_0Width, Img::Mono::c8_0Height, 0, -4},
     {Img::Mono::c8_1, Img::Mono::c8_1Width, Img::Mono::c8_1Height, 0, -4},
     {Img::Mono::c8_2, Img::Mono::c8_2Width, Img::Mono::c8_2Height, 0, -5},
     {1, 0, 0}}, // food, game, clean

    // 9 大人（人型）
    // 清潔
    {{Img::Mono::c9_0, Img::Mono::c9_0Width, Img::Mono::c9_0Height, 0, -1},
     {Img::Mono::c9_1, Img::Mono::c9_1Width, Img::Mono::c9_1Height, 1, -1},
     {Img::Mono::c9_2, Img::Mono::c9_2Width, Img::Mono::c9_2Height, 0, -2},
     {0, 0, 1}}, // food, game, clean

    // 10 大人（黒）
    // 不清潔
    {{Img::Mono::c10_0, Img::Mono::c10_0Width, Img::Mono::c10_0Height, 0, -2},
     {Img::Mono::c10_1, Img::Mono::c10_1Width, Img::Mono::c10_1Height, 1, -2},
     {Img::Mono::c10_2, Img::Mono::c10_2Width, Img::Mono::c10_2Height, 1, -3},
     {1, 1, 0}}, // food, game, clean

    // 11 大人（目デカ）
    {{Img::Mono::c11_0, Img::Mono::c11_0Width, Img::Mono::c11_0Height, 0, -4},
     {Img::Mono::c11_1, Img::Mono::c11_1Width, Img::Mono::c11_1Height, 0, -5},
     {Img::Mono::c11_2, Img::Mono::c11_2Width, Img::Mono::c11_2Height, 0, -7},
     {0, 1, 1}}, // food, game, clean

    // 12 大人（ヒラヒラ）
    {{Img::Mono::c12_0, Img::Mono::c12_0Width, Img::Mono::c12_0Height, 0, -4},
     {Img::Mono::c12_1, Img::Mono::c12_1Width, Img::Mono::c12_1Height, 0, -5},
     {Img::Mono::c12_2, Img::Mono::c12_2Width, Img::Mono::c12_2Height, 0, -7},
     {0, 0, 0}}}; // food, game, clean

/**
 * @brief 総時間から進化形態の段階を返却
 *
 * @param totalSec
 * @return unsigned char
 */
static unsigned char getEvolutionCountFromTotalSec(long totalSec) {
  const int min = totalSec / 60;
  const int hour = totalSec / 3600;
  const int day = totalSec / 86400;
  if (min < 1) return 0;  // 1分未満は 卵
  if (hour < 6) return 1; // 12時間未満は 赤ちゃん１
  if (day < 1) return 2;  // 1日未満は 赤ちゃん２
  if (day < 3) return 3;  // 3日未満は 子供１
  if (day < 5) return 4;  // 5日未満は 子供２
  return 5;               // 大人
}

/**
 * @brief プレイヤーが操作したカウンタからパーソナリティデータを作成する
 *
 * @param countFood
 * @param countGame
 * @param countClean
 * @return seamonsue::MonsPersonalityData*
 */
static seamonsue::MonsPersonalityData *createPersonalityFromCount(float countFood, float countGame, float countClean) {
  float minCount = INT_MAX;
  minCount = minCount < countFood ? minCount : countFood;
  minCount = minCount < countGame ? minCount : countGame;
  minCount = minCount < countClean ? minCount : countClean;

  countFood -= minCount;
  countGame -= minCount;
  countClean -= minCount;

  float maxCount = 0;
  maxCount = maxCount > countFood ? maxCount : countFood;
  maxCount = maxCount > countGame ? maxCount : countGame;
  maxCount = maxCount > countClean ? maxCount : countClean;

  countFood /= maxCount;
  countGame /= maxCount;
  countClean /= maxCount;

  countFood = std::round(countFood);
  countGame = std::round(countGame);
  countClean = std::round(countClean);

  // パーソナリティデータを作成
  seamonsue::MonsPersonalityData *data = new seamonsue::MonsPersonalityData();
  data->food = countFood;
  data->game = countGame;
  data->clean = countClean;
  return data;
}

/**
 * @brief パーソナリティデータから 6~11 までのパターンを作成
 *
 * @param personality
 * @return int
 */
static int getMonsIdFromPersonality(seamonsue::MonsPersonalityData *personality) {
  // 残りはパラメータをみて一番近いもの
  int beginIndex = 6;
  int endIndex = 11;
  int minDiff = INT_MAX;
  unsigned char nextMonsId = beginIndex;
  seamonsue::MonsPersonalityData *a = personality;
  for (int i = beginIndex; i <= endIndex; i++) {
    seamonsue::MonsPersonalityData b = monsDataList[i].personality;
    int diff = abs(a->food - b.food) + abs(a->game - b.game) + abs(a->clean - b.clean);
    if (diff < minDiff) {
      minDiff = diff;
      nextMonsId = i;
    }
  }
  return nextMonsId;
}

/**
 * @brief 進化形態を取得する 5~12 (5 と 12 はランダムに出現)
 *
 * @param personality
 * @return int
 */
static int getEvolvuteMonsterId(seamonsue::MonsPersonalityData *personality) {
  // 最も近いモンスターのインデックス
  int minDiff = INT_MAX;
  unsigned char nextMonsId = 6;
  seamonsue::MonsPersonalityData *a = personality;

  int rand = random(0, 100);

  // 2 % の確立でレア
  if (rand < 2) {
    return 12;
  }

  // 15 % の確立でノーマル
  if (rand < 17) {
    return 5;
  }

  // 残りはパラメータをみて一番近いもの
  return getMonsIdFromPersonality(personality);
}

#endif