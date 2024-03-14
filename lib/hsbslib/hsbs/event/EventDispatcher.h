#ifndef _HSBS__EVENT__EVENT_DISPATCHER_H_INCLUDE_
#define _HSBS__EVENT__EVENT_DISPATCHER_H_INCLUDE_

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace hsbs {

/**
 * @brief イベントハンドラ
 */
using EventHandler = std::function<void()>;

/**
 * @class EventDispatcher
 * @brief イベントの発生、登録した関数に伝達する
 */
class EventDispatcher {
private:
  std::unordered_map<std::string, std::vector<EventHandler>> _handlers;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief デストラクタ
   */
  virtual ~EventDispatcher();

  /**
   * @brief イベントハンドラを登録
   *
   * @param eventName
   * @param handler
   */
  void registerEvent(const std::string &eventName, EventHandler handler);

  /**
   * @brief イベントを発火
   *
   * @param eventName
   */
  void dispatchEvent(const std::string &eventName);

  /**
   * @brief 特定イベントのすべてのハンドラを破棄
   *
   * @param eventName
   */
  void clearEventHandlers(const std::string &eventName);

  /**
   * @brief すべてのイベントハンドラを破棄
   *
   */
  void clearAllEventHandlers();
};
} // namespace hsbs

#endif
