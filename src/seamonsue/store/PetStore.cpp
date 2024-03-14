
#include "PetStore.h"

namespace seamonsue {

void PetStore::restore() {
  this->_preferences.begin(this->_namespace, true);

  // 最大寿命
  this->_maxAgeSec = this->_preferences.getULong("maxage", 86400 * random(8, 14));

  // しんでるか
  this->_dead = this->_preferences.getBool("dead", false);

  // モンスの種類
  this->_monsId = this->_preferences.getUChar("mons", 0);

  // 進化形態
  this->_evolutionCount = this->_preferences.getUChar("evolution", 0);

  // パラメータ
  this->_fullup = this->_preferences.getFloat("p_fullup", 0);
  this->_pleasanty = this->_preferences.getFloat("p_pleasanty", 0);
  this->_pretty = this->_preferences.getFloat("p_pretty", 0);

  // カウンター(進化の分岐用パラメータ)
  this->_countGame = this->_preferences.getUShort("c_game", 0);
  this->_countFood = this->_preferences.getUShort("c_food", 0);
  this->_countClean = this->_preferences.getUShort("c_clean", 0);

  this->_preferences.end();
}

void PetStore::save() {
  this->_preferences.begin(this->_namespace, false);

  // 最大寿命
  this->_preferences.putULong("maxage", this->_maxAgeSec);

  // しんでるか
  this->_preferences.putBool("dead", this->_dead);

  // モンスの種類
  this->_preferences.putUChar("mons", this->_monsId);

  // 進化形態
  this->_preferences.putUChar("evolution", this->_evolutionCount);

  // パラメータ
  this->_preferences.putFloat("p_fullup", this->_fullup);
  this->_preferences.putFloat("p_pleasanty", this->_pleasanty);
  this->_preferences.putFloat("p_pretty", this->_pretty);

  // カウンター(進化の分岐用パラメータ)
  this->_preferences.putUShort("c_game", this->_countGame);
  this->_preferences.putUShort("c_food", this->_countFood);
  this->_preferences.putUShort("c_clean", this->_countClean);

  this->_preferences.end();
}

void PetStore::clear() {
  this->_preferences.begin(this->_namespace, false);
  this->_preferences.clear();
  this->_preferences.end();
  this->restore(); // 変数の値も初期値に
}

void PetStore::updatePetParams(long elapsedSec) {

  // たまご
  if (this->_evolutionCount == 0) return;

  const float threeHour = (float)elapsedSec / (10800);
  this->_fullup -= threeHour;
  this->_pleasanty -= threeHour * 0.5;
  this->_pretty -= threeHour;
  // さすがに減りすぎてたら死亡
  if (this->_fullup < -5) this->_dead = true;
  if (this->_pleasanty < -5) this->_dead = true;
  if (this->_pretty < -5) this->_dead = true;
}

void PetStore::updateEvolutionCount(long totalSec) {

  // 最大寿命は８日
  if (totalSec > this->_maxAgeSec) {
    this->_dead = true;
  }

  // 生きてる時間で進化形態を更新
  const int evolutionCount = getEvolutionCountFromTotalSec(totalSec);
  if (evolutionCount == this->_evolutionCount) return;
  this->_evolutionCount = evolutionCount;

  // 進化（最終形態を除いて順番通り固定）
  if (this->_evolutionCount < 5) {
    this->_monsId = this->_evolutionCount;
    return;
  }

  // 最終形態は分岐
  MonsPersonalityData *personality = createPersonalityFromCount(this->_countFood, this->_countGame, this->_countClean);
  this->_monsId = getEvolvuteMonsterId(personality);
  delete personality;
}

bool PetStore::isDead() { return this->_dead; }

unsigned char PetStore::getMonsId() { return this->_monsId; }

unsigned char PetStore::getEvolutionCount() { return this->_evolutionCount; }

float PetStore::getPleasanty() { return this->_pleasanty; }

float PetStore::getPretty() { return this->_pretty; }

float PetStore::getFullup() { return this->_fullup; }

unsigned short PetStore::getCountFood() { return this->_countFood; }

unsigned short PetStore::getCountClean() { return this->_countClean; }

unsigned short PetStore::getCountGame() { return this->_countGame; }

void PetStore::execClean() {
  Serial.println("execClean");
  this->_pretty = this->_pretty < 0 ? 0 : this->_pretty; // 　マイナス値はゼロに

  float backup = this->_pretty;                              // 変数の状態をバックアップ
  this->_countClean++;                                       // カウンタを更新
  this->_pretty = (++this->_pretty) > 5 ? 5 : this->_pretty; // パラメータを更新
  float delta = this->_pretty - backup;                      // 変更量

  if (this->_pleasanty > 0) this->_pleasanty -= delta * 0.25; // 副作用 掃除をすると楽しいことしたくなる
}

void PetStore::execFood() {
  Serial.println("execFood");
  this->_fullup = this->_fullup < 0 ? 0 : this->_fullup; // 　マイナス値はゼロに

  float backup = this->_fullup;                              // 変数の状態をバックアップ
  this->_countFood++;                                        // カウンタを更新
  this->_fullup = (++this->_fullup) > 5 ? 5 : this->_fullup; // パラメータを更新
  float delta = this->_fullup - backup;                      // 変更量

  if (this->_pretty > 0) this->_pretty -= delta * 0.25; // 副作用 エサをあげたら水槽が汚れる
}

void PetStore::execGame() {
  Serial.println("execGame");
  this->_pleasanty = this->_pleasanty < 0 ? 0 : this->_pleasanty; // 　マイナス値はゼロに

  float backup = this->_pleasanty;                                    // 変数の状態をバックアップ
  this->_countGame += 1.25;                                           // カウンタを更新(ゲームは他の２つより大変なのでやや補正値)
  this->_pleasanty = (++this->_pleasanty) > 5 ? 5 : this->_pleasanty; // パラメータを更新
  float delta = this->_pleasanty - backup;                            // 変更量

  if (this->_fullup > 0) this->_fullup -= delta * 0.25; // 副作用 遊んだらお腹が減る
}

} // namespace seamonsue
