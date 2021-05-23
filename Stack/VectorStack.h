#pragma once
#include "StackImplementation.h"
#include "../Vector/vector.h"


template <class T>
class VectorStack : public StackImplementation<T> {
    Vector<T> vector;

public:
    VectorStack();
    VectorStack(const VectorStack<T>& other);
    VectorStack(VectorStack<T>&& other) noexcept;

    VectorStack<T>& operator=(const VectorStack& other);
    VectorStack<T>& operator=(VectorStack&& other) noexcept;

    ~VectorStack() = default;


    void push(const T& value);
    void pop();
    const T& top() const;
    T& top();
    bool isEmpty() const;
    size_t size() const;

};

template<class T>
VectorStack<T>::VectorStack() {
    vector = Vector<T>();
}

template<class T>
VectorStack<T>::VectorStack(const VectorStack<T>& other) {
    vector = other.vector;
}

template<class T>
VectorStack<T>::VectorStack(VectorStack<T>&& other) noexcept {
    vector = std::move(other.vector);
}

template<class T>
VectorStack<T>& VectorStack<T>::operator=(const VectorStack& other) {
    if (this != &other) {
        *this = VectorStack(other);
    }
    return *this;
}

template<class T>
VectorStack<T>& VectorStack<T>::operator=(VectorStack&& other) noexcept {
    if (this != &other) {
        vector = std::move(other.vector);
    }
    return *this;
}


template<class T>
void VectorStack<T>::push(const T& value) {
    vector.pushBack(value);
}

template<class T>
void VectorStack<T>::pop() {
    vector.popBack();
}

template<class T>
const T& VectorStack<T>::top() const {
    return vector[vector.size() - 1];
}

template<class T>
T& VectorStack<T>::top()  {
    return vector[vector.size() - 1];
}
template<class T>
bool VectorStack<T>::isEmpty() const {
    return vector.size() == 0;
}

template<class T>
size_t VectorStack<T>::size() const {
    return vector.size();
}

