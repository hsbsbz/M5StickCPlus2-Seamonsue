
#include "M5StickCPlust2App.h"

namespace hsbs {

/**
 * @brief 初期設定を行う
 */
void M5StickCPlust2App::setup() {

  // ボタンのセットアップ(StickCP2 より先)
  this->_buttonA.setup(37, 1000);
  this->_buttonB.setup(39, 1000);
  this->_buttonC.setup(35, 1000);

  // StickCP2 を開始
  auto cfg = M5.config();
  StickCP2.begin(cfg);
  StickCP2.Display.setRotation(1);

  // オフスクリーンレンダリングのメモリを確保
  this->canvas.createSprite(StickCP2.Display.width(), StickCP2.Display.height());

  // スリープのタイマー設定
  this->_sleepTimestamp = millis();
  this->_autoSleepTime = 10000;

  // デフォルトFPS
  this->setFps(30);
}

void M5StickCPlust2App::setFps(unsigned int fps) {
  this->_intrevaMicros = 1000000 / fps;
  this->_intrevalTicks = pdMS_TO_TICKS(1000 / fps);
}

TickType_t M5StickCPlust2App::getIntrevalTicks() {
  return this->_intrevalTicks;
}

void M5StickCPlust2App::setAutoSleepTime(unsigned int ms) {
  this->_autoSleepTime = ms;
}

/**
 * @brief アップデート処理を行う
 */
void M5StickCPlust2App::update() {

  // // update 開始時刻
  unsigned long beginTimestamp = micros();

  // StickCP2
  StickCP2.update();

  // ボタンイベントの発火前のパスを保持
  this->_path2 = this->getPath();

  // Button A
  this->_buttonA.update();
  if (this->_buttonA.changedLongPress() && this->_buttonA.longPressed()) {
    this->onLongPressButtonA();
  }
  if (this->_buttonA.changed()) {
    if (this->_buttonA.pressed())
      this->onPressButtonA();
    else
      this->onReleaseButtonA();
  }
  // Button B
  this->_buttonB.update();
  if (this->_buttonB.changedLongPress() && this->_buttonB.longPressed()) {
    this->onLongPressButtonB();
  }
  if (this->_buttonB.changed()) {
    if (this->_buttonB.pressed())
      this->onPressButtonB();
    else
      this->onReleaseButtonB();
  }
  // Button C
  this->_buttonC.update();
  if (this->_buttonC.changedLongPress() && this->_buttonC.longPressed()) {
    this->onLongPressButtonC();
  }
  if (this->_buttonC.changed()) {
    if (this->_buttonC.pressed())
      this->onPressButtonC();
    else
      this->onReleaseButtonC();
  }

  // アクティビティの更新
  ActivityRooter::update();

  // スリープ判定
  if (this->_autoSleepTime > 0) {
    unsigned long now = millis();
    unsigned long elapsed = now - this->_sleepTimestamp;
    if (elapsed >= this->_autoSleepTime) {
      this->sleepNow();
    }
  }

  // イベントを発火
  this->dispatchEvent(EVENT_ENTER_FRAME);

  // オフスクリーンレンダリング
  this->draw();
  // スクリーンに描画
  this->renderScreen();

  // update 終了時刻
  unsigned long endTimestamp = micros();

  // 経過時間
  unsigned int delta = (endTimestamp - beginTimestamp);

  // 設定された FPS 以上の実行速度が出ていたら遅延を差し込んで FPS に合わせる。
  if (delta < this->_intrevaMicros) {
    delayMicroseconds(this->_intrevaMicros - delta);
  } else {
    // 設定した FPS のパフォーマンスが出てないケース
  }
}

bool M5StickCPlust2App::transitioning() {
  if (this->running()) return true;
  if (!this->_path2.equals(this->getPath())) return true;
  // 他に何かあれば追記
  return false;
}

void M5StickCPlust2App::resetSleepTimestamp() {
  this->_sleepTimestamp = millis();
}

void M5StickCPlust2App::sleepNow() {
  unsigned int length = this->activityList.length();
  for (int i = 0; i < length; i++) {
    M5StickCPlust2Activity *activity = static_cast<M5StickCPlust2Activity *>(this->activityList.getAt(i));
    if (activity->visiblity()) {
      activity->onBeforeSleep();
    }
  }
  this->dispatchEvent(EVENT_BEFORE_SLEEP);
  StickCP2.Power.deepSleep(0, true);
}


void M5StickCPlust2App::restart() {
  StickCP2.Power.deepSleep(1, false);
}

/**
 * @brief ボタンAが押された時の処理
 */
void M5StickCPlust2App::onPressButtonA() {
  this->resetSleepTimestamp();
  unsigned int length = this->activityList.length();
  for (int i = 0; i < length; i++) {
    if (this->transitioning()) return;
    M5StickCPlust2Activity *activity = static_cast<M5StickCPlust2Activity *>(this->activityList.getAt(i));
    if (activity->visiblity()) {
      activity->onPressButtonA();
    }
  }
  this->dispatchEvent(EVENT_BUTTON_PRESS_A);
}

/**
 * @brief ボタンAが長押しされた時の処理
 */
void M5StickCPlust2App::onLongPressButtonA() {
  this->resetSleepTimestamp();
  unsigned int length = this->activityList.length();
  for (int i = 0; i < length; i++) {
    if (this->transitioning()) return;
    M5StickCPlust2Activity *activity = static_cast<M5StickCPlust2Activity *>(this->activityList.getAt(i));
    if (activity->visiblity()) {
      activity->onLongPressButtonA();
    }
  }
  this->dispatchEvent(EVENT_BUTTON_LONG_PRESS_A);
}

/**
 * @brief ボタンAが離された時の処理
 */
void M5StickCPlust2App::onReleaseButtonA() {
  this->resetSleepTimestamp();
  unsigned int length = this->activityList.length();
  for (int i = 0; i < length; i++) {
    if (this->transitioning()) return;
    M5StickCPlust2Activity *activity = static_cast<M5StickCPlust2Activity *>(this->activityList.getAt(i));
    if (activity->visiblity()) {
      activity->onReleaseButtonA();
    }
  }
  this->dispatchEvent(EVENT_BUTTON_RELEASE_A);
}

/**
 * @brief ボタンBが押された時の処理
 */
void M5StickCPlust2App::onPressButtonB() {
  this->resetSleepTimestamp();
  unsigned int length = this->activityList.length();
  for (int i = 0; i < length; i++) {
    if (this->transitioning()) return;
    M5StickCPlust2Activity *activity = static_cast<M5StickCPlust2Activity *>(this->activityList.getAt(i));
    if (activity->visiblity()) {
      activity->onPressButtonB();
    }
  }
  this->dispatchEvent(EVENT_BUTTON_PRESS_B);
}

/**
 * @brief ボタンBが長押しされた時の処理
 */
void M5StickCPlust2App::onLongPressButtonB() {
  this->resetSleepTimestamp();
  unsigned int length = this->activityList.length();
  for (int i = 0; i < length; i++) {
    if (this->transitioning()) return;
    M5StickCPlust2Activity *activity = static_cast<M5StickCPlust2Activity *>(this->activityList.getAt(i));
    if (activity->visiblity()) {
      activity->onLongPressButtonB();
    }
  }
  this->dispatchEvent(EVENT_BUTTON_LONG_PRESS_B);
}

/**
 * @brief ボタンBが離された時の処理
 */
void M5StickCPlust2App::onReleaseButtonB() {
  this->resetSleepTimestamp();
  unsigned int length = this->activityList.length();
  for (int i = 0; i < length; i++) {
    if (this->transitioning()) return;
    M5StickCPlust2Activity *activity = static_cast<M5StickCPlust2Activity *>(this->activityList.getAt(i));
    if (activity->visiblity()) {
      activity->onReleaseButtonB();
    }
  }
  this->dispatchEvent(EVENT_BUTTON_RELEASE_B);
}

/**
 * @brief ボタンCが押された時の処理
 */
void M5StickCPlust2App::onPressButtonC() {
  this->resetSleepTimestamp();
  unsigned int length = this->activityList.length();
  for (int i = 0; i < length; i++) {
    if (this->transitioning()) return;
    M5StickCPlust2Activity *activity = static_cast<M5StickCPlust2Activity *>(this->activityList.getAt(i));
    if (activity->visiblity()) {
      activity->onPressButtonC();
    }
  }
  this->dispatchEvent(EVENT_BUTTON_PRESS_C);
}

/**
 * @brief ボタンCが長押しされた時の処理
 */
void M5StickCPlust2App::onLongPressButtonC() {
  unsigned int length = this->activityList.length();
  for (int i = 0; i < length; i++) {
    if (this->transitioning()) return;
    M5StickCPlust2Activity *activity = static_cast<M5StickCPlust2Activity *>(this->activityList.getAt(i));
    if (activity->visiblity()) {
      activity->onLongPressButtonC();
    }
  }
  this->dispatchEvent(EVENT_BUTTON_LONG_PRESS_C);
  this->sleepNow();
}

/**
 * @brief ボタンCが離された時の処理
 */
void M5StickCPlust2App::onReleaseButtonC() {
  this->resetSleepTimestamp();
  unsigned int length = this->activityList.length();
  for (int i = 0; i < length; i++) {
    if (this->transitioning()) return;
    M5StickCPlust2Activity *activity = static_cast<M5StickCPlust2Activity *>(this->activityList.getAt(i));
    if (activity->visiblity()) {
      activity->onReleaseButtonC();
    }
  }
  this->dispatchEvent(EVENT_BUTTON_RELEASE_C);
}

} // namespace hsbs