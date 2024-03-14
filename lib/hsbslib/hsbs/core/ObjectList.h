#ifndef _HSBS__CORE__OBJECT_LIST_H_INCLUDE_
#define _HSBS__CORE__OBJECT_LIST_H_INCLUDE_

#include <algorithm>
#include <vector>

namespace hsbs {

template <typename T>

/**
 * @class ObjectList
 * @brief 既存の std::vector のラッパー
 *
 */
class ObjectList {
private:
  //------------------------------
  // Private
  //------------------------------
  /**
   * @brief アイテムを登録しておく vector配列
   *
   */
  std::vector<T> _list;

public:
  //------------------------------
  // Public
  //------------------------------
  /**
   * @brief デストラクタ、内部のリストをクリアする
   */
  virtual ~ObjectList() {
    this->_list.clear();
  }

  /**
   * @brief アイテムを追加する（重複チェックなし）
   *
   * @param item 追加するアイテム
   */
  void push(T item) {
    this->_list.push_back(item);
  }

  /**
   * @brief アイテムを追加する（重複チェック有）
   *
   * @param item 追加するアイテム
   * @return 追加されたら true すでに登録済みなら false を返却
   */
  bool add(T item) {
    if (this->includes(item)) return false; // すでに存在する場合は追加しない
    this->_list.push_back(item);
    return true;
  }

  /**
   * @brief アイテムがすでに追加されているか評価
   *
   * @param item 評価するアイテム
   * @return アイテムが存在する場合は true を返却
   */
  bool includes(T item) {
    return std::find(this->_list.begin(), this->_list.end(), item) != _list.end();
  }

  /**
   * @brief アイテムを削除する
   *
   * @param item 削除するアイテム
   * @return 削除されたら true 存在しない場合は何もせず false を返却
   */
  bool remove(T item) {
    auto it = std::find(this->_list.begin(), this->_list.end(), item);
    if (it != _list.end()) {
      this->_list.erase(it);
      return true;
    }
    return false;
  }

  /**
   * @brief アイテムのインデックスを返却する
   *
   * @param item インデックスを取得するアイテム
   * @return アイテムのインデックス。存在しない場合は -1 を返却
   */
  int indexOf(T item) {
    auto it = std::find(_list.begin(), _list.end(), item);
    if (it != _list.end()) {
      return std::distance(_list.begin(), it);
    }
    return -1;
  }

  /**
   * @brief 登録されているアイテムの数を返却する
   *
   * @return アイテムの数
   */
  unsigned int length() {
    return this->_list.size();
  }

  /**
   * @brief 指定されたインデックスのアイテムを返却する
   * @param index インデックス
   *
   * @return 指定されたインデックスのアイテムを返却
   */
  T getAt(int index) { return this->_list.at(index); }

  /**
   * @brief 先頭のアイテムを取り出す
   *
   * @return 先頭のアイテム
   */
  T shift() {
    T item = this->_list.front();           // リストの最初の要素を取得
    this->_list.erase(this->_list.begin()); // リストの最初の要素を削除
    return item;
  }

  /**
   * @brief 最後尾のアイテムを取り出す
   *
   * @return 最後尾のアイテム
   */
  T pop() {
    T item = this->_list.back(); // リストの最後の要素を取得
    this->_list.pop_back();      // リストからその要素を削除
    return item;
  }

  /**
   * @brief アイテムを空にする
   */
  void clear() {
    this->_list.clear();
  }
};
} // namespace hsbs

#endif