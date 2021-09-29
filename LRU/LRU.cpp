#include <memory>
#include <unordered_map>
class LRU {
 public:
  LRU(int key, int data) : _key(key), _data(data){};
  int _key, _data;
  std::shared_ptr<LRU> _next;
  std::shared_ptr<LRU> _pre;
};
class LRUCache {
 public:
  std::unordered_map<int, std::shared_ptr<LRU>> _get;
  std::shared_ptr<LRU> head;
  int cap;
  LRUCache(int capacity) { cap = capacity; }

  int get(int key) {
    auto it = _get.find(key);
    if (it == _get.end()) {
      return -1;
    } else {
      int ans = _get[key]->_data;
      if (it->second != head) {
        std::shared_ptr<LRU> headpre = head->_pre;
        std::shared_ptr<LRU> tmppre = it->second->_pre;
        std::shared_ptr<LRU> tmpnext = it->second->_next;

        tmppre->_next = tmpnext;
        tmpnext->_pre = tmppre;
        _get.erase(it);
        put(key, ans);
      }
      return ans;
    }
  }

  void Puts(int key, int value) {
    std::shared_ptr<LRU> Tmp = std::make_shared<LRU>(key, value);
    auto it = _get.find(key);
    std::shared_ptr<LRU> headpre = head->_pre;

    Tmp->_pre = headpre;
    Tmp->_next = head;
    head->_pre = Tmp;
    headpre->_next = Tmp;

    head = Tmp;
    _get[key] = head;
  }
  void put(int key, int value) {
    if (_get.size() == 0) {
      std::shared_ptr<LRU> Tmp = std::make_shared<LRU>(key, value);
      Tmp->_next = Tmp, Tmp->_pre = Tmp;
      head = Tmp;
      _get[key] = head;
      return;
    }
    std::shared_ptr<LRU> Tmp = std::make_shared<LRU>(key, value);
    auto it = _get.find(key);
    if (it != _get.end()) {
      if (it->second == head) {
        it->second->_data = value;
        return;
      }
      std::shared_ptr<LRU> tmppre = it->second->_pre;
      std::shared_ptr<LRU> tmpnext = it->second->_next;

      tmppre->_next = tmpnext;
      tmpnext->_pre = tmppre;
      _get.erase(it);
      Puts(key, value);

    } else {
      std::shared_ptr<LRU> headpre = head->_pre;

      Tmp->_pre = headpre;
      Tmp->_next = head;
      head->_pre = Tmp;
      headpre->_next = Tmp;

      head = Tmp;
      _get[key] = head;
      if (_get.size() > cap) {
        auto tail = head->_pre;
        auto tailpre = tail->_pre;
        auto tailnext = head;
        tailpre->_next = head;
        head->_pre = tailpre;
        auto it = _get.find(tail->_key);
        _get.erase(it);
      }
    }
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
