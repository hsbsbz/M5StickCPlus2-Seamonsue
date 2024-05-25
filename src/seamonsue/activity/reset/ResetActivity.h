#ifndef _SEAMONSUE__ACTIVITY__RESET__RESET_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__RESET__RESET_ACTIVITY_H_INCLUDE_

#include "../../../image_progmem.h"
#include "../../global.h"
#include "hsbs/app/M5StickCPlust2Activity.h"
#include "hsbs/display/BitmapMono.h"
#include "hsbs/tween/Ease.h"

namespace seamonsue {

class ResetActivity : public hsbs::M5StickCPlust2Activity {
private:
  /**
   * タイトル画像
   */
  hsbs::BitmapMono *_resetLabelBitmap;
  hsbs::BitmapMono *_resetYesBitmap0;
  hsbs::BitmapMono *_resetYesBitmap1;
  hsbs::BitmapMono *_resetNoBitmap0;
  hsbs::BitmapMono *_resetNoBitmap1;
  hsbs::BitmapMono *_outlineBitmap;
  hsbs::BitmapMono *_faceBitmap0;
  hsbs::BitmapMono *_faceBitmap1;

  int _selectedIndex;

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {
    this->_selectedIndex = 0;
    // Reset?
    this->_resetLabelBitmap = new hsbs::BitmapMono(Img::Mono::reset_label, Img::Mono::reset_labelWidth, Img::Mono::reset_labelHeight);
    this->_resetLabelBitmap->setPosition(34, 2 * 4)->setScale(4, 4);
    this->stage.addChild(this->_resetLabelBitmap);
    if (petStore.isDead()) {
      this->_resetLabelBitmap->x += 9 * 4;
    }

    // yes0
    this->_faceBitmap0 = new hsbs::BitmapMono(Img::Mono::reset_face0, Img::Mono::reset_face0Width, Img::Mono::reset_face0Height);
    this->_faceBitmap0->setPosition(34 + (28 * 4), 2 * 4)->setScale(4, 4);
    this->stage.addChild(this->_faceBitmap0);
    // yes1
    this->_faceBitmap1 = new hsbs::BitmapMono(Img::Mono::reset_face1, Img::Mono::reset_face1Width, Img::Mono::reset_face1Height);
    this->_faceBitmap1->setPosition(this->_faceBitmap0->x, this->_faceBitmap0->y)->setScale(4, 4);
    this->stage.addChild(this->_faceBitmap1);

    // yes0
    this->_resetYesBitmap0 = new hsbs::BitmapMono(Img::Mono::reset_yes0, Img::Mono::reset_yes0Width, Img::Mono::reset_yes0Height);
    this->_resetYesBitmap0->setPosition(34 + (3 * 4), (22 * 4))->setScale(4, 4);
    this->stage.addChild(this->_resetYesBitmap0);
    // yes1
    this->_resetYesBitmap1 = new hsbs::BitmapMono(Img::Mono::reset_yes1, Img::Mono::reset_yes1Width, Img::Mono::reset_yes1Height);
    this->_resetYesBitmap1->setPosition(this->_resetYesBitmap0->x, this->_resetYesBitmap0->y)->setScale(4, 4);
    this->stage.addChild(this->_resetYesBitmap1);

    // no0
    this->_resetNoBitmap0 = new hsbs::BitmapMono(Img::Mono::reset_no0, Img::Mono::reset_no0Width, Img::Mono::reset_no0Height);
    this->_resetNoBitmap0->setPosition(34 + (23 * 4), (22 * 4))->setScale(4, 4);
    this->stage.addChild(this->_resetNoBitmap0);
    // no1
    this->_resetNoBitmap1 = new hsbs::BitmapMono(Img::Mono::reset_no1, Img::Mono::reset_no1Width, Img::Mono::reset_no1Height);
    this->_resetNoBitmap1->setPosition(this->_resetNoBitmap0->x, this->_resetNoBitmap0->y)->setScale(4, 4);
    this->stage.addChild(this->_resetNoBitmap1);
    // outline
    this->_outlineBitmap = new hsbs::BitmapMono(Img::Mono::reset_outline, Img::Mono::reset_outlineWidth, Img::Mono::reset_outlineHeight);
    this->_outlineBitmap->setScale(4, 4);
    this->stage.addChild(this->_outlineBitmap);
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->activeTransition.clear();
    this->stage.removeChild(this->_resetLabelBitmap);
    delete this->_resetLabelBitmap;
    this->stage.removeChild(this->_resetYesBitmap0);
    delete this->_resetYesBitmap0;
    this->stage.removeChild(this->_resetYesBitmap1);
    delete this->_resetYesBitmap1;
    this->stage.removeChild(this->_resetNoBitmap0);
    delete this->_resetNoBitmap0;
    this->stage.removeChild(this->_resetNoBitmap1);
    delete this->_resetNoBitmap1;
    this->stage.removeChild(this->_faceBitmap0);
    delete this->_faceBitmap0;
    this->stage.removeChild(this->_faceBitmap1);
    delete this->_faceBitmap1;
    this->stage.removeChild(this->_outlineBitmap);
    delete this->_outlineBitmap;
  }

  /**
   * フレーム更新時
   */
  void onEnterFrame() override {
    long now = millis();

    this->_resetYesBitmap0->visible = (this->_selectedIndex == 0);
    this->_resetYesBitmap1->visible = !this->_resetYesBitmap0->visible;
    this->_resetNoBitmap0->visible = !this->_resetYesBitmap0->visible;
    this->_resetNoBitmap1->visible = !this->_resetNoBitmap0->visible;

    if (petStore.isDead()) {
      this->_faceBitmap0->visible = false;
      this->_faceBitmap1->visible = false;
    } else {
      this->_faceBitmap0->visible = this->_resetYesBitmap0->visible;
      this->_faceBitmap1->visible = !this->_faceBitmap0->visible;
    }

    hsbs::BitmapMono *outlineTarget = (this->_selectedIndex == 0) ? this->_resetNoBitmap0 : this->_resetYesBitmap0;
    this->_outlineBitmap->setPosition(outlineTarget->x - 4, outlineTarget->y - 4);
    this->_outlineBitmap->visible = ((now / 250) % 3) == 0;
  }

  void gotoHome() {
    switch (gameStore.getGameState()) {
    case seamonsue::TITLE: this->go("/title"); break; // タイトル画面
    case seamonsue::PLAY: this->go("/home"); break;   // 育成画面
    case seamonsue::DEAD: this->go("/dead"); break;   // お墓画面
    }
  }

  /**
   * Aボタン押下
   */
  void onReleaseButtonA() override {
    if (this->_selectedIndex == 0) {
      soundUtil.pressButton();
      this->gotoHome();
    } else {
      gameStore.clear();  
      soundUtil.muted = gameStore.getMuted();// ミュートの状態を反映
      this->go("/title");
    }
  }

  /**
   * Bボタン押下
   */
  void onPressButtonB() override {
    soundUtil.pressButton();
    this->_selectedIndex = ++this->_selectedIndex % 2;
  }

  /**
   * Cボタン押下
   */
  void onReleaseButtonC() override {
    soundUtil.pressButton();
    this->gotoHome();
  }
};

} // namespace seamonsue

#endif