//
// Created by Hasanga Ranasinghe on 2023-06-01.
//

#include "Binary_Search_Tree.h"

#include <iostream>

using namespace std;

template<typename T>
class Node {
public:
    T key;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(T key) {
        this->key = key;
    }

};

template<typename T>
class BST {
private:
    Node<T> *root = nullptr;
    long nodeCount = 0;

    void printInOrderPrivate(Node<T> *temp, int* count) {
        if (temp != nullptr) {
            printInOrderPrivate(temp->left, count);
            if (count[0] != nodeCount) {
                cout << temp->key << ", ";
            }
            else {
                cout << temp->key << endl;
            }
            count[0]++;
            printInOrderPrivate(temp->right, count);
        }
    }

    void printPreOrderPrivate(Node<T> *temp, int* count) {
        if (temp != nullptr) {
            if (count[0] != nodeCount) {
                cout << temp->key << ", ";
            }
            else {
                cout << temp->key << endl;
            }
            count[0]++;
            printPreOrderPrivate(temp->left, count);
            printPreOrderPrivate(temp->right, count);
        }
    }

    void printPostOrderPrivate(Node<T> *temp, int* count) {
        if (temp != nullptr) {
            printPostOrderPrivate(temp->left, count);
            printPostOrderPrivate(temp->right, count);

            if (count[0] != nodeCount) {
                cout << temp->key << ", ";
            }
            else {
                cout << temp->key << endl;
            }
            count[0]++;
        }
    }

    bool ppofp(Node<T> *temp, T key) {
        if (temp != nullptr) {
            if (temp->key == key) {
                return true;
            }
            else {
                return ppofp(temp->left, key) || ppofp(temp->right, key);;
            }
        }
        return false;
    }

    bool ppof(T key) {
        Node<T> *temp = this->root;
        return this->ppofp(temp, key);
    }

public:
    BST(T root) {
        this->root = new Node<T>(root);
    }
    BST() {};

    void insert(T key) {
        nodeCount++;

        if (root == nullptr) {
            this->root = new Node<T>(key);
            return;
        }
        Node<T> *temp = root;
        while (temp->right != nullptr || temp->left != nullptr) {
            if (temp->key < key) {
                if (temp->right == nullptr) {
                    temp->right = new Node<T>(key);
                    return;
                }
                temp = temp->right;
            }
            else if (temp->key > key) {
                if (temp->left == nullptr) {
                    temp->left = new Node<T>(key);
                    return;
                }
                temp = temp->left;
            }
            else {
                return;
            }
        }
        if (temp->key < key) {
            temp->right = new Node<T>(key);
        }
        else if (temp->key > key) {
            temp->left = new Node<T>(key);
        }
    }

    void printInOrder() {
        Node<T> *temp = this->root;
        int* count = new int[0];
        count[0] = 0;

        this->printInOrderPrivate(temp, count);
    }

    void printPreOrder() {
        Node<T> *temp = this->root;
        int* count = new int[0];
        count[0] = 0;

        this->printPreOrderPrivate(temp, count);
    }

    void printPostOrder() {
        Node<T> *temp = this->root;
        int* count = new int[0];
        count[0] = 0;

        this->printPostOrderPrivate(temp, count);
    }

    bool find(T key) {
        return ppof(key);
    }

    bool empty() {
        if (root == nullptr) {
            return true;
        }
        return false;
    }

};

int main() {
    BST<int> *bst = new BST<int>(40);
    bst->insert(30);
    bst->insert(50);
    bst->insert(25);
    bst->insert(35);
    bst->insert(45);
    bst->insert(60);
    cout << bst->find(80) << endl;
    bst->printPreOrder();
    bst->insert(90);


}