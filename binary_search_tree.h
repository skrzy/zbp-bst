#ifndef ZBP_BST_BINARYSEARCHTREE_H
#define ZBP_BST_BINARYSEARCHTREE_H

#include <memory>
#include <ostream>
#include <iostream>

using namespace std;

template <typename T>
class binary_search_tree {
private:
    struct node;

    typedef shared_ptr<node> node_ptr;

    struct node {
        T value;
        node_ptr parent;
        node_ptr left_child;
        node_ptr right_child;

        explicit node(T value);
        void print(int level);
    };

    node_ptr root = nullptr;

    node_ptr find_successor(node_ptr n);
    node_ptr find_min(node_ptr root);
    node_ptr find_max(node_ptr root);
    node_ptr find_node(T element);

public:
    bool insert(T inserted_value);
    bool find(T element);
    bool erase(T element);
    T& min();
    T& max();
    void print();
};


template <typename T>
bool binary_search_tree<T>::insert(T inserted_value) {

    node_ptr parent_node = nullptr;
    node_ptr current_node = root;

    while (current_node != nullptr) {
        parent_node = current_node;
        if (inserted_value < current_node->value) {
            current_node = current_node->left_child;
        } else if(current_node-> value < inserted_value) {
            current_node = current_node->right_child;
        } else {
            return false;   //value already in tree
        }
    }

    node_ptr new_node = make_shared<node>(inserted_value);
    new_node->parent = parent_node;

    if (parent_node == nullptr) {
        root = new_node;
    } else {
        if (new_node->value < parent_node->value) {
            parent_node->left_child = new_node;
        } else {
            parent_node->right_child = new_node;
        }
    }

    return true;
}

template <typename T>
bool binary_search_tree<T>::find(T element) {
    return find_node(element) != nullptr;
}

template <typename T>
typename binary_search_tree<T>::node_ptr binary_search_tree<T>::find_node(T element) {
    auto current_node = root;

    while (current_node != nullptr && element != current_node->value) {
        if (element < current_node->value) {
            current_node = current_node->left_child;
        } else {
            current_node = current_node->right_child;
        }
    }

    if (current_node != nullptr && current_node->value != element) {
        current_node = nullptr;
    }

    return current_node;
}

template <typename T>
bool binary_search_tree<T>::erase(T element) {
    auto node_to_remove = find_node(element);

    if (node_to_remove == nullptr) {
        return false;
    }

    node_ptr y;
    if (node_to_remove->left_child == nullptr || node_to_remove->right_child == nullptr) {
        y = node_to_remove;
    } else {
        y = find_successor(node_to_remove);
    }

    node_ptr x;
    if (y->left_child != nullptr) {
        x = y->left_child;
    } else {
        x = y->right_child;
    }

    if (x != nullptr) {
        x->parent = y->parent;
    }

    if (y->parent == nullptr) {
        root = x;
    } else {
        if (y == y->parent->left_child) {
            y->parent->left_child = x;
        } else {
            y->parent->right_child = x;
        }
    }
    if (y != node_to_remove) {
        node_to_remove->value = y->value;
    }

    return true;
}

template <typename T>
typename binary_search_tree<T>::node_ptr binary_search_tree<T>::find_successor(node_ptr n) {
    if (n->right_child != nullptr) {
        return find_min(n->right_child);
    }

    auto current_node = n;
    auto parent_node = n->parent;

    while (current_node != nullptr && current_node->value == parent_node->value) {
        current_node = parent_node;
        parent_node = parent_node->parent;
    }

    return parent_node;
}

template <typename T>
T& binary_search_tree<T>::min() {
    return find_min(root);
}

template <typename T>
T& binary_search_tree<T>::max() {
    return find_max(root);
}

template <typename T>
typename binary_search_tree<T>::node_ptr binary_search_tree<T>::find_min(node_ptr root) {
    auto current_node = root;
    while (current_node->left_child != nullptr) {
        current_node = current_node->left_child;
    }
    return current_node;
}

template <typename T>
typename binary_search_tree<T>::node_ptr binary_search_tree<T>::find_max(node_ptr root) {
    auto current_node = root;
    while (current_node->right_child != nullptr) {
        current_node = current_node->right_child;
    }
    return current_node;
}

template <typename T>
binary_search_tree<T>::node::node(T value) : value(value) {}

template <typename T>
void binary_search_tree<T>::print() {
    root->print(0);
    cout << endl;
}

template <typename T>
void binary_search_tree<T>::node::print(int level) {
    cout << "(" << value << "-L" << level << ") -> (";
    if (left_child != nullptr) left_child->print(level + 1);
    if (right_child != nullptr) right_child->print(level + 1);
    cout << ")";

}
#endif //ZBP_BST_BINARYSEARCHTREE_H
