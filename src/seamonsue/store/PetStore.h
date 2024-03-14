#ifndef _SEAMONSUE__STORE__PET_STORE_H_INCLUDE_
#define _SEAMONSUE__STORE__PET_STORE_H_INCLUDE_

#include "../data/MonsData.h"
#include "Preferences.h"

namespace seamonsue {

class PetStore {
private:
  //------------------------------
  // Private
  //------------------------------
  Preferences _preferences;

  /**
   * @brief 名前空間
   */
  const char *_namespace = "seamons_game_v1";

  /**
   * @brief 種類
   */
  unsigned char _monsId;

  /**
   * @brief 進化した数
   */
  unsigned char _evolutionCount;

  /**
   * @brief おなか一杯
   */
  float _fullup;

  /**
   * @brief 綺麗
   */
  float _pretty;

  /**
   * @brief 楽しい
   */
  float _pleasanty;

  /**
   * @brief しんでる
   */
  bool _dead;

  /**
   * @brief 寿命
   *
   */
  long _maxAgeSec;

  /**
   * @brief プレイヤーがユーザーがゲームした数
   */
  unsigned short _countGame;

  /**
   * @brief プレイヤーがユーザーがエサをあげた数
   */
  unsigned short _countFood;

  /**
   * @brief プレイヤーが掃除した数
   */
  unsigned short _countClean;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief ストレージからデータを読み出す
   */
  void restore();

  /**
   * @brief ストレージにデータを書き込む
   */
  void save();

  /**
   * @brief セーブデータを削除
   */
  void clear();

  /**
   * @brief 種類
   */
  unsigned char getMonsId();

  /**
   * @brief 種類
   */
  unsigned char getEvolutionCount();

  /**
   * @brief しんでる
   */
  bool isDead();

  /**
   * @brief おなか一杯
   */
  float getFullup();

  /**
   * @brief 楽しい
   */
  float getPleasanty();

  /**
   * @brief 綺麗
   */
  float getPretty();

  /**
   * @brief エサをあげた回数
   */
  unsigned short getCountFood();

  /**
   * @brief 掃除した回数
   */
  unsigned short getCountClean();

  /**
   * @brief 遊んだ回数
   */
  unsigned short getCountGame();

  /**
   * @brief 掃除をした
   */
  void execClean();

  /**
   * @brief 食事をした
   */
  void execFood();

  /**
   * @brief ゲームをした
   */
  void execGame();

  /**
   * @brief 経過時間をもとにパラメータを更新する
   *
   * @param elapsedSec
   */
  void updatePetParams(long elapsedSec);

  /**
   * @brief 総時間をみて進化形態を更新する
   *
   * @param totalSec
   */
  void updateEvolutionCount(long totalSec);

  /**
   * パーソナリティの一番近いモンスを取得
   * @param totalSec
   * @return unsigned char
   */
  unsigned char getMonsIdByPersonality(MonsPersonalityData *data);
};

} // namespace seamonsue

#endif
