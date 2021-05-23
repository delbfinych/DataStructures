#include <iostream>
#include "SinglyLinkedList/List.h"
#include "Vector/vector.h"
#include "Stack/Stack.h"
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

Stack<int> st(StackContainer::List);
st.push(3);
st.push(4);
st.pop();
std::cout << st.top();

//    std::cout << std::endl;
//    for (size_t i = 0; i < l.size(); ++i) {
//        std::cout << l[i] << " ";
//    }
    return 0;
}
