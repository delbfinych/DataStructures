#pragma once
#include "../Vector/vector.h"
template <class T>
class Chunk {
public:
    Chunk(size_t size);
    ~Chunk() = default;

    // пуш справа налево(для пушфронт)
    void pushRight(const T& value);
    void popRight();
    // пуш слева направо(для пушбек)
    void pushLeft(const T& value);
    void popLeft();

    const T& back() const;
    T& back();
    const T& front() const;
    T& front();

    size_t size() const;
    bool isEmpty() const;

    T& operator[](size_t i);
    const T& operator[](size_t i) const;

    bool canPushRight() const;
    bool canPushLeft() const;
private:
    Vector<T> _vector;
    size_t _size;
    size_t _rIdx;
    size_t _lIdx;
};

template<class T>
Chunk<T>::Chunk(size_t size) {
    _size = 0;
    _vector.reserve(size);
    _rIdx = size;
    _lIdx = 0;
}

template<class T>
void Chunk<T>::pushRight(const T& value) {
    if (_size != _vector.capacity()) {
        _vector[--_rIdx] = value;
        _lIdx = _vector.capacity() - 1;
        ++_size;
    }
}

template<class T>
void Chunk<T>::popRight() {
    ++_rIdx;
    --_size;
}

template<class T>
void Chunk<T>::pushLeft(const T& value) {
    if (_size != _vector.capacity()) {
        _vector[_lIdx] = value;
        ++_lIdx;
        ++_size;
        _rIdx = 0;
    }
}

template<class T>
void Chunk<T>::popLeft() {
    --_lIdx;
    --_size;
}

template<class T>
size_t Chunk<T>::size() const {
    return _size;
}

template<class T>
bool Chunk<T>::isEmpty() const {
    return _size == 0;
}

template<class T>
const T& Chunk<T>::back() const {
    return _vector[_lIdx - 1];
}

template<class T>
T& Chunk<T>::back() {
    return _vector[_lIdx - 1];
}

template<class T>
const T& Chunk<T>::front() const {
    return _vector[_rIdx];
}

template<class T>
T& Chunk<T>::front() {
    return _vector[_rIdx];
}

template<class T>
bool Chunk<T>::canPushRight() const {
    return _rIdx != 0 && _size != _vector.capacity();
}

template<class T>
bool Chunk<T>::canPushLeft() const {
    return _lIdx - 1 != _vector.capacity() - 1 && _size != _vector.capacity();
}

template<class T>
T& Chunk<T>::operator[](size_t i) {
    return _vector[i];
}

template<class T>
const T& Chunk<T>::operator[](size_t i) const {
    return _vector[i];
}
