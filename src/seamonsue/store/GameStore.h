#ifndef _SEAMONSUE__STORE__GAME_STORE_H_INCLUDE_
#define _SEAMONSUE__STORE__GAME_STORE_H_INCLUDE_

#include "Preferences.h"

namespace seamonsue {

enum GameState {
  /**
   * @brief タイトル
   */
  TITLE = 0,

  /**
   * @brief プレイ中
   */
  PLAY = 1,

  /**
   * @brief 死亡
   */
  DEAD = 2
};

class GameStore {
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
   * @brief ゲームの状態
   *
   */
  GameState _gameState;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief ゲームの状態
   *
   * @return GameState
   */
  GameState getGameState();

  /**
   * @brief ストレージからデータを読み出す
   */
  void restore();

  /**
   * @brief ストレージにデータを書き込む
   */
  void save();

  /**
   * @brief タイトルから育成を開始する
   */
  void startGame();

  /**
   * @brief しんでる
   */
  void dead();

  /**
   * @brief セーブデータを削除
   */
  void clear();
};

} // namespace seamonsue

#endif
