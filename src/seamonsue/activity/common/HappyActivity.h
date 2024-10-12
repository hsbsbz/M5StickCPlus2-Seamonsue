#ifndef _SEAMONSUE__ACTIVITY__COMMON__HAPPY_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__COMMON__HAPPY_ACTIVITY_H_INCLUDE_

#include "../../display/FaceBitmap.h"
#include "../../display/MonsBitmap.h"
#include "../../global.h"
#include "hsbs/display/BitmapMono.h"
#include "../SeamonsueActivity.h"

namespace seamonsue {

class HappyActivity : public SeamonsueActivity {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * モンス画像
   */
  MonsBitmap *_monsBitmap;

  /**
   * 喜ぶ顔のアイコン
   */
  FaceBitmap *_faceBitmap;

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
    this->_monsBitmap->setPosition(21, 34);
    this->_monsBitmap->actionAnimation();
    this->dotStage.addChild(this->_monsBitmap);

    // 喜ぶ顔のアイコン
    this->_faceBitmap = new FaceBitmap(true);
    this->_faceBitmap->setPosition(0, 2);
    this->dotStage.addChild(this->_faceBitmap);

    // 音再生
    soundUtil.fun();
    // 一定時間待機
    this->activeTransition.add(this->activeTransition.wait(3200));
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->activeTransition.clear();
    this->dotStage.removeChild(this->_monsBitmap);
    delete this->_monsBitmap;
    this->dotStage.removeChild(this->_faceBitmap);
    delete this->_faceBitmap;
  }

  /**
   * フレーム更新時
   */
  void onEnterFrame() override {
    this->resetSleepTimestamp(); // 自動スリープをリセット
    this->_monsBitmap->update(); // コマアニメーションを更新
    this->_faceBitmap->update(); // コマアニメーションを更新

    int minMonsX = ((int)this->_monsBitmap->monsW >> 1) + Img::Mono::face0Width + 1;
    this->_monsBitmap->x = this->_monsBitmap->x < minMonsX ? minMonsX : this->_monsBitmap->x;

    this->_faceBitmap->x = this->_monsBitmap->x + (int)this->_monsBitmap->monsX - ((int)this->_monsBitmap->monsW >> 1) - 1;
    this->_faceBitmap->y = this->_monsBitmap->y + (int)(this->_monsBitmap->monsY - this->_monsBitmap->monsH);
    int minFaceX = Img::Mono::face0Width;
    int minFaceY = Img::Mono::face0Height + 1;
    this->_faceBitmap->x = this->_faceBitmap->x < minFaceX ? minFaceX : this->_faceBitmap->x;
    this->_faceBitmap->y = this->_faceBitmap->y < minFaceY ? minFaceY : this->_faceBitmap->y;

    if (this->activeTransition.getState() == hsbs::COMPLETE) {
      // トランジションが終了したら自動で遷移
      this->go("home");
    }
  }
};

} // namespace seamonsue

#endif