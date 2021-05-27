#include <iostream>
#include "SinglyLinkedList/List.h"
#include "Vector/vector.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"
#include "profile.h"
#include "Stack/VectorStack.h"
#include "ChunkedVector/ChunkedVector.h"
#include <vector>
template<class T>
bool isOdd(const T& val) {
    return val % 2 == 1;
}

template<class T>
bool isEven(const T& val) {
    return !isOdd(val);
}

template<class T>
void kek(T& val, size_t i) {
    if (i == 0) val = 228;
    else if (i == 2) val = 1488;
    else val = 42;

}

template<class T>
T addFive(const T& val) {
    return val + 5;
}

int main() {

  ChunkedVector<int> v(3);
Vector<int>v1;
v1.reserve(5);
v1[3] = 33;

  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(10);
//    v.pushFront(0);
//    v.pushFront(-1);
//    v.pushFront(-3);
    auto t = v.back();
    auto k = v.front();
    v.popFront();
    auto kk = v.front();
    v.popBack();
    auto tt = v.back();
    size_t s = v.size();
//std::cout << s;
//Stack<int> q(StackContainer::List);
//
//    auto q1(q);
//
//
//std::cout << q.top();

//    std::cout << std::endl;


    return 0;
}
