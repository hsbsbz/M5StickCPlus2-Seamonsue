

#include "EventDispatcher.h"

namespace hsbs {

EventDispatcher::~EventDispatcher() {
  this->_handlers.clear();
}

void EventDispatcher::registerEvent(const std::string &eventName, EventHandler handler) {
  this->_handlers[eventName].push_back(handler);
}

void EventDispatcher::dispatchEvent(const std::string &eventName) {
  auto it = this->_handlers.find(eventName);
  if (it != this->_handlers.end()) {
    for (auto &handler : it->second) {
      handler();
    }
  }
}

void EventDispatcher::clearEventHandlers(const std::string &eventName) {
  this->_handlers[eventName].clear();
}

void EventDispatcher::clearAllEventHandlers() {
  this->_handlers.clear();
}

} // namespace hsbs
