#pragma once
#include <stdexcept>
#include <utility>
#include <sstream>
#include <cstddef>



template<class T>
class List {
    class Node {
    public:
        T data;
        Node* next;
        Node(T data, Node* next): data(data), next(next) {};
        void removeNext();
    };
    Node* _head;
    size_t _size;


    void _mutableMap(T (* callback)(const T& currVal));
    void _mutableFilter(bool (* callback)(const T& currVal));
    void _reverse(Node* beforeBegin, List::Node* begin, Node* end);
public:
    class Iterator;
    List();
    List(const List& other);
    List(List&& other) noexcept;

    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;

    ~List();

    size_t size() const;
    bool empty() const;

    const T& operator[](size_t pos) const;
    T& operator[](size_t pos);

    const T& front() const;
    T& front();

    const T& back() const;
    T& back();

    void insert(size_t pos, const T& val);
    void insert(const List::Iterator& pos, const T& val);
    void pushBack(const T& val);
    void pushFront(const T& val);

    void popFront();
    void popBack();
    void remove(size_t pos);
    void remove(const Iterator& pos);
    void removeAfter(const Iterator& pos);

    void clear();

    void forEach(void (* callback)(T& currVal, size_t idx));
    List map(T (* callback)(const T& currVal)) const;
    List filter(bool (* callback)(const T& currVal)) const;

    void reverse(size_t begin, size_t end);

    Node* findNode(size_t pos) const;


    class Iterator {
    private:
        Node* _ptr;
    public:
        friend List;
        Iterator(Node* ptr) : _ptr(ptr) {};
        Iterator(const Iterator& it) : _ptr(it._ptr) {};

        Iterator operator+(size_t n);

        Iterator& operator++ ();

        Iterator operator++ (int);


        bool operator!=(const Iterator& it) const { return _ptr != it._ptr; }
        bool operator==(const Iterator& it ) const { return _ptr == it._ptr; }

        T& operator*() const { return _ptr->data; }
    };
    Iterator begin() const { return Iterator(_head); };
    Iterator end() const { return nullptr; };
};

template<class T>
List<T>::List(): _head(nullptr), _size(0) {}

template<class T>
List<T>::~List() {
    clear();
}

template<class T>
size_t List<T>::size() const {
    return _size;
}

template<class T>
bool List<T>::empty() const {
    return !size();
}

template<class T>
const T& List<T>::front() const {
    return _head->data;
}

template<class T>
T& List<T>::front() {
    return _head->data;
}

template<class T>
const T& List<T>::back() const {
    return operator[](_size - 1);
}

template<class T>
T& List<T>::back() {
    return operator[](_size - 1);
}

template<class T>
void List<T>::pushBack(const T& val) {
    insert(_size, val);
}

template<class T>
void List<T>::pushFront(const T& val) {
    insert(0, val);
}

template<class T>
void List<T>::popFront() {
    remove(0);
}

template<class T>
void List<T>::popBack() {
    remove(_size - 1);
}

template<class T>
void List<T>::insert(size_t pos, const T& val) {
    if (pos == 0) {
        auto newNode = new Node(val, _head);
        _head = newNode;
    }
    else if (pos >= _size) {
        auto node = findNode(_size - 1);
        auto newNode = new Node(val, nullptr);
        node->next = newNode;
    }
    else {
        auto node = findNode(pos - 1);
        auto newNode = new Node(val, node->next);
        node->next = newNode;
    }
    ++_size;
}

template<class T>
void List<T>::clear() {
    while (_size > 0) {
        popFront();
    }
}

template<class T>
List<T>::List(const List& other): _head(nullptr), _size(0) {
    if (!other._head) {
        return;
    }
    auto node = new Node(0, nullptr);
    _head = node;
    auto otherPtr = other._head;
    while (_size != other._size - 1) {
        node->data = otherPtr->data;
        node->next = new Node(0, nullptr);
        otherPtr = otherPtr->next;
        node = node->next;
        ++_size;
    }
    node->data = otherPtr->data;
    ++_size;
}

template<class T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        *this = List(other);
    }
    return *this;
}

template<class T>
List<T>::List(List<T>&& other) noexcept {
    _size = std::exchange(other._size, 0);
    _head = std::exchange(other._head, nullptr);
}

template<class T>
List<T>& List<T>::operator=(List&& other) noexcept {
    if (this != &other) {
        clear();
        _size = std::exchange(other._size, 0);
        _head = std::exchange(other._head, nullptr);
    }
    return *this;
}

template<class T>
const T& List<T>::operator[](size_t pos) const {
    return findNode(pos)->data;
}

template<class T>
T& List<T>::operator[](size_t pos) {
    return findNode(pos)->data;
}

