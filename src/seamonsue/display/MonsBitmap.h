#ifndef _SEAMONSUE__DISPLAY__MONS_BITMAP_H_INCLUDE_
#define _SEAMONSUE__DISPLAY__MONS_BITMAP_H_INCLUDE_

#include "../../image_progmem.h"
#include "../global.h"
#include "hsbs/display/BitmapMono.h"
#include "hsbs/display/DisplayObjectContainer.h"

namespace seamonsue {

enum MonsAnimationType {
  NONE = 0,
  WALK = 1,
  ACTION = 2,
};

class MonsBitmap : public hsbs::DisplayObjectContainer {
private:
  //------------------------------
  // Private
  //------------------------------
  int _monsId = -1;
  MonsAnimationType _monsAnimationType = WALK;
  hsbs::BitmapMono *walk0 = nullptr;
  hsbs::BitmapMono *walk1 = nullptr;
  hsbs::BitmapMono *action = nullptr;

  /**
   * 停止中
   */
  void _updateStand() {
    walk0->visible = true;
  }

  /**
   * 歩くアニメーション
   */
  void _updateWalk() {
    walk0->visible = false;
    walk1->visible = false;
    action->visible = false;
    int t = (int)(millis() / 500);
    if ((t % 12) == 0) {
      action->visible = true;
      return;
    }
    if ((t % 2) == 0) {
      walk1->visible = true;
      return;
    }
    walk0->visible = true;
  }

  /**
   * 喜ぶアニメーション
   */
  void _updateAction() {
    walk0->visible = false;
    walk1->visible = false;
    action->visible = false;
    int t = (int)(millis() / 500);
    if ((t % 2) == 0) {
      walk1->visible = true;
      return;
    }
    action->visible = true;
  }

  /**
   * モンスの種類によってビットマップを更新する
   *
   * @param data
   */
  void _updateBitmap(MonsData *data) {
    if (walk0 != nullptr) {
      this->removeChild(walk0);
      delete walk0;
    }

    this->monsX = data->action.x;
    this->monsY = data->action.y;
    this->monsW = data->action.width;
    this->monsH = data->action.height;

    walk0 = new hsbs::BitmapMono(data->walk0.data, data->walk0.width, data->walk0.height);
    walk0->clipRect = &dotAreaRect;
    walk0->x = data->walk0.x;
    walk0->y = data->walk0.y;
    walk0->anchorX = data->walk0.width >> 1;
    walk0->anchorY = data->walk0.height;

    if (walk1 != nullptr) {
      this->removeChild(walk1);
      delete walk1;
    }
    walk1 = new hsbs::BitmapMono(data->walk1.data, data->walk1.width, data->walk1.height);
    walk1->clipRect = &dotAreaRect;
    walk1->x = data->walk1.x;
    walk1->y = data->walk1.y;
    walk1->anchorX = data->walk1.width >> 1;
    walk1->anchorY = data->walk1.height;

    if (action != nullptr) {
      this->removeChild(action);
      delete action;
    }
    action = new hsbs::BitmapMono(data->action.data, data->action.width, data->action.height);
    action->clipRect = &dotAreaRect;
    action->x = data->action.x;
    action->y = data->action.y;
    action->anchorX = data->action.width >> 1;
    action->anchorY = data->action.height;

    this->addChild(walk0);
    this->addChild(walk1);
    this->addChild(action);

    walk0->visible = false;
    walk1->visible = false;
    action->visible = false;
  };

public:
  //------------------------------
  // Public
  //------------------------------

  int monsX = 0;
  int monsY = 0;
  int monsW = 0;
  int monsH = 0;

  /**
   * 表示を更新する
   */
  void update() {
    // ストアの状態を参照してビットマップを更新
    const int monsId = petStore.getMonsId();
    // const int monsId = 6;
    if (this->_monsId != monsId) {
      this->_monsId = monsId;
      this->_updateBitmap(&monsDataList[this->_monsId]);
    }
    // アニメーションの状態
    if (this->_monsAnimationType == NONE) {
      return;
    }
    // 表示するビットマップを切り替える
    switch (this->_monsAnimationType) {
    case WALK:
      this->_updateWalk();
      break;
    case ACTION:
      this->_updateAction();
      break;
    }
  }

  /**
   * 歩くフレームで停止する
   */
  void stopWalkFrame() {
    this->_monsAnimationType = NONE;
    walk0->visible = true;
    walk1->visible = false;
    action->visible = false;
  }

  /**
   * 喜んでるフレームで停止する
   */
  void stopActionFrame() {
    this->_monsAnimationType = NONE;
    walk0->visible = false;
    walk1->visible = false;
    action->visible = true;
  }

  /**
   * 歩くアニメーション
   */
  void walkAnimation() {
    this->_monsAnimationType = WALK;
  }

  /**
   * 喜んでるアニメーション
   */
  void actionAnimation() {
    this->_monsAnimationType = ACTION;
  }

  /**
   * デストラクタ
   */
  virtual ~MonsBitmap() {
    if (walk0 != nullptr) {
      this->removeChild(walk0);
      delete walk0;
    }
    if (walk1 != nullptr) {
      this->removeChild(walk1);
      delete walk1;
    }
    if (action != nullptr) {
      this->removeChild(action);
      delete action;
    }
  }
};

} // namespace seamonsue

#endif