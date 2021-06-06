#pragma once
#include <utility>
#include <stdexcept>

template <class T>
class BST {
    class Node {
    public:
        T data;
        Node* left;
        Node* right;

        explicit Node(T data, Node* left = nullptr, Node* right = nullptr):
        data(data),
        left(left),
        right(right) {}
    };

public:
    BST();
    BST(const BST& other);
    BST(const BST&& other) noexcept ;

    BST& operator=(const BST& other);
    BST& operator=(BST&& other) noexcept ;

    ~BST();

    void insert(const T& val);
    void remove(const T& val);
    const T& find(const T& val) const;
//    T& find(const T& val);

private:
    void _removeNode(Node* node, Node* parent);
    Node* _root;
};

template<class T>
BST<T>::BST() {
    _root = nullptr;
}

template<class T>
BST<T>::BST(const BST& other) {

}

template<class T>
BST<T>::BST(const BST&& other) noexcept {
    _root = std::exchange(other._root, nullptr);
}

template<class T>
BST<T>& BST<T>::operator=(const BST& other) {
    if (this != &other) {
        *this = BST(other);
    }
    return *this;
}

template<class T>
BST<T>& BST<T>::operator=(BST&& other) noexcept {
    if (this != &other) {
        _root = std::exchange(other._root, nullptr);
    }
    return *this;
}

template<class T>
BST<T>::~BST() {

}

template<class T>
void BST<T>::insert(const T& val) {
    if (!_root) {
        _root = new Node(val);
    }
    else {
        Node* node = _root;
        while (true) {
            if (node->data > val) {
                if (!node->left) {
                    node->left = new Node(val);
                    return;
                }
                node = node->left;
            }
            else {
                if (!node->right) {
                    node->right = new Node(val);
                    return;
                }
                node = node->right;
            }
        }
    }
}

template<class T>
void BST<T>::remove(const T& val) {
    Node* node = _root;
//    if (!node) {
//        return;
//    }
    Node* parent = nullptr;
    while (node) {
        if (node->data == val) {
            _removeNode(node, parent);
        }
        else if (node->data > val) {
            parent = node;
            node = node->left;
        }
        else {
            parent = node;
            node = node->right;
        }
    }
}

template<class T>
const T& BST<T>::find(const T& val) const {
    Node* node = _root;

    while (node) {
        if (node->data == val) {
            return node->data;
        }
        else if (node->data > val) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    throw std::runtime_error("Incorrect value");
}

template<class T>
void BST<T>::_removeNode(BST::Node* node, BST::Node* parent) {
    // 0 child case
    if (!node->left && !node->right) {
        if (parent->right == node) {
            parent->right = nullptr;
        }
        else {
            parent->left = nullptr;
        }
        delete node;
        return;
    }
    // 1 child case
    if (!node->left || !node->right) {
        if (!node->left) {
            Node* right = node->right;
            node->data = right->data;
            node->right = right->right;
            node->left = right->left;
            delete right;
        }
        else {
            Node* left = node->left;
            node->data = left->data;
            node->right = left->right;
            node->left = left->left;
            delete left;
        }
        return;
    }

    // 2 child case
    if (!node->right->left) {
        Node* tmp = node->right->right;
        node->data = node->right->data;
        delete node->right;
        node->right = tmp;
    }
    else {
        Node* ptr = node->right;
        Node* par = parent;
        // поиск самого левого
        while (ptr->left) {
            par = ptr;
            ptr = ptr->left;
        }
        node->data = ptr->data;
        return _removeNode(ptr, par);
    }






}

//template<class T>
//T& BST<T>::find(const T& val) {
//
//}

