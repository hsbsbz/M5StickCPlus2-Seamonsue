#ifndef _SEAMONSUE__ACTIVITY__TEMPLATE_ACTIVITY_H_INCLUDE_
#define _SEAMONSUE__ACTIVITY__TEMPLATE_ACTIVITY_H_INCLUDE_

#include "hsbs/app/M5StickCPlust2Activity.h"

namespace seamonsue {

class TemplateActivity : public hsbs::M5StickCPlust2Activity {
public:
  TemplateActivity() {}
  virtual ~TemplateActivity() {}

  // 初回アクティブ時
  virtual void onInit() override {}

  // アクティブ時
  virtual void onActive() override {}

  // 非アクティブ時
  virtual void onDeactive() override {}

  // 毎フレーム
  virtual void onEnterFrame() override {}

  // ボタンを押した
  virtual void onPressButtonA() override {}
  virtual void onPressButtonB() override {}
  virtual void onPressButtonC() override {}

  // ボタンを離した
  virtual void onReleaseButtonA() override {}
  virtual void onReleaseButtonB() override {}
  virtual void onReleaseButtonC() override {}

  // ボタンを長押しした
  virtual void onLongPressButtonA() override {}
  virtual void onLongPressButtonB() override {}
  virtual void onLongPressButtonC() override {}

  virtual void onSleepBefore() override {}
};

} // namespace seamonsue

#endif