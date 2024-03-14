

#ifndef _SEAMONSUE__DISPLAY__GAME_CONTAINER_H_INCLUDE_
#define _SEAMONSUE__DISPLAY__GAME_CONTAINER_H_INCLUDE_

#include "../../image_progmem.h"
#include "../global.h"
#include "../media/SoundUtil.h"
#include "hsbs/core/ObjectList.h"
#include "hsbs/core/Ticker.h"
#include "hsbs/display/BitmapMono.h"
#include "hsbs/display/DisplayObjectContainer.h"
#include "hsbs/geom/Point.h"
#include <Arduino.h>

namespace seamonsue {

class GameContainer : public hsbs::DisplayObjectContainer {

protected:
  //------------------------------
  // Protected
  //------------------------------
  hsbs::Rectangle *_playerRect;
  hsbs::ObjectList<hsbs::Rectangle *> _fishList;
  hsbs::ObjectList<hsbs::Rectangle *> _heartList;
  hsbs::BitmapMono *_fishBitmap;
  hsbs::BitmapMono *_heartBitmap0;
  hsbs::BitmapMono *_heartBitmap1;
  hsbs::BitmapMono *_playerBitmap0;
  hsbs::BitmapMono *_playerBitmap1;
  hsbs::BitmapMono *_smallHeartBitmap0;
  hsbs::BitmapMono *_smallHeartBitmap1;

  const int dotScreenX = 34;
  const int maxWidth = 43 - 7;
  const int maxHeight = 34;

  int value = 0;
  float playerVelocity = 0;
  int waitCount = 0;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief コンストラクタ
   */
  GameContainer() {
    this->_playerRect = new hsbs::Rectangle((maxWidth - Img::Mono::game_player0Width) >> 1, maxHeight - Img::Mono::game_player0Height, Img::Mono::game_player0Width, Img::Mono::game_player0Height);

    this->_fishBitmap = new hsbs::BitmapMono(Img::Mono::game_fish, Img::Mono::game_fishWidth, Img::Mono::game_fishHeight);
    this->_fishBitmap->setScale(4, 4);

    this->_heartBitmap0 = new hsbs::BitmapMono(Img::Mono::game_heart0, Img::Mono::game_heart0Width, Img::Mono::game_heart0Height);
    this->_heartBitmap0->setScale(4, 4);
    this->_heartBitmap1 = new hsbs::BitmapMono(Img::Mono::game_heart1, Img::Mono::game_heart1Width, Img::Mono::game_heart1Height);
    this->_heartBitmap1->setScale(4, 4);

    this->_playerBitmap0 = new hsbs::BitmapMono(Img::Mono::game_player0, Img::Mono::game_player0Width, Img::Mono::game_player0Height);
    this->_playerBitmap0->setScale(4, 4);
    this->_playerBitmap1 = new hsbs::BitmapMono(Img::Mono::game_player1, Img::Mono::game_player1Width, Img::Mono::game_player1Height);
    this->_playerBitmap1->setScale(4, 4);

    this->_smallHeartBitmap0 = new hsbs::BitmapMono(Img::Mono::game_heart_s0, Img::Mono::game_heart_s0Width, Img::Mono::game_heart_s0Height);
    this->_smallHeartBitmap0->setScale(4, 4);
    this->_smallHeartBitmap1 = new hsbs::BitmapMono(Img::Mono::game_heart_s1, Img::Mono::game_heart_s1Width, Img::Mono::game_heart_s1Height);
    this->_smallHeartBitmap1->setScale(4, 4);
  }

  /**
   * @brief デストラクタ
   */
  virtual ~GameContainer() {
    delete this->_smallHeartBitmap0;
    delete this->_smallHeartBitmap1;
    delete this->_fishBitmap;
    delete this->_heartBitmap0;
    delete this->_heartBitmap1;
    delete this->_playerBitmap0;
    delete this->_playerBitmap1;
    delete this->_playerRect;
    while (this->_fishList.length()) {
      delete this->_fishList.pop();
    }
    while (this->_heartList.length()) {
      delete this->_heartList.pop();
    }
  }

  /**
   * @brief ゲームが終了しているか
   */
  bool completed() {
    return this->value >= 5 && this->waitCount == 0;
  }

  /**
   * @brief ハートと魚をすべて消す
   */
  void removeHeartAndFish() {
    while (this->_fishList.length()) {
      delete this->_fishList.pop();
    }
    while (this->_heartList.length()) {
      delete this->_heartList.pop();
    }
  }

