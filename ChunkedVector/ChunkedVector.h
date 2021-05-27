#pragma once
#include "../Vector/vector.h"
#include "Chunk.h"
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



private:
    Vector<Chunk<T>*> _map;
    size_t _chunkSize;
    size_t _tailIdx;
    Chunk<T>* _head;
    Chunk<T>* _tail;
};

template<class T>
ChunkedVector<T>::ChunkedVector(size_t chunkSize) {
    _chunkSize = chunkSize;

    _map.pushBack(new Chunk<T>(chunkSize));
    _head = _tail = _map[0];

    _tailIdx = 0;
}



template<class T>
void ChunkedVector<T>::pushFront(const T& value) {
    if (!_head->canPushRight()) {
        _map.pushFront(new Chunk<T>(_chunkSize));
        _head = _map[0];
        ++_tailIdx;
    }
    _head->pushRight(value);
}

template<class T>
void ChunkedVector<T>::popFront() {
    _head->popRight();

    if (_head->size() == 0) {
        _map.erase(0);
        _head = _map[0];
    }

}

template<class T>
void ChunkedVector<T>::pushBack(const T& value) {
    if (!_tail->canPushLeft()) {
        _map.pushBack(new Chunk<T>(_chunkSize));
        ++_tailIdx;
        _tail = _map[_tailIdx];
    }
    _tail->pushLeft(value);
}

template<class T>
void ChunkedVector<T>::popBack() {
    _tail->popLeft();

    if (_tail->size() == 0) {
        --_tailIdx;
        _tail = _map[_tailIdx];
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
    auto middleCellCount = &(_map[_map.size() - 1]) - &(_map[0]) - 1;
    if (_head == _tail) {
        return middleCellCount + _head->size();
    }
    return  _head->size() + middleCellCount * _chunkSize + _tail->size();

}

template<class T>
bool ChunkedVector<T>::isEmpty() {
    return size() == 0;
}
