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
            if (count[0] != nodeCount - 1) {
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
            if (count[0] != nodeCount - 1) {
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

            if (count[0] != nodeCount - 1) {
                cout << temp->key << ", ";
            }
            else {
                cout << temp->key << endl;
            }
            count[0]++;
        }
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
        Node<T> **temp = &root;
        while ((*temp)->right != nullptr || (*temp)->left != nullptr) {
            if ((*temp)->key < key) {
                temp = &((*temp)->right);
            } else if ((*temp)->key > key) {
                temp = &((*temp)->left);
            } else {
                return true;
            }
        }
        if ((*temp)->key == key) {
            return true;
        }
        return false;
    }

    bool empty() {
        if (root == nullptr) {
            return true;
        }
        return false;
    }

    bool remove(T key) {
        Node<T> **temp = &root;
        while ((*temp)->right != nullptr || (*temp)->left != nullptr) {
            if ((*temp)->key < key) {
                temp = &((*temp)->right);
            }
            else if ((*temp)->key > key) {
                temp = &((*temp)->left);
            }
            else {
                if ((*temp)->right == nullptr && (*temp)->left != nullptr) {
                    *temp = (*temp)->left;
                    nodeCount--;
                    return true;
                }
                else if ((*temp)->left == nullptr && (*temp)->right != nullptr) {
                    *temp = (*temp)->right;
                    nodeCount--;
                    return true;
                }
                else {
                    Node<T> **temp2 = &((*temp)->right);
                    while ((*temp2)->left != nullptr) {
                        temp2 = &((*temp2)->left);
                    }
                    (*temp)->key = (*temp2)->key;
                    *temp2 = nullptr;
                    nodeCount--;
                    return true;
                }
            }
        }
        if ((*temp)->key == key) {
            *temp = nullptr;
            nodeCount--;
            return true;
        }
        else {
            return false;
        }
    }

    void clear() {
        this->root = nullptr;
        nodeCount = 0;
    }


};

int main() {
    BST<int> *bst = new BST<int>();
    bst->insert(40);
    bst->insert(30);
    bst->insert(50);
    bst->insert(25);
    bst->insert(35);
    bst->insert(45);
    bst->insert(60);
    bst->insert(70);
    bst->insert(65);
    bst->insert(75);
    bst->insert(55);
    bst->insert(56);
    bst->insert(54);

    cout << "Original BST:\t";
    bst->printInOrder();

    bst->remove(50);
    bst->remove(55);
    bst->remove(30);
    bst->remove(70);

    cout << bst->find(40) << endl;
    bst->printInOrder();
}