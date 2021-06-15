#pragma once
#include "../Vector/vector.h"
#include "Chunk.h"
#include <memory>

using std::make_shared, std::shared_ptr;

template <class T>
class ChunkedVector {
public:
    ChunkedVector(size_t chunkSize);
    ~ChunkedVector() = default;

    void pushFront(const T& value);
    void popFront();
    void pushBack(const T& value);
    void popBack();
    const T& back() const;
    T& back();
    const T& front() const;
    T& front();
    size_t size();
    bool isEmpty();

    T& operator[](size_t i);
    const T& operator[](size_t i) const;

private:
    Vector<shared_ptr<Chunk<T>>> _map;
    size_t _chunkSize;
    size_t _tailIdx;
    shared_ptr<Chunk<T>> _head;
    shared_ptr<Chunk<T>> _tail;

    size_t frontOffset();
};

template<class T>
ChunkedVector<T>::ChunkedVector(size_t chunkSize) {
    _chunkSize = chunkSize;

    _map.pushBack(make_shared<Chunk<T>>(chunkSize));
    _head = _tail = _map[0];

    _tailIdx = 0;
}



template<class T>
void ChunkedVector<T>::pushFront(const T& value) {
    if (!_head || !_head->canPushRight()) {
        _map.pushFront(make_shared<Chunk<T>>(_chunkSize));

        if (!_head) {
            _tail = _head = _map[0];
        }
        else {
            _head = _map[0];
        }

    }
    _head->pushRight(value);
}

template<class T>
void ChunkedVector<T>::popFront() {
    _head->popRight();

    if (_head->size() == 0) {
        _map.erase(0);
        if (_map.size()) {
            _head = _map[0];
        }
        else {
            _head = _tail = nullptr;
            _tailIdx = 0;
        }

    }

}

template<class T>
void ChunkedVector<T>::pushBack(const T& value) {
    if (!_tail || !_tail->canPushLeft()) {
        _map.pushBack(make_shared<Chunk<T>>(_chunkSize));

        if (!_tail) {
            _head =  _tail = _map[_tailIdx];
        }
        else {
            ++_tailIdx;
            _tail = _map[_tailIdx];
        }


    }
    _tail->pushLeft(value);
}

template<class T>
void ChunkedVector<T>::popBack() {
    _tail->popLeft();

    if (_tail->size() == 0) {
        _map.popBack();
        if (_map.size()) {
            --_tailIdx;
            _tail = _map[_tailIdx];
        }
        else {
            _tail = _head = nullptr;
        }
    }
}

template<class T>
const T& ChunkedVector<T>::back() const {
    return _tail->back();
}

template<class T>
T& ChunkedVector<T>::back() {
    return _tail->back();
}

template<class T>
const T& ChunkedVector<T>::front() const {
    return _head->front();
}

template<class T>
T& ChunkedVector<T>::front() {
    return _head->front();
}

template<class T>
size_t ChunkedVector<T>::size() {
    if (!_head) {
        return 0;
    }
    if (_head == _tail) {
        return _head->size();
    }
    auto middleCellCount = &(_map[_map.size() - 1]) - &(_map[0]) - 1;

    return  _head->size() + middleCellCount * _chunkSize + _tail->size();

}

template<class T>
bool ChunkedVector<T>::isEmpty() {
    return size() == 0;
}

template<class T>
size_t ChunkedVector<T>::frontOffset() {
    return &_head->front() - &(*_map[0])[0];
}

template<class T>
T& ChunkedVector<T>::operator[](size_t i) {
    i += frontOffset();
    return (*_map[i / _chunkSize])[i % _chunkSize];
}

template<class T>
const T& ChunkedVector<T>::operator[](size_t i) const {
    i += frontOffset();
    return (*_map[i / _chunkSize])[i % _chunkSize];
}
