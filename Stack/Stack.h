#pragma once
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"
#include <stdexcept>
#include <cstddef>


enum class StackContainer {
	Vector = 0,
	List,

};


template <class T>
class Stack
{
public:
	Stack(StackContainer container = StackContainer::Vector);
	// элементы массива последовательно подкладываются в стек
	Stack(const T* valueArray, size_t arraySize,
          StackContainer container = StackContainer::Vector);

	explicit Stack(const Stack& other);
	Stack& operator=(const Stack& other);

    Stack(Stack&& other) noexcept;
    Stack& operator=(Stack&& other) noexcept;


	~Stack();

	// добавление в хвост
	void push(const T& value);
	// удаление с хвоста
	void pop();
	// посмотреть элемент в хвосте
	T& top();
	const T& top() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;
private:
    StackImplementation<T>* _pimpl = nullptr;
	StackContainer _containerType;
};

template <class T>
Stack<T>::Stack(StackContainer container)
        : _containerType(container)
{
    switch (container)
    {
        case StackContainer::List: {
            _pimpl = new ListStack<T>();
            break;
        }
        case StackContainer::Vector: {
            _pimpl = new VectorStack<T>();
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}

template <class T>
Stack<T>::Stack(const T* valueArray, const size_t arraySize, StackContainer container) {

}

template <class T>
Stack<T>::Stack(const Stack& other): Stack<T>(other._containerType) {
    switch (_containerType)
    {
        case StackContainer::List: {
            _pimpl = new ListStack<T>(*(static_cast<ListStack<T>*>(other._pimpl)));
            break;
        }
        case StackContainer::Vector: {
            _pimpl = new VectorStack<T>(*(static_cast<VectorStack<T>*>(other._pimpl)));
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        *this = Stack(other);
    }
    return *this;
}

template<class T>
Stack<T>::Stack(Stack&& other) noexcept {
    _pimpl = std::exchange(other._pimpl, nullptr);
}

template<class T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {
    if (this != &other) {
        _pimpl = std::exchange(other._pimpl, nullptr);
    }
    return *this;
}

template <class T>
Stack<T>::~Stack() {
    delete _pimpl;
}

template <class T>
void Stack<T>::push(const T& value) {
    _pimpl->push(value);
}

template <class T>
void Stack<T>::pop() {
    _pimpl->pop();
}

template <class T>
T& Stack<T>::top() {
    return _pimpl->top();
}

template <class T>
const T& Stack<T>::top() const {
    return _pimpl->top();
}

template <class T>
bool Stack<T>::isEmpty() const {
    return _pimpl->isEmpty();
}

template <class T>
size_t Stack<T>::size() const {
    return _pimpl->size();
}

