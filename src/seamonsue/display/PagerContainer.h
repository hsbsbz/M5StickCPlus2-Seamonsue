

#ifndef _SEAMONSUE__DISPLAY__PAGER_CONTAINER_H_INCLUDE_
#define _SEAMONSUE__DISPLAY__PAGER_CONTAINER_H_INCLUDE_

#include "../../image_progmem.h"
#include "hsbs/core/ObjectList.h"
#include "hsbs/display/BitmapMono.h"
#include "hsbs/display/DisplayObjectContainer.h"

namespace seamonsue {

class PagerContainer : public hsbs::DisplayObjectContainer {

protected:
  //------------------------------
  // Protected
  //------------------------------
  hsbs::ObjectList<hsbs::BitmapMono *> _bitmapList;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief コンストラクタ
   */
  PagerContainer(int total, int page) {
    int space = 5;
    int x = 22;
    x -= (total * space) >> 1;
    for (int i = 0; i < total; i++) {
      hsbs::BitmapMono *bitmap = (i == (page - 1))
                                     ? static_cast<hsbs::BitmapMono*>(new Img::Mono::InfoPageActBitmap())
                                     : static_cast<hsbs::BitmapMono*>(new Img::Mono::InfoPageBitmap());
      bitmap->setPosition(x, 28);
      this->addChild(bitmap);
      this->_bitmapList.add(bitmap);
      x += space;
    }
  }

  /**
   * @brief デストラクタ
   */
  virtual ~PagerContainer() {
    while (this->_bitmapList.length()) {
      hsbs::BitmapMono* bitmap = this->_bitmapList.pop();
      this->removeChild(bitmap);
      delete bitmap;
    }
  }
};

} // namespace seamonsue

#endif