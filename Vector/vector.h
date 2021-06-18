#pragma once
#include <initializer_list>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <utility>

#include "IVector.h"

enum class ResizeStrategy {
    Additive,
    Multiplicative
};

template <class T>
class Vector: public IVector<T> {
    T* _data;
    size_t _size;
    size_t _capacity;
    float _coef;
    ResizeStrategy _strategy;

    float loadFactor() const;
    void expandIfNeeded();

    static T* allocate(size_t size);
    static void deallocate(const T* data);
public:
    class Iterator;
    class ConstantIterator;
    class ReverseIterator;

    // заполнить вектор значениями T()
    Vector(size_t size = 0,
            ResizeStrategy strategy = ResizeStrategy::Multiplicative,
    float coef = 2.0f);
    // заполнить вектор значениями value
    Vector(size_t size,
    T value,
            ResizeStrategy strategy = ResizeStrategy::Multiplicative,
    float coef = 2.0f);
    Vector(std::initializer_list<T> list);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept ;
    ~Vector() override;

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    void reserve(size_t newCapacity) override;
    void resize(size_t count) override;
    void resize(size_t count, const T& val) override;

    T& at(size_t idx) override;
    const T& at(size_t idx) const override;
    T& operator[](size_t i) override;
    const T& operator[](size_t i) const override;

    void pushBack(const T& value) override;
    void pushFront(const T &value) override;
    void insert(size_t idx, const T& value) override;
    void insert(size_t i, const Vector& value);
    void insert(const Iterator& it, const T& value);
    void insert(const Iterator& it, const Vector& value);

    void clear() override;
    void erase(size_t i) override;
    void erase(size_t i, size_t len) override;
    void popBack() override;

    long long find(const T &value) const override;

    size_t size() const override;
    size_t capacity() const override;


    class Iterator {
    protected:
        T* _ptr;
    public:
        Iterator(T* ptr);
        Iterator(const Iterator& it);

        Iterator operator+(size_t n);
        Iterator operator-(size_t n);

        Iterator& operator++ ();
        Iterator& operator-- ();

        Iterator operator++ (int);
        Iterator operator-- (int);

        bool operator!=(const Iterator& it) const;
        bool operator==(const Iterator& it ) const;

        T& operator*() const;
    };
    Iterator begin() const { return &_data[0]; };
    Iterator end() const { return &_data[_size]; };


    class ConstantIterator: public Iterator {
    public:
        ConstantIterator(T* ptr): Iterator(ptr) {};
        ConstantIterator(const ConstantIterator& it): Iterator(it) {};


        const T& operator*() const { return *Iterator::_ptr; };
    };
    ConstantIterator cbegin() const { return &_data[0]; };
    ConstantIterator cend() const { return &_data[_size]; };


    class ReverseIterator {
    private:
        T* _ptr;
    public:
        ReverseIterator(T* ptr);
        ReverseIterator(const ReverseIterator& it);

        ReverseIterator operator+(size_t n);
        ReverseIterator operator-(size_t n);

        ReverseIterator& operator++ ();
        ReverseIterator& operator-- ();

        ReverseIterator operator++ (int);
        ReverseIterator operator-- (int);

        bool operator!=(const ReverseIterator& it) const;
        bool operator==(const ReverseIterator& it ) const;

        T& operator*() const;
    };

    ReverseIterator rbegin() const { return &_data[_size - 1]; }
    ReverseIterator rend() const { return &_data[-1]; }
};


template <class T>
void Vector<T>::pushFront(const T& value) {
    insert(0, value);
}


template <class T>
const T& Vector<T>::at(size_t idx) const {
    if (idx >= _capacity) {
        throw std::range_error("at(): Invalid pos");
    }
    return _data[idx];
}


template <class T>
T& Vector<T>::at(size_t idx) {
    if (idx >= _capacity) {
        throw std::range_error("at(): Invalid pos");
    }
    return _data[idx];
}

template <class T>
void Vector<T>::clear() {
    // remove content
    _size = 0;
}

template <class T>
void Vector<T>::insert(size_t idx, const T& value) {
    if (idx > _size) {
        return;
    }
    expandIfNeeded();
    if (idx == _size) {
        _data[_size] = value;
    }
    else {
        memcpy(_data + idx + 1, _data + idx, (_size - idx) * sizeof(T));
        _data[idx] = value;
    }
    ++_size;
}

