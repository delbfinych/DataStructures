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

    T& operator[](size_t i);
    const T& operator[](size_t i) const;

    class Iterator {
    protected:
        T* _ptr;
        size_t _idx;
    public:
        Iterator(T* ptr, size_t idx);
        Iterator(const Iterator& it);

        Iterator operator+(size_t n);
        Iterator operator-(size_t n);

        Iterator& operator++ ();
        Iterator& operator-- ();

        Iterator operator++ (int);
        Iterator operator-- (int);

        bool operator!=(const Iterator& it) const;
        bool operator==(const Iterator& it ) const;

        T& operator*() const;
    };
    Iterator begin() const { return Iterator(&_head->front(), 0); };
    Iterator end() const { return Iterator(&(*_tail)[_tail->size()], size() - 1); };
private:
    Vector<Chunk<T>*> _map;
    size_t _chunkSize;
    size_t _tailIdx;
    Chunk<T>* _head;
    Chunk<T>* _tail;

    size_t frontOffset();
};

template<class T>
ChunkedVector<T>::Iterator::Iterator(T* ptr, size_t idx): _ptr(ptr), _idx(idx) {}

template<class T>
ChunkedVector<T>::Iterator::Iterator(const ChunkedVector::Iterator& it): _ptr(it._ptr), _idx(it._idx) {}

//template<class T>
//typename ChunkedVector<T>::Iterator ChunkedVector<T>::Iterator::operator+(size_t n) {
//    return ChunkedVector::Iterator(operator[](_idx + n), _idx + n);
//}
//
//template<class T>
//typename ChunkedVector<T>::Iterator ChunkedVector<T>::Iterator::operator-(size_t n) {
//    return ;
//}
//
//template<class T>
//typename ChunkedVector<T>::Iterator& ChunkedVector<T>::Iterator::operator++() {
////    return <#initializer#>;
//}
//
//template<class T>
//typename ChunkedVector<T>::Iterator& ChunkedVector<T>::Iterator::operator--() {
////    return <#initializer#>;
//}
//
//template<class T>
//typename ChunkedVector<T>::Iterator ChunkedVector<T>::Iterator::operator++(int) {
////    return ChunkedVector::Iterator(nullptr);
//}
//
//template<class T>
//typename ChunkedVector<T>::Iterator ChunkedVector<T>::Iterator::operator--(int) {
////    return ChunkedVector::Iterator(nullptr);
//}
//
//template<class T>
//bool ChunkedVector<T>::Iterator::operator!=(const ChunkedVector::Iterator& it) const {
//    return  _ptr != it._ptr;
//}
//
//template<class T>
//bool ChunkedVector<T>::Iterator::operator==(const ChunkedVector::Iterator& it) const {
//    return  _ptr == it._ptr;
//}
//
//template<class T>
//T& ChunkedVector<T>::Iterator::operator*() const {
//    return _ptr;
//}

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
        return _head->size();
    }
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
