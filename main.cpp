#include <iostream>
#include "SinglyLinkedList/List.h"
#include "Vector/vector.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"
#include "profile.h"
#include "Stack/VectorStack.h"
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

    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.insert(1, 10);
    for (auto i: v) {
        std::cout << i << " ";
    }

//Stack<int> q(StackContainer::List);
//
//    auto q1(q);
//
//
//std::cout << q.top();

//    std::cout << std::endl;
//    for (size_t i = 0; i < l.size(); ++i) {
//        std::cout << l[i] << " ";
//    }
    return 0;
}