template <class T>
T* Vector<T>::allocate(size_t size) {
    return new T[size];
}

template <class T>
void Vector<T>::deallocate(const T* data) {
    delete[] data;
}

template <class T>
void Vector<T>::pushBack(const T& value) {
    insert(_size, value);
}

template <class T>
Vector<T>::Vector(const Vector& other) {
    _data = allocate(other._size);
    memcpy(_data, other._data, sizeof(T) * other._size);
    _size = _capacity = other._size;
    _coef = other._coef;
    _strategy = other._strategy;
}

template <class T>
Vector<T>::Vector(Vector&& other) noexcept {
    _data     = std::exchange(other._data, nullptr);
    _size     = std::exchange(other._size, 0);
    _capacity = std::exchange(other._capacity, 0);
    _coef     = std::exchange(other._coef, 2);
    _strategy = std::exchange(other._strategy, ResizeStrategy::Multiplicative);
}

template <class T>
size_t Vector<T>::size() const {
    return _size;
}

template <class T>
void Vector<T>::erase(size_t idx) {
    for (size_t i = idx + 1; i < _size; ++i) {
        _data[i - 1] = _data[i];
    }
    --_size;
}

template <class T>
void Vector<T>::erase(size_t idx, size_t len) {
    if (len >= _size) {
        len = _size - idx;
    }
    for (size_t i = idx + len; i < _size; ++i) {
        _data[i - len] = _data[i];
    }
    _size -= len;
}

template <class T>
long long Vector<T>::find(const T& value) const {
    for (size_t i = 0; i < size(); ++i) {
        if (_data[i] == value) {
            return i;
        }
    }
    return -1;
}

template <class T>
void Vector<T>::popBack() {
    --_size;
}

template <class T>
T& Vector<T>::operator[](size_t i) {
    return at(i);
}

template <class T>
const T& Vector<T>::operator[](size_t i) const {
    return at(i);
}

template <class T>
Vector<T>::~Vector() {
    deallocate(_data);
}

template <class T>
void Vector<T>::reserve(size_t newCapacity) {
    if (newCapacity <= _capacity) {
        return;
    }
    _capacity = newCapacity;
    auto newData = allocate(newCapacity);
    // TODO: move instead of copy?
    if (_data) {
        memcpy(newData, _data, _size * sizeof(T));
        deallocate(_data);
    }
    _data = newData;
}

template <class T>
void Vector<T>::resize(size_t count, const T& val) {
    size_t oldSize = _size;
    _size = count;
    reserve(count);
    for (size_t i = oldSize; i < count; ++i) {
        _data[i] = val;
    }
}

template <class T>
void Vector<T>::resize(size_t count) {
    resize(count, 0);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        *this = Vector(other);
    }
    return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        deallocate(_data);
        _data     = std::exchange(other._data, nullptr);
        _size     = std::exchange(other._size, 0);
        _capacity = std::exchange(other._capacity, 0);
        _coef     = std::exchange(other._coef, 2);
        _strategy = std::exchange(other._strategy, ResizeStrategy::Multiplicative);
    }
    return *this;
}

template <class T>
float Vector<T>::loadFactor() const {
    return (float)_size / _capacity;
}

template <class T>
size_t Vector<T>::capacity() const {
    return _capacity;
}

template <class T>
void Vector<T>::expandIfNeeded() {
    if (capacity() == 0 || loadFactor() >= 0.8) {
        size_t newCap = capacity();
        while (newCap == 0 || (float)_size / newCap >= 0.8) {
            switch (_strategy) {
                case ResizeStrategy::Multiplicative: {
                    newCap = _capacity == 0 ? 1 : std::ceil(_coef * _capacity);
                    break;
                }
                case ResizeStrategy::Additive: {
                    newCap = _capacity + std::ceil(_coef);
                    break;
                }
                default:
                    throw std::invalid_argument("Invalid ResizeStrategy");
            }
        }
        reserve(newCap);
    }

}

template <class T>
Vector<T>::Vector(std::initializer_list<T> list):
        _size(0), _capacity(0), _data(nullptr), _strategy(ResizeStrategy::Multiplicative), _coef(2)
{
    reserve(list.size());
    for (auto& it : list) {
        pushBack(it);
    }
}

