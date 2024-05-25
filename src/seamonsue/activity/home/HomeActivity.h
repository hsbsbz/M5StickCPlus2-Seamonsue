#ifndef _SEAMONSUE__ACTIVITY__HOME__HOME_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__HOME__HOME_ACTIVITY_H_INCLUDE_

#include "../../../image_progmem.h"
// #include "../../display/DirtyBitmap.h"
#include "../../display/MonsBitmap.h"
#include "../../global.h"
#include "hsbs/app/M5StickCPlust2Activity.h"

namespace seamonsue {

class HomeActivity : public hsbs::M5StickCPlust2Activity {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * モンス画像
   */
  MonsBitmap *_monsBitmap;

  /**
   * @brief ミュートの状態をバックアップしておく変数
   */
  bool _bkMuted;

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {
    // モンス画像
    this->_monsBitmap = new MonsBitmap();
    this->_monsBitmap->setPosition(119, 135)->setScale(4, 4);
    this->stage.addChild(this->_monsBitmap);
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->stage.removeChild(this->_monsBitmap);
    delete this->_monsBitmap;
  }

  /**
   * フレーム更新時
   */
  void onEnterFrame() override {
    this->_monsBitmap->update(); // フレームを更新
  }

  
  /**
   * Aボタン押下
   */
  void onPressButtonA() override {
    this->_bkMuted = gameStore.getMuted();
  }

  
  /**
   * Aボタン押下
   */
  void onReleaseButtonA() override {
    if (this->isExact()) { // パスの完全一致
      if (this->_bkMuted != gameStore.getMuted()) {
        // 長押しでミュートの切り替えがあったら何もしない
        return;
      }
      soundUtil.pressButton();
      this->go("/clock");
    }
  }

  /**
   * Bボタン押下
   */
  void onPressButtonB() override {
    if (petStore.getEvolutionCount() == 0) return;
    if (this->isExact()) { // パスの完全一致
      soundUtil.pressButton();
      this->go("/home/info");
    }
  }
};

} // namespace seamonsue

#endif