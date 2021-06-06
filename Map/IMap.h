#pragma once

template <class K, class V>
class IMap {
public:
    virtual void add(const K& key, const V& val) = 0;
    virtual const V& find(const K& key) const = 0;
//    virtual V& find() = 0;
    virtual void remove(const K& key) = 0;
};