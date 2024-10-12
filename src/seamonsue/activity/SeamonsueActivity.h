#ifndef _SEAMONSUE__ACTIVITY__SEAMONSUE_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__SEAMONSUE_ACTIVITY_H_INCLUDE_

#include "hsbs/app/M5StickCPlust2Activity.h"
#include "hsbs/display/DisplayObjectContainer.h"

// 液晶のエリアの 4x 処理を個別ではなく、dotStage で一括で行えるようにするスーパークラス。

namespace seamonsue {

class SeamonsueActivity : public hsbs::M5StickCPlust2Activity {
protected:
  /**
   * @brief ドットエリアの表示コンテナ
   */
  hsbs::DisplayObjectContainer dotStage;
  
public:
  SeamonsueActivity() : hsbs::M5StickCPlust2Activity() {
    // ドットエリアの位置と縮尺を matrix で処理。
    this->dotStage.x = 34;
    this->dotStage.scaleX = 4;
    this->dotStage.scaleY = 4;
    this->stage.addChild(&this->dotStage);
  }

  virtual ~SeamonsueActivity() {
    this->stage.removeChild(&this->dotStage);
  }

};

} // namespace seamonsue

#endif