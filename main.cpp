#include <iostream>
#include "SinglyLinkedList/List.h"
#include "Vector/vector.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"

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
class Kek {
public:
    int& _ref;


};
int main() {


Queue<int> q(QueueContainer::List);
q.push(3);
q.push(4);

std::cout << q.front();

//    std::cout << std::endl;
//    for (size_t i = 0; i < l.size(); ++i) {
//        std::cout << l[i] << " ";
//    }
    return 0;
}
