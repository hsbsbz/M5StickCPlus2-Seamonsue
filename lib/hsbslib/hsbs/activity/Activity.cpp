
#include "./Activity.h"
#include "ActivityRooter.h" // h に置くと循環参照になる。 h では 前方宣言で対処

namespace hsbs {

//------------------------------
// Protected
//------------------------------
void Activity::onInit() {}
void Activity::onActive() {}
void Activity::onDeactive() {}
void Activity::onEnterFrame() {}

//------------------------------
// Public
//------------------------------
bool Activity::running() { return this->_running; }

bool Activity::isActive() { return this->_isActive; }

void Activity::active() {
  // 初回のみ onInit をコールバック
  if (!this->_inited) {
    this->_inited = true;
    this->onInit();
  }
  if (this->_isActive) return;    // 既にアクティブなら何もしない
  this->_isActive = true;         // アクティブ状態にする
  this->_running = true;          // 実行中にする
  this->activeTransition.reset(); // トランジションをリセットしておく
}

void Activity::deactive() {
  if (this->_isActive == false) return;
  this->_isActive = false;          // 非アクティブ状態にする
  this->_running = true;            // 実行中にする
  this->deactiveTransition.reset(); // トランジションをリセットしておく
}

void Activity::updateTransition() {

  if (!this->_running) return; // 実行中でなければ何もしない

  if (this->_isActive) {
    // アクティブ状態
    if (this->activeTransition.getState() == STANDBY) {
      // 待機状態
      this->onActive();               // アクティブ時のコールバック
      this->activeTransition.start(); // トランジションを開始する
    }
    if (this->activeTransition.getState() == RUNNING) {
      // トランジションを実行中
      this->activeTransition.update(); // トランジションを更新する
    }
    if (this->activeTransition.getState() != COMPLETE) {
      // トランジションが完了していなければフラグを折らない
      return;
    }
    this->_running = false; // トランジションが完了していたら実行中を解除
  } else {
    // 非アクティブ状態
    if (this->deactiveTransition.getState() == STANDBY) {
      // 待機状態
      this->deactiveTransition.start(); // トランジションを開始する
    }
    if (this->deactiveTransition.getState() == RUNNING) {
      // トランジションを実行中
      this->deactiveTransition.update(); // トランジションを更新する
    }
    if (this->deactiveTransition.getState() != COMPLETE) {
      // トランジションが完了していなければフラグを折らない
      return;
    }
    this->_running = false; // トランジションが完了していたら実行中を解除
    this->onDeactive();     // 非アクティブ時のコールバック
  }
}

void Activity::update() {
  this->onEnterFrame();
}

String Activity::getPath() { return this->_path; }

void Activity::setPath(String path) {
  // 前後に "/" を追加する
  if (path.indexOf("/") != 0) path = "/" + path;
  if (path.lastIndexOf("/") != (path.length() - 1)) path = path + "/";
  // パスを設定
  this->_path = path;
}

void Activity::setRoot(ActivityRooter *root) {
  this->root = root; // 親のルーターの参照を保持
}

bool Activity::visiblity() {
  if (this->_isActive) return this->activeTransition.getState() != STANDBY;
  return this->deactiveTransition.getState() == RUNNING;
}

bool Activity::isExact() {
  if (this->root == nullptr) return false;
  return this->_path.equals(this->root->getPath());
}

void Activity::go(String path) {
  if (this->root == nullptr) return;

  this->root->go(path);
}

String Activity::getRootPath() {
  if (this->root == nullptr) return "";
  return this->root->getPath();
}

} // namespace hsbs