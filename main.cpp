#include <iostream>
#include "SinglyLinkedList/List.h"
#include "Vector/vector.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"
#include "profile.h"
#include "Stack/VectorStack.h"
#include "ChunkedVector/ChunkedVector.h"
#include <vector>
#include "Map/BST.h"
#include "Map/Map.h"
#include <string>
int main() {

  ChunkedVector<int> v(3);


Map<std::string,int> t;


t.add("010", 2);
t.add("005", 9);
t.add("017", 4);
t.add("031", 4);
t.add("004",3);
t.add("007",8);
t.add("008",1);
    Map<std::string,int> L(t);

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
//Queue<int> q;
//q.push(1);
//q.push(2);
//q.push(3);
//
//q.pop();
//q.pop();
//auto kk = q.front();
//q.pop();
//auto k = q.front();
////std::cout << s;
//Stack<int> q(StackContainer::List);
//
//    auto q1(q);
//
//
//std::cout << q.top();

//    std::cout << std::endl;


    return 0;
}
