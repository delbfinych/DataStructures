#pragma once
#include "./QueueImplementation.h"
#include "../Vector/vector.h"
#include <stdexcept>

template <class T>
class VectorQueue : public QueueImplementation<T> {
    Vector<T> _vector;
    size_t _begin;
public:
    VectorQueue();
    VectorQueue(const VectorQueue<T>& other);
    VectorQueue(VectorQueue<T>&& other) noexcept;

    VectorQueue<T>& operator=(const VectorQueue& other);
    VectorQueue<T>& operator=(VectorQueue&& other) noexcept;

    ~VectorQueue() = default;

    void push(const T& value) override;
    void pop() override;
    const T& front() const override;
    T& front() override;
    bool isEmpty() const override;
    size_t size() const override;

};

template<class T>
VectorQueue<T>::VectorQueue() {
    _vector = Vector<T>();
    _begin  = 0;
}

template<class T>
VectorQueue<T>::VectorQueue(const VectorQueue<T>& other) {
    _vector = other._vector;
    _begin  = other._begin;
}

template<class T>
VectorQueue<T>::VectorQueue(VectorQueue<T>&& other) noexcept {
    _vector = std::move(other._vector);
    _begin  = other._begin;
}

template<class T>
VectorQueue<T>& VectorQueue<T>::operator=(const VectorQueue& other) {
    _vector = other._vector;
    return *this;
}

template<class T>
VectorQueue<T>& VectorQueue<T>::operator=(VectorQueue&& other) noexcept {
    _vector = std::move(other._vector);
    return *this;
}

template<class T>
void VectorQueue<T>::push(const T& value) {
    _vector.pushBack(value);
}

template<class T>
void VectorQueue<T>::pop() {
    if (!isEmpty()) {
        ++_begin;
    }
//    _vector.erase(0);
}

template<class T>
const T& VectorQueue<T>::front() const {
    if (isEmpty()) {
        throw std::range_error("Queue is empty");
    }
    return _vector[_begin];
}

template<class T>
T& VectorQueue<T>::front() {
    if (isEmpty()) {
        throw std::range_error("Queue is empty");
    }
    return _vector[_begin];
}

template<class T>
bool VectorQueue<T>::isEmpty() const {
    return _begin == _vector.size();
}

template<class T>
size_t VectorQueue<T>::size() const {
    return _vector.size() - _begin;
}