template <class T>
Vector<T>::Vector(size_t size, ResizeStrategy strategy, float coef) {
    _size = 0;
    _coef = coef;
    _strategy = strategy;
    _data = nullptr;
    _capacity = 0;
    resize(size);
}

template <class T>
Vector<T>::Vector(size_t size, T value, ResizeStrategy strategy, float coef) {
    _size = 0;
    _coef = coef;
    _strategy = strategy;
    _data = nullptr;
    _capacity = 0;
    resize(size, value);
}


template <class T>
void Vector<T>::insert(size_t i, const Vector& value) {
    size_t oldSize = _size;
//    size_t rest = _size - i;
    _size += value.size();
    expandIfNeeded();
//    for (size_t j = i; rest > 0; ++j, --rest) {
//        _data[j + value.size()] = _data[j];
//    }
    memcpy(_data + i + value.size(), _data + i, (oldSize - i) * sizeof(T));
    memcpy(_data + i, value._data, value.size() * sizeof(T));
}

template <class T>
void Vector<T>::insert(const Vector::Iterator& it, const T& value) {
    size_t idx = 0;
    while (begin() + idx != it) {
        ++idx;
    }
    insert(idx, value);
}

template <class T>
void Vector<T>::insert(const Vector::Iterator& it, const Vector& value) {
    size_t idx = 0;
    while (begin() + idx != it) {
        ++idx;
    }
    insert(idx, value);
}


template <class T>
Vector<T>::Iterator::Iterator(T* ptr): _ptr(ptr) {}

template <class T>
Vector<T>::Iterator::Iterator(const Vector::Iterator& it): _ptr(it._ptr) {}

template <class T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator+(size_t n) {
    return _ptr + n;
}

template <class T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator-(size_t n) {
    return _ptr - n;
}

template <class T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++() {
    _ptr++;
    return *this;
}

template <class T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator--() {
    _ptr--;
    return *this;
}

template <class T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int) {
    auto tmp = *this;
    ++*this;
    return tmp;
}

template <class T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int) {
    auto tmp = *this;
    --(*this);
    return tmp;
}

template <class T>
bool Vector<T>::Iterator::operator!=(const Vector::Iterator& it) const {
    return _ptr != it._ptr;
}

template <class T>
bool Vector<T>::Iterator::operator==(const Vector::Iterator& it) const {
    return _ptr == it._ptr;
}

template <class T>
T& Vector<T>::Iterator::operator*() const {
    return *_ptr;
}

template<class T>
Vector<T>::ReverseIterator::ReverseIterator(T* ptr): _ptr(ptr) {}

template<class T>
Vector<T>::ReverseIterator::ReverseIterator(const Vector::ReverseIterator& it): _ptr(it._ptr) {}

template<class T>
typename Vector<T>::ReverseIterator Vector<T>::ReverseIterator::operator+(size_t n) {
    return _ptr - n;
}

template<class T>
typename Vector<T>::ReverseIterator Vector<T>::ReverseIterator::operator-(size_t n) {
    return _ptr + n;
}

template<class T>
typename Vector<T>::ReverseIterator& Vector<T>::ReverseIterator::operator++() {
    --_ptr;
    return *this;
}

template<class T>
typename Vector<T>::ReverseIterator& Vector<T>::ReverseIterator::operator--() {
    ++_ptr;
    return *this;
}

template<class T>
typename Vector<T>::ReverseIterator Vector<T>::ReverseIterator::operator++(int) {
    auto tmp = *this;
    --*this;
    return tmp;
}

template<class T>
typename Vector<T>::ReverseIterator Vector<T>::ReverseIterator::operator--(int) {
    auto tmp = *this;
    ++*this;
    return tmp;
}

template<class T>
bool Vector<T>::ReverseIterator::operator!=(const Vector::ReverseIterator& it) const {
    return _ptr != it._ptr;
}

template<class T>
bool Vector<T>::ReverseIterator::operator==(const Vector::ReverseIterator& it) const {
    return _ptr == it._ptr;
}

template<class T>
T& Vector<T>::ReverseIterator::operator*() const {
    return *_ptr;
}

