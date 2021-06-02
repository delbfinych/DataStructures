#include <iostream>
#include "SinglyLinkedList/List.h"
#include "Vector/vector.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"
#include "profile.h"
#include "Stack/VectorStack.h"
#include "ChunkedVector/ChunkedVector.h"
#include <vector>



int main() {

  ChunkedVector<int> v(3);
Vector<int>v1;
v1.reserve(5);
v1[3] = 33;
//
//    v.pushFront(0);
//    v.pushFront(1);
//    v.pushFront(2);
//    v.pushFront(3);
//    v.pushFront(4);
//
//    v.pushBack(0);
//    v.pushBack(1);
//    v.pushBack(2);
//    v.pushBack(3);
//    v.pushBack(4);
//
//    v.pushFront(-10);
//for(int i = 0; i < v.size(); ++i) {
//    std::cout << v[i] << " ";
//}
Queue<int> q;
q.push(1);
q.push(2);
q.push(3);

q.pop();
q.pop();
auto kk = q.front();
q.pop();
auto k = q.front();
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
