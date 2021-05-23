#include <cstddef>


template <class T>
class IVector
{
public:

    virtual T& at(size_t idx) = 0;
    virtual const T& at(size_t idx) const = 0;
    virtual T& operator[](size_t i) = 0;
    virtual const T& operator[](size_t i) const = 0;

    virtual void pushBack(const T& value) = 0;
    virtual void pushFront(const T& value) = 0;
    virtual void insert(size_t idx, const T& value) = 0;

    virtual void clear() = 0;
    virtual void erase(size_t i) = 0;
    virtual void erase(size_t i, size_t len) = 0;
    virtual void popBack() = 0;

    virtual void resize(size_t count) = 0;
    virtual void resize(size_t count, const T& val) = 0;
    virtual void reserve(size_t newCapacity) = 0;

    virtual size_t size() const = 0;
    virtual size_t capacity() const = 0;

    virtual long long find(const T& value) const = 0;

    virtual ~IVector() = default;
};