template<class T>
void List<T>::remove(size_t pos) {
    if (_size == 0) {
        return;
    }
    else if (pos >= _size) {
        throw std::range_error("remove(): Invalid pos");
    }
        // popFront
    else  if (pos == 0) {
        auto tmp = _head;
        _head = _head->next;
        delete tmp;
    }
        // popBack
    else if (pos == _size - 1) {
        auto node = findNode(_size - 2);
        delete node->next;
        node->next = nullptr;
    }
    else {
        auto prev = findNode(pos - 1);
        prev->removeNext();
    }
    --_size;
}

template<class T>
typename List<T>::Node* List<T>::findNode(size_t pos) const {
    if (pos >= _size) {
        throw std::range_error("findNode(): Invalid pos");
    }
    size_t i = 0;
    Node* ptr = _head;
    while (i < pos) {
        if (ptr->next) {
            ptr = ptr->next;
        }
        ++i;
    }
    return ptr;
}

template<class T>
void List<T>::forEach(void (* callback)(T&, size_t)) {
    size_t i = 0;
    for (auto h = _head; h != nullptr; h = h->next, ++i) {
        callback(h->data, i);
    }
}

template<class T>
List<T> List<T>::map(T (* callback)(const T& )) const {
    auto copy(*this);
    copy._mutableMap(callback);
    return copy;
}

template<class T>
List<T> List<T>::filter(bool (* callback)(const T& )) const {
    auto copy(*this);
    copy._mutableFilter(callback);
    return copy;
}

template<class T>
void List<T>::_mutableMap(T (* callback)(const T&)) {
    for (auto h = _head; h != nullptr; h = h->next) {
        h->data = callback(h->data);
    }
}

template<class T>
void List<T>::_mutableFilter(bool (* callback)(const T&)) {
    for (auto i = _head; i->next != nullptr; ) {
        if (!callback(i->next->data)) {
            i->removeNext();
            --_size;
        }
        else {
            i = i->next;
        }
    }

    if (!callback(_head->data)) {
        remove(0);
    }
}

template<class T>
void List<T>::reverse(size_t begin, size_t end) {
    if (begin > end || begin >= _size || end >= _size) {
        std::stringstream e;
        e << "List::reverse(" << begin
          << "," << end
          << ") bad range";

        throw std::range_error(e.str());
    }
    auto beforeStart = begin == 0 ? nullptr : findNode(begin - 1);
    auto start = begin == 0 ? _head : beforeStart->next;
    auto finish = start;
    for (size_t i = begin; i < end; ++i) {
        finish = finish->next;
    }
    _reverse(beforeStart, start, finish);
}

template<class T>
void List<T>::_reverse(List::Node* beforeBegin, List::Node* begin, List::Node* end) {
    Node* afterEnd = end->next;
    // разделяем список на 3 части: левая, реверсируемая, правая
    // и изолируем реверсируемую часть, как буто это полноценный список
    // затем реверсируем её обычным алгоритмом для списков
    // и потом соединяем части
    end->next = nullptr;
    Node* current = begin;
    Node* next;
    Node* prev = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    if (!beforeBegin) {
        _head = end;
    }
    else {
        beforeBegin->next = end;
    }
    begin->next = afterEnd;
}

template<class T>
void List<T>::insert(const List::Iterator& pos, const T& val) {
    if (pos == begin()) {
        insert(0, val);
    }
    else if (pos == end()) {
        insert(_size, val);
    }
    else {
        auto nextNode = pos._ptr->next;
        auto newNode = new Node(val, nextNode);
        pos._ptr->next = newNode;
        ++_size;
    }
}

template<class T>
void List<T>::remove(const List::Iterator& pos) {
    if (pos == begin() || _size == 1) {
        remove(0);
    }
    else if (pos == end()) {
        remove(_size - 1);
    }
    else {
        Node* node = pos._ptr;
        auto t = begin();
        while (t._ptr && t._ptr->next != node) {
            ++t;
        }
        removeAfter(t);
    }
}

template<class T>
void List<T>::removeAfter(const List::Iterator& pos) {
    if (!pos._ptr || !pos._ptr->next || pos == end()) {
        return;
    }
    pos._ptr->removeNext();
    --_size;
}

template<class T>
void List<T>::Node::removeNext() {
    auto n = next;
    next = n->next;
    delete n;
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator+(size_t n) {
    auto tmp = *this;
    while (n > 0) {
        ++(tmp);
        --n;
    }
    return tmp._ptr;
}

template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    _ptr = _ptr->next;
    return *this;
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    auto tmp = *this;
    ++(*this);
    return tmp;
}