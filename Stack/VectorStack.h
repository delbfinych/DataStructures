#pragma once
#include "StackImplementation.h"
#include "../Vector/vector.h"


template <class T>
class VectorStack : public StackImplementation<T> {
    Vector<T> _vector;
public:
    VectorStack();
    VectorStack(const VectorStack<T>& other);
    VectorStack(VectorStack<T>&& other) noexcept;

    VectorStack<T>& operator=(const VectorStack& other);
    VectorStack<T>& operator=(VectorStack&& other) noexcept;

    ~VectorStack() = default;


    void push(const T& value) override;
    void pop() override;
    const T& top() const override;
    T& top() override;
    bool isEmpty() const override;
    size_t size() const override;

};

template<class T>
VectorStack<T>::VectorStack() {
    _vector = Vector<T>();
}

template<class T>
VectorStack<T>::VectorStack(const VectorStack<T>& other) {
    _vector = other._vector;
}

template<class T>
VectorStack<T>::VectorStack(VectorStack<T>&& other) noexcept {
    _vector = std::move(other._vector);
}

template<class T>
VectorStack<T>& VectorStack<T>::operator=(const VectorStack& other) {
    _vector = other._vector;
    return *this;
}

template<class T>
VectorStack<T>& VectorStack<T>::operator=(VectorStack&& other) noexcept {
    _vector = std::move(other._vector);
    return *this;
}


template<class T>
void VectorStack<T>::push(const T& value) {
    _vector.pushBack(value);
}

template<class T>
void VectorStack<T>::pop() {
    _vector.popBack();
}

template<class T>
const T& VectorStack<T>::top() const {
    return _vector[_vector.size() - 1];
}

template<class T>
T& VectorStack<T>::top()  {
    return _vector[_vector.size() - 1];
}
template<class T>
bool VectorStack<T>::isEmpty() const {
    return _vector.size() == 0;
}

template<class T>
size_t VectorStack<T>::size() const {
    return _vector.size();
}

