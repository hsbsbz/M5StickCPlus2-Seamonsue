

#ifndef _SEAMONSUE__ACTIVITY__CLEAN__CLEAN_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__CLEAN__CLEAN_ACTIVITY_H_INCLUDE_

#include "../../display/BroomBitmap.h"
#include "../../display/MonsBitmap.h"
// #include "../../global.h"
#include "hsbs/display/BitmapMono.h"
#include "hsbs/tween/Ease.h"
#include "../SeamonsueActivity.h"

namespace seamonsue {

class CleanActivity : public SeamonsueActivity {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * モンス画像
   */
  MonsBitmap *_monsBitmap;

  /**
   * ブラシ画像
   */
  BroomBitmap *_broomBitmap;

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
    this->dotStage.addChild(this->_monsBitmap);
    this->_monsBitmap->update();
    // ブラシ画像
    this->_broomBitmap = new BroomBitmap();
    this->_broomBitmap->setPosition(-23, 3);
    this->dotStage.addChild(this->_broomBitmap);
    // トランジション
    this->activeTransition.add(
        this->activeTransition.tween(800, hsbs::Ease::IN_SINE)->add(&this->_monsBitmap->y, 34, -3),
        this->activeTransition.callback([this]() { soundUtil.clean(); }),
        this->activeTransition.tween(3000, hsbs::Ease::LINEAR)->add(&this->_broomBitmap->x, -23, 52),
        this->activeTransition.tween(800, hsbs::Ease::IN_OUT_CUBIC)->add(&this->_monsBitmap->y, -3 , 34),
        this->activeTransition.callback([this]() {
          petStore.execClean();
        }));
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->activeTransition.clear();
    this->dotStage.removeChild(this->_monsBitmap);
    delete this->_monsBitmap;
    this->dotStage.removeChild(this->_broomBitmap);
    delete this->_broomBitmap;
  }

  /**
   * フレーム更新時
   */
  void onEnterFrame() override {
    this->resetSleepTimestamp();                                    // 自動スリープをリセット
    this->_monsBitmap->y = (int)this->_monsBitmap->y >> 0;   // ドットに吸着
    this->_broomBitmap->x = (int)this->_broomBitmap->x >> 0; // ドットに吸着
    this->_broomBitmap->update();                                   // コマアニメーションを更新
    if (this->activeTransition.getState() == hsbs::COMPLETE) {
      // トランジションが終了したら自動で遷移
      this->go("/clean/page2");
    }
  }
};

} // namespace seamonsue

#endif