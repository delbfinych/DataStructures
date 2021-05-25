#pragma once




#include "./QueueImplementation.h"
#include "../SinglyLinkedList/List.h" // меняете на include вашего листа


template <class T>
class ListQueue : public QueueImplementation<T> {
    List<T> _list;
public:
    ListQueue();
    ListQueue(const ListQueue<T>& other);
    ListQueue(ListQueue<T>&& other) noexcept;

    ListQueue<T>& operator=(const ListQueue& other);
    ListQueue<T>& operator=(ListQueue&& other) noexcept;

    ~ListQueue() = default;


    void push(const T& value) override;
    void pop() override;
    const T& front() const override;
    T& front() override;
    bool isEmpty() const override;
    size_t size() const override;
};

template<class T>
ListQueue<T>::ListQueue() {
    _list = List<T>();
}

template<class T>
ListQueue<T>::ListQueue(const ListQueue<T>& other) {
    _list = other._list;
}

template<class T>
ListQueue<T>::ListQueue(ListQueue<T>&& other) noexcept {
    _list = std::move(other._list);
}

template<class T>
ListQueue<T>& ListQueue<T>::operator=(const ListQueue& other) {
    _list = other._list;
    return *this;
}

template<class T>
ListQueue<T>& ListQueue<T>::operator=(ListQueue&& other) noexcept {
    _list = std::move(other._list);
    return *this;
}

template<class T>
void ListQueue<T>::push(const T& value) {
    _list.pushBack(value);
}

template<class T>
void ListQueue<T>::pop() {
    _list.popFront();
}

template<class T>
const T& ListQueue<T>::front() const {
    return _list.front();
}

template<class T>
T& ListQueue<T>::front() {
    return _list.front();
}

template<class T>
bool ListQueue<T>::isEmpty() const {
    return _list.empty();
}

template<class T>
size_t ListQueue<T>::size() const {
    return _list.size();
}
