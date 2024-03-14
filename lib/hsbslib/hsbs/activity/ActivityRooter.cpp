
#include "./ActivityRooter.h"

namespace hsbs {

//------------------------------
// Public
//------------------------------
ActivityRooter::ActivityRooter() : canvas(&M5.Display) {
}

bool ActivityRooter::running() { return this->_running; }

void ActivityRooter::add(String path, Activity *activity) {
  activity->setRoot(this);          // 親のアクティビティの参照を登録
  activity->setPath(path);          // パスを設定
  this->activityList.add(activity); // リストに追加
}

void ActivityRooter::go(String path) {
  // 遷移中は何もしない
  if (this->_running) return;

  // 変更がない場合は何もしない
  if (this->_path.equals(path)) return;

  // 前後に "/" を追加する
  if (path.indexOf("/") != 0) path = "/" + path;
  if (path.lastIndexOf("/") != (path.length() - 1)) path = path + "/";

  // パスを更新
  this->_path = path;

  // 実行中フラグを立てる
  this->_running = true;

  // 登録されている数
  unsigned int length = this->activityList.length();

  // 登録アクティビティのループ
  for (int i = 0; i < length; i++) {
    Activity *activity = this->activityList.getAt(i);
    if (path.indexOf(activity->getPath()) == 0) {
      // 該当の場合はアクティブに
      activity->active(); // アクティブに変更されたら内部で running が true に
    } else {
      // 該当しない場合は非アクティブ
      activity->deactive(); // 非アクティブに変更されたら内部で running が true に
    }
  }

  // 実行時に一度だけ更新を行う
  this->update();
}

void ActivityRooter::updateActivity() {
  // 登録されている数
  unsigned int length = this->activityList.length();

  // 非アクティブイベントの発火
  for (int i = length - 1; i >= 0; i--) {
    Activity *activity = this->activityList.getAt(i);
    if (!activity->isActive()) {
      // 非アクティブのアクティビティ
      if (activity->running()) {
        // 非アクティブのトランジション実行中
        activity->updateTransition(); // 更新
        if (activity->running()) {
          // 更新後もまだ running 状態なら処理を中断し、次のフレームを待つ
          return;
        }
      }
    }
  }

  // アクティブイベントの発火
  for (int i = 0; i < length; i++) {
    Activity *activity = this->activityList.getAt(i);
    if (activity->isActive()) {
      // アクティブのアクティビティ
      if (activity->running()) {
        // アクティブのトランジション実行中
        activity->updateTransition(); // 更新
        if (activity->running()) {
          // 更新後もまだ running 状態なら処理を中断し、次のフレームを待つ
          return;
        }
      }
    }
  }

  // 全てのアクティビティのトランジションが終了したら自身を完了
  this->_running = false;
}

void ActivityRooter::draw() {
  this->canvas.fillScreen(BLACK);
  unsigned int length = this->activityList.length();
  for (int i = 0; i < length; i++) {
    Activity *activity = this->activityList.getAt(i);
    if (activity->visiblity()) {
      if (activity->stage.visible) {
        activity->stage.updateTransform(nullptr);
        activity->stage.draw(&this->canvas);
      }
    }
  }
}

void ActivityRooter::renderScreen() {
  this->canvas.pushSprite(0, 0); // (0, 0)座標に一括表示実行（12ms くらいかかる）
}

void ActivityRooter::update() {
  // アクティビティの更新
  this->updateActivity();
  // エンターフレーム
  unsigned int length = this->activityList.length();
  for (int i = 0; i < length; i++) {
    Activity *activity = this->activityList.getAt(i);
    if (activity->visiblity()) {
      activity->update();
    }
  }
}

String ActivityRooter::getPath() {
  return this->_path;
}

} // namespace hsbs