  /**
   * @brief ゲームを更新する
   */
  void update() {
    // 待機フレームは何もしない
    if (this->waitCount > 0) {
      --this->waitCount;
      this->playerVelocity = 0; // キャラクタが正面を向く
      return;
    }

    // 加速度センサを更新
    StickCP2.Imu.update();
    auto data = StickCP2.Imu.getImuData();

    // プレイヤーの位置を更新
    int xMax = maxWidth - Img::Mono::game_player0Width;
    this->playerVelocity = data.accel.y * 20;
    this->_playerRect->x += this->playerVelocity;
    this->_playerRect->x = this->_playerRect->x < 0 ? 0 : this->_playerRect->x;
    this->_playerRect->x = this->_playerRect->x > xMax ? xMax : this->_playerRect->x;

    // 一定の間隔で、魚かハートを追加
    if (globalTicker.checkInterval(1300)) {
      if (random(0, 3) == 0) {
        this->_heartList.push(new hsbs::Rectangle(random(0, maxWidth - Img::Mono::game_heart0Width), -Img::Mono::game_heart0Height, Img::Mono::game_heart0Width, Img::Mono::game_heart0Height));
      } else {
        this->_fishList.push(new hsbs::Rectangle(random(0, maxWidth - Img::Mono::game_fishWidth), -Img::Mono::game_fishHeight, Img::Mono::game_fishWidth, Img::Mono::game_fishHeight));
      }
    }

    // 魚
    for (int i = this->_fishList.length() - 1; i >= 0; i--) {
      hsbs::Rectangle *fish = this->_fishList.getAt(i);

      fish->y += 2;

      if (this->hitTest(this->_playerRect, fish, 3)) {
        // プレイヤーと衝突
        this->value = 0;
        this->waitCount = 15;
        soundUtil.gameHitFish();
        this->removeHeartAndFish();
      } else if (fish->y > maxHeight) {
        // 画面外
        this->_fishList.remove(fish);
        delete fish;
      }
    }

    // ハート
    for (int i = this->_heartList.length() - 1; i >= 0; i--) {
      hsbs::Rectangle *heart = this->_heartList.getAt(i);

      heart->y += 2;

      if (this->hitTest(this->_playerRect, heart, 2)) {
        // プレイヤーと衝突
        ++this->value;
        if (this->value == 5) {
          this->waitCount = 15;
        }
        soundUtil.gameHitHeart();
        this->_heartList.remove(heart);
        delete heart;
      } else if (heart->y > maxHeight) {
        // 画面外
        this->value = --this->value < 0 ? 0 : this->value;
        soundUtil.gameHitFish();
        this->_heartList.remove(heart);
        delete heart;
      }
    }
  }

  /**
   * @brief 矩形の当たり判定
   *
   * @param a
   * @param b
   * @param padding
   * @return true
   * @return false
   */
  bool hitTest(hsbs::Rectangle *a, hsbs::Rectangle *b, int padding) {
    return (a->x + padding < b->x + b->width) &&
           (b->x + padding < a->x + a->width) &&
           (a->y + padding < b->y + b->height) &&
           (b->y + padding < a->y + a->height);
  }

  void draw(M5Canvas *targetCanvas) override {

    long now = millis();

    // 魚の描画
    bool fishReflect = (now / 250) % 2;
    for (int i = 0; i < this->_fishList.length(); i++) {
      hsbs::Rectangle *fish = this->_fishList.getAt(i);
      if (fishReflect) {
        this->_fishBitmap->scaleX = -4;
        this->_fishBitmap->x = ((int)(fish->x + Img::Mono::game_fishWidth) << 2) + dotScreenX;
      } else {
        this->_fishBitmap->scaleX = 4;
        this->_fishBitmap->x = ((int)fish->x << 2) + dotScreenX;
      }
      this->_fishBitmap->y = ((int)fish->y << 2);
      this->_fishBitmap->updateTransform(nullptr);
      this->_fishBitmap->canvas.pushAffine(targetCanvas, this->_fishBitmap->transform.matrix, this->_fishBitmap->transparentColor);
    }

    // ハート描画
    bool heartFrame = ((now / 150) % 3) == 0;
    for (int i = 0; i < this->_heartList.length(); i++) {
      hsbs::Rectangle *heart = this->_heartList.getAt(i);
      hsbs::BitmapMono *heartBitmap = heartFrame ? this->_heartBitmap1 : this->_heartBitmap0;
      heartBitmap->x = ((int)heart->x << 2) + dotScreenX;
      heartBitmap->y = (int)heart->y << 2;
      heartBitmap->updateTransform(nullptr);
      heartBitmap->canvas.pushAffine(targetCanvas, heartBitmap->transform.matrix, heartBitmap->transparentColor);
    }

    // プレイヤー描画
    bool playerFrame = (now / 100) % 2;
    bool playerIsFast = (abs(this->playerVelocity) > 1);
    bool playerReflect = this->playerVelocity > 0;
    hsbs::BitmapMono *playerBitmap = playerIsFast ? this->_playerBitmap1 : this->_playerBitmap0;
    if (playerReflect) {
      playerBitmap->scaleX = -4;
      playerBitmap->x = ((int)(this->_playerRect->x + Img::Mono::game_player0Width) << 2) + dotScreenX;
    } else {
      playerBitmap->scaleX = 4;
      playerBitmap->x = ((int)this->_playerRect->x << 2) + dotScreenX;
    }
    playerBitmap->y = (int)(this->_playerRect->y + playerFrame) << 2;
    playerBitmap->updateTransform(nullptr);
    playerBitmap->canvas.pushAffine(targetCanvas, playerBitmap->transform.matrix, playerBitmap->transparentColor);

    // ハートのゲージ描画
    for (int i = 0; i < 5; i++) {
      int index = 4 - i;
      hsbs::BitmapMono *bmp = this->value > index ? this->_smallHeartBitmap1 : this->_smallHeartBitmap0;
      bmp->x = ((maxWidth + 2) << 2) + dotScreenX;
      bmp->y = (i * 6 + 3) << 2;
      bmp->updateTransform(nullptr);
      bmp->canvas.pushAffine(targetCanvas, bmp->transform.matrix, bmp->transparentColor);
    }
  }
};

} // namespace seamonsue

#endif