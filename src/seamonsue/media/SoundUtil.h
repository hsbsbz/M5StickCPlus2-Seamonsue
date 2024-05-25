#ifndef _SEAMONSUE__MEDIA__SOUND_UTIL_H_INCLUDE_
#define _SEAMONSUE__MEDIA__SOUND_UTIL_H_INCLUDE_

#include "hsbs/app/M5ToneSoundManager.h"

namespace seamonsue {

class SoundUtil : public hsbs::M5ToneSoundManager {

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * ボタンを押したときの音
   */
  void pressButton() {
    this->stop();
    this->pushTone(4400, 200);
  }

  /**
   * タイトル画面の音
   */
  void title() {
    this->stop();
    this->pushTone(5274.04, 2000);
  }

  /**
   * 掃除中の音
   */
  void clean() {
    for (int i = 0; i < 3; i++) {
      this->pushTone(4186.01, 100);
      this->pushTone(4698.64, 100);
      this->pushWait(300);
      this->pushTone(5274.04, 100);
      this->pushTone(5587.65, 100);
      this->pushWait(300);
    }
  }

  /**
   * 時計の編集開始の音
   */
  void startClockEdit() {
    this->stop();
    this->pushTone(4186.01, 100);
    this->pushTone(4698.64, 100);
  }

  /**
   * 時計の編集終了の音
   */
  void endClockEdit() {
    this->stop();
    this->pushTone(10548.08, 100); // ９オクターブのド
    this->pushTone(7902.13, 100);  // ８オクターブのシ
    this->pushWait(10);
    this->pushTone(6271.93, 100); // ８オクターブのソ
    this->pushTone(4698.64, 100); // ８オクターブのレ
  }

  /**
   * 食べるときの音
   */
  void eat() {
    this->stop();
    this->pushTone(6271.93, 50);  // ８オクターブのソ
    this->pushTone(4698.64, 100); // ８オクターブのレ
  }

  /**
   * 喜ぶ時の音
   */
  void fun() {
    this->stop();
    this->pushTone(4698.64, 100); // ８オクターブのレ
    this->pushTone(6271.93, 100); // ８オクターブのソ
    this->pushWait(10);
    this->pushTone(7902.13, 100);  // ８オクターブのシ
    this->pushTone(10548.08, 200); // ９オクターブのド
  }

  /**
   * カウントダウン中の音
   */
  void gameContdown() {
    this->stop();
    this->pushTone(2637.02, 100); // ７オクターブのミ
  }

  /**
   * カウントダウン終了時、ゲーム開始の音
   */
  void gameStart() {
    this->stop();
    this->pushTone(4698.64, 400); // ８オクターブのレ
  }

  /**
   * ハートをとった時の音
   */
  void gameHitHeart() {
    this->stop();
    this->pushTone(4698.64, 50); // ８オクターブのレ
    this->pushWait(10);
    this->pushTone(6271.93, 100); // ８オクターブのソ
  }

  /**
   * 魚に衝突したときの音
   */
  void gameHitFish() {
    this->stop();
    this->pushTone(2093.00, 50); // ７オクターブのド
    this->pushWait(10);
    this->pushTone(2093.00, 200); // ７オクターブのド
  }
};

} // namespace seamonsue

#endif
