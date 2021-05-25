#pragma once

#include "StackImplementation.h"
#include "../SinglyLinkedList/List.h" // меняете на include вашего листа


template <class T>
class ListStack : public StackImplementation<T> {
    List<T> _list;
public:
    ListStack();
    ListStack(const ListStack<T>& other);
    ListStack(ListStack<T>&& other) noexcept;

    ListStack<T>& operator=(const ListStack& other);
    ListStack<T>& operator=(ListStack&& other) noexcept;

    ~ListStack() = default;


    void push(const T& value) override;
    void pop() override;
    const T& top() const override;
    T& top() override;
    bool isEmpty() const override;
    size_t size() const override;
};

template<class T>
ListStack<T>::ListStack() {
    _list = List<T>();
}

template<class T>
ListStack<T>::ListStack(const ListStack<T>& other) {
    _list = other._list;
}

template<class T>
ListStack<T>::ListStack(ListStack<T>&& other) noexcept {
    _list = std::move(other._list);
}

template<class T>
ListStack<T>& ListStack<T>::operator=(const ListStack& other) {
    _list = other._list;
    return *this;
}

template<class T>
ListStack<T>& ListStack<T>::operator=(ListStack&& other) noexcept {
    _list = std::move(other._list);
    return *this;
}


template<class T>
void ListStack<T>::push(const T& value) {
    _list.pushFront(value);
}

template<class T>
void ListStack<T>::pop() {
    _list.popFront();
}

template<class T>
const T& ListStack<T>::top() const {
    return _list.front();
}

template<class T>
T& ListStack<T>::top() {
    return _list.front();
}

template<class T>
bool ListStack<T>::isEmpty() const {
    return _list.empty();
}

template<class T>
size_t ListStack<T>::size() const {
    return _list.size();
}

