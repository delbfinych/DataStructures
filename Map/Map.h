#pragma once
#include "IMap.h"
#include "./BST.h"

namespace {
    template <typename T1, typename T2>
    class Pair {
    public:
        T1 fst;
        T2 snd;
        explicit Pair(const T1& fst = T1(),
                      const T2& snd = T2())
                      :fst(fst), snd(snd)
                      {}

        bool operator==(const Pair& lp) const {
            return fst == lp.fst;
        }
        bool operator>=(const Pair& lp) const {
            return fst >= lp.fst;
        }
        bool operator<=(const Pair& lp) const {
            return fst <= lp.fst;
        }
        bool operator>(const Pair& lp) const {
            return fst > lp.fst;;
        }
        bool operator<(const Pair& lp) const {
            return fst < lp.fst;
        }
        bool operator!=(const Pair& lp) const {
            return !operator==(lp);
        }
    };
}
using std::pair;
template <class K, class V>
class Map: public IMap<K, V> {
public:
    Map();
    Map(const Map& other);
    Map(Map&& other);

    Map& operator=(const Map& other);
    Map& operator=(Map&& other);

    //TODO
    ~Map() = default;

    void add(const K& key, const V& val) override;
    void remove(const K& key) override;
    const V& find(const K& key) const override;
    const V& operator[](const K& key) const;
private:
    BST<Pair<K,V>> _tree;
};

template<class K, class V>
void Map<K, V>::add(const K& key, const V& val) {
     Pair<K,V> p(key, val);
    _tree.insert(p);
}

template<class K, class V>
void Map<K, V>::remove(const K& key) {
    Pair<K,V> p(key);
    _tree.remove(p);
}

template<class K, class V>
const V& Map<K, V>::find(const K& key) const {
    Pair<K,V> p(key);
    return _tree.find(p).snd;
}

template<class K, class V>
Map<K, V>::Map() {

}

template<class K, class V>
Map<K, V>::Map(const Map& other) {
    _tree = other._tree;
}

template<class K, class V>
Map<K, V>::Map(Map&& other) {
    _tree = std::move(other._tree);
}

template<class K, class V>
Map<K,V>& Map<K, V>::operator=(const Map& other) {
    _tree = other._tree;
    return *this;
}

template<class K, class V>
Map<K,V>& Map<K, V>::operator=(Map&& other) {
    _tree = std::move(other._tree);
    return *this;
}

template<class K, class V>
const V& Map<K, V>::operator[](const K& key) const {
    return find(key);
}
