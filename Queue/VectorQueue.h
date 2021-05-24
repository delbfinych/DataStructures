#pragma once
#include "./QueueImplementation.h"
#include "../Vector/vector.h"


template <class T>
class VectorQueue : public QueueImplementation<T> {
    Vector<T> _vector;
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
}

template<class T>
VectorQueue<T>::VectorQueue(const VectorQueue<T>& other) {
    _vector = other._vector;
}

template<class T>
VectorQueue<T>::VectorQueue(VectorQueue<T>&& other) noexcept {
    _vector = std::move(other._vector);
}

template<class T>
VectorQueue<T>& VectorQueue<T>::operator=(const VectorQueue& other) {
    if (this != &other) {
        *this = VectorQueue(other);
    }
    return *this;
}

template<class T>
VectorQueue<T>& VectorQueue<T>::operator=(VectorQueue&& other) noexcept {
    if (this != &other) {
        _vector = std::move(other._vector);
    }
    return *this;
}

template<class T>
void VectorQueue<T>::push(const T& value) {
    _vector.pushBack(value);
}

template<class T>
void VectorQueue<T>::pop() {
    _vector.erase(0);
}

template<class T>
const T& VectorQueue<T>::front() const {
    return _vector[0];
}

template<class T>
T& VectorQueue<T>::front() {
    return _vector[0];
}

template<class T>
bool VectorQueue<T>::isEmpty() const {
    return _vector.size() == 0;
}

template<class T>
size_t VectorQueue<T>::size() const {
    return _vector.size();
}
