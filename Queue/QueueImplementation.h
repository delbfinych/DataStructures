#pragma once

#include <cstddef>


template <class T>
class QueueImplementation {
public:
	virtual void push(const T& value) = 0;
	virtual void pop() = 0;
	virtual const T& front() const = 0;
	virtual T& front() = 0;
	virtual bool isEmpty() const = 0;
	virtual size_t size() const = 0;
	virtual ~QueueImplementation() {};
};
