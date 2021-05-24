#pragma once

#include <cstddef>
#include "QueueImplementation.h"
#include "ListQueue.h"
#include "VectorQueue.h"

enum class QueueContainer {
    Vector = 0,
    List,

};


template <class T>
class Queue
{
public:
    Queue(QueueContainer container = QueueContainer::Vector);
    Queue(const T* valueArray, size_t arraySize,
          QueueContainer container = QueueContainer::Vector);

    explicit Queue(const Queue& other);
    Queue& operator=(const Queue& other);

    Queue(Queue&& other) noexcept;
    Queue& operator=(Queue&& other) noexcept;

    ~Queue();

    void push(const T& value);
    void pop();
    T& front();
    const T& front() const;
    bool isEmpty() const;
    size_t size() const;
private:
    QueueImplementation<T>* _pimpl = nullptr;
    QueueContainer _containerType;
};

template<class T>
Queue<T>::Queue(QueueContainer container): _containerType(container) {
    switch (container)
    {
        case QueueContainer::List: {
            _pimpl = new ListQueue<T>();
            break;
        }
        case QueueContainer::Vector: {
            _pimpl = new VectorQueue<T>();
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}

template<class T>
Queue<T>::Queue(const T* valueArray, size_t arraySize, QueueContainer container) {

}

template<class T>
Queue<T>::Queue(const Queue& other): Queue<T>(other._containerType) {


    switch (_containerType)
    {
        case QueueContainer::List: {
            _pimpl = new ListQueue<T>((ListQueue<T>&)(*other._pimpl));
            break;
        }
        case QueueContainer::Vector: {
            _pimpl = new VectorQueue<T>((VectorQueue<T>&)(*other._pimpl));
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        *this = Queue(other);
    }
    return *this;
}

template<class T>
Queue<T>::Queue(Queue&& other) noexcept {
    _pimpl = std::exchange(other._pimpl, nullptr);
}

template<class T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept {
    if (this != &other) {
        _pimpl = std::exchange(other._pimpl, nullptr);
    }
    return *this;
}

template<class T>
Queue<T>::~Queue() {
    delete _pimpl;
}

template<class T>
void Queue<T>::push(const T& value) {
    _pimpl->push(value);
}

template<class T>
void Queue<T>::pop() {
    _pimpl->pop();
}

template<class T>
T& Queue<T>::front() {
    return _pimpl->front();
}

template<class T>
const T& Queue<T>::front() const {
    return _pimpl->front();
}

template<class T>
bool Queue<T>::isEmpty() const {
    return _pimpl->isEmpty();
}

template<class T>
size_t Queue<T>::size() const {
    return _pimpl->size();
}
