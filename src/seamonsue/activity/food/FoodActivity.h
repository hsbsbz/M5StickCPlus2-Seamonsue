

#ifndef _SEAMONSUE__ACTIVITY__FOOD__FOOD_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__FOOD__FOOD_ACTIVITY_H_INCLUDE_

#include "../../display/BroomBitmap.h"
#include "../../display/MonsBitmap.h"
#include "../../global.h"
#include "hsbs/app/M5StickCPlust2Activity.h"
#include "hsbs/display/BitmapMono.h"
#include "hsbs/tween/Ease.h"

namespace seamonsue {

class FoodActivity : public hsbs::M5StickCPlust2Activity {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * モンス画像
   */
  MonsBitmap *_monsBitmap;
  /**
   * 食べ物画像１
   */
  hsbs::BitmapMono *_foodBitmap0;
  /**
   * 食べ物画像２
   */
  hsbs::BitmapMono *_foodBitmap1;
  /**
   * 食べ物画像３
   */
  hsbs::BitmapMono *_foodBitmap2;

protected:
  //------------------------------
  // Protected
  //------------------------------
  /**
   * アクティブ時
   */
  void onActive() override {
    this->_monsBitmap = new MonsBitmap();
    this->_monsBitmap->setPosition(119, 135)->setScale(4, 4);
    this->stage.addChild(this->_monsBitmap);
    this->_monsBitmap->walkAnimation();
    this->_monsBitmap->update();
    this->_foodBitmap0 = new hsbs::BitmapMono(Img::Mono::food, Img::Mono::foodWidth, Img::Mono::foodHeight);
    this->_foodBitmap0->setPosition(34 + (4 * 4), -14 * 4)->setScale(4, 4);
    this->_foodBitmap1 = new hsbs::BitmapMono(Img::Mono::food, Img::Mono::foodWidth, Img::Mono::foodHeight);
    this->_foodBitmap1->setPosition(34 + (4 * 10), -10 * 4)->setScale(4, 4);
    this->_foodBitmap2 = new hsbs::BitmapMono(Img::Mono::food, Img::Mono::foodWidth, Img::Mono::foodHeight);
    this->_foodBitmap2->setPosition(34 + (4 * 6), -4 * 4)->setScale(4, 4);
    this->stage.addChild(this->_foodBitmap0);
    this->stage.addChild(this->_foodBitmap1);
    this->stage.addChild(this->_foodBitmap2);

    int minMonsX = ((int)this->_monsBitmap->monsW << 1) + (64) + 34;
    ;
    minMonsX = this->_monsBitmap->x < minMonsX ? minMonsX : this->_monsBitmap->x;

    this->activeTransition.add(
        // 食べ物が出てくる
        this->activeTransition.parallel(
            // 食べ物が出てくる
            this->activeTransition.parallel(
                this->activeTransition.tween(1600, hsbs::Ease::OUT_CUBIC)->add(&this->_foodBitmap0->y, this->_foodBitmap0->y + 20 * 4)->setDelay(400),
                this->activeTransition.tween(1600, hsbs::Ease::OUT_CUBIC)->add(&this->_foodBitmap1->y, this->_foodBitmap1->y + 20 * 4)->setDelay(200),
                this->activeTransition.tween(1600, hsbs::Ease::OUT_CUBIC)->add(&this->_foodBitmap2->y, this->_foodBitmap2->y + 20 * 4)->setDelay(0)),

            this->activeTransition.serial(
                // モンスが横にズレる
                this->activeTransition.tween(500, hsbs::Ease::LINEAR)->add(&this->_monsBitmap->x, minMonsX),
                // 食べるコマアニメ
                this->activeTransition.callback([this]() {
                  this->_monsBitmap->stopWalkFrame();
                }),
                this->activeTransition.wait(600),
                this->activeTransition.callback([this]() {
                  this->_monsBitmap->stopActionFrame();
                  this->_monsBitmap->x -= 4;
                  this->_foodBitmap1->visible = false;
                  soundUtil.eat();
                }),
                this->activeTransition.wait(200),
                this->activeTransition.callback([this]() {
                  this->_monsBitmap->stopWalkFrame();
                  this->_monsBitmap->x += 4;
                }),
                this->activeTransition.wait(600),
                this->activeTransition.callback([this]() {
                  this->_monsBitmap->stopActionFrame();
                  this->_monsBitmap->x -= 4;
                  this->_foodBitmap2->visible = false;
                  soundUtil.eat();
                }),
                this->activeTransition.wait(200),
                this->activeTransition.callback([this]() {
                  this->_monsBitmap->stopWalkFrame();
                  this->_monsBitmap->x += 4;
                }),
                this->activeTransition.wait(600),
                this->activeTransition.callback([this]() {
                  this->_monsBitmap->stopActionFrame();
                  this->_monsBitmap->x -= 4;
                  this->_foodBitmap0->visible = false;
                  soundUtil.eat();
                }),
                this->activeTransition.wait(200),
                this->activeTransition.callback([this]() {
                  this->_monsBitmap->stopWalkFrame();
                  this->_monsBitmap->x += 4;
                }))),
        this->activeTransition.wait(1000),
        this->activeTransition.callback([this]() {
          petStore.execFood();
        })

    );
  }

  /**
   * 非アクティブ時
   */
  void onDeactive() override {
    this->activeTransition.clear();
    this->stage.removeChild(this->_monsBitmap);
    delete this->_monsBitmap;
    this->stage.removeChild(this->_foodBitmap0);
    delete this->_foodBitmap0;
    this->stage.removeChild(this->_foodBitmap1);
    delete this->_foodBitmap1;
    this->stage.removeChild(this->_foodBitmap2);
    delete this->_foodBitmap2;
  }

  /**
   * フレーム更新時
   */
  void onEnterFrame() override {
    this->resetSleepTimestamp();
    this->_monsBitmap->update();
    this->_monsBitmap->x = ((int)this->_monsBitmap->x >> 2) << 2;
    this->_monsBitmap->y = ((int)this->_monsBitmap->y >> 2) << 2;
    this->_foodBitmap0->y = ((int)this->_foodBitmap0->y >> 2) << 2;
    this->_foodBitmap1->y = ((int)this->_foodBitmap1->y >> 2) << 2;
    this->_foodBitmap2->y = ((int)this->_foodBitmap2->y >> 2) << 2;
    if (this->activeTransition.getState() == hsbs::COMPLETE) {
      // トランジションが終了したら自動で遷移
      this->go("/food/page2");
    }
  }
};

} // namespace seamonsue

#endif