#pragma once

#include "StackImplementation.h"
#include "../SinglyLinkedList/List.h" // меняете на include вашего листа


template <class T>
class ListStack : public StackImplementation<T> {
    List<T> list;

public:
    ListStack();
    ListStack(const ListStack<T>& other);
    ListStack(ListStack<T>&& other) noexcept;

    ListStack<T>& operator=(const ListStack& other);
    ListStack<T>& operator=(ListStack&& other) noexcept;

    ~ListStack() = default;


    void push(const T& value);
    void pop();
    const T& top() const;
    T& top();
    bool isEmpty() const;
    size_t size() const;
};

template<class T>
ListStack<T>::ListStack() {
    list = List<T>();
}

template<class T>
ListStack<T>::ListStack(const ListStack<T>& other) {
    list = other.list;
}

template<class T>
ListStack<T>::ListStack(ListStack<T>&& other) noexcept {
    list = std::move(other.list);
}

template<class T>
ListStack<T>& ListStack<T>::operator=(const ListStack& other) {
    if (this != &other) {
        *this = ListStack(other);
    }
    return *this;
}

template<class T>
ListStack<T>& ListStack<T>::operator=(ListStack&& other) noexcept {
    if (this != &other) {
        list = std::move(other.list);
    }
    return *this;
}


template<class T>
void ListStack<T>::push(const T& value) {
    list.pushFront(value);
}

template<class T>
void ListStack<T>::pop() {
    list.popFront();
}

template<class T>
const T& ListStack<T>::top() const {
    return list.front();
}

template<class T>
T& ListStack<T>::top() {
    return list.front();
}

template<class T>
bool ListStack<T>::isEmpty() const {
    return list.empty();
}

template<class T>
size_t ListStack<T>::size() const {
    return list.size();
}

