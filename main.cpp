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
