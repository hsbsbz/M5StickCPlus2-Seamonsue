
#include "GameStore.h"

namespace seamonsue {

void GameStore::restore() {
  this->_preferences.begin(this->_namespace, true);
  this->_gameState = (GameState)this->_preferences.getInt("game_state", (int)TITLE);
  this->_muted = this->_preferences.getBool("muted", false);
  this->_preferences.end();
}

void GameStore::save() {
  this->_preferences.begin(this->_namespace, false);
  this->_preferences.putInt("game_state", (int)this->_gameState);
  this->_preferences.putBool("muted", this->_muted);
  this->_preferences.end();
}

GameState GameStore::getGameState() {
  return this->_gameState;
}

bool GameStore::getMuted() {
  return this->_muted;
}

void GameStore::startGame() {
  this->_gameState = PLAY;
  this->_preferences.begin(this->_namespace, false);
  this->_preferences.putInt("game_state", (int)this->_gameState);
  this->_preferences.end();
}

void GameStore::dead() {
  this->_gameState = DEAD;
  this->_preferences.begin(this->_namespace, false);
  this->_preferences.putInt("game_state", (int)this->_gameState);
  this->_preferences.end();
}

void GameStore::clear() {
  this->_preferences.begin(this->_namespace, false);
  this->_preferences.clear();
  this->_preferences.end();
  this->restore(); // 変数の値も初期値に
}

void GameStore::toggleMute() {
  this->_muted = !this->_muted;
}


} // namespace seamonsue
