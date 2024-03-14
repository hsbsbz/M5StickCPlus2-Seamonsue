
#include "M5StickCPlust2Activity.h"
#include "M5StickCPlust2App.h"

namespace hsbs {

void M5StickCPlust2Activity::resetSleepTimestamp() {
  if (this->root == nullptr) return;

  M5StickCPlust2App *app = static_cast<M5StickCPlust2App *>(this->root);
  app->resetSleepTimestamp();
}

} // namespace hsbs
