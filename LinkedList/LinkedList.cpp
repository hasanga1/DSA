//
// Created by Hasanga Ranasinghe on 2023-06-01.
//

#include <iostream>

using namespace std;

template<typename T>
class Node {

public:
    Node(T data) {
        this->data = data;
    }

    Node* next = nullptr;
    Node* prev = nullptr;
    T data;
};

template<typename T>
class LinkedList {

protected:
    long size = 0;
    Node<T> *head = nullptr;
public:

    LinkedList(T data) {
        head = new Node<T>(data);
        size++;
    }
    LinkedList() {}

    virtual void insert(T data) {
        size++;
        if (head == nullptr) {
            head = new Node<T>(data);
            return;
        }
        Node<T> *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new Node<T>(data);
    }

    bool remove(int index) {
        Node<T> **temp = &head;
        if (index > size - 1) {
            return false;
        }
        for (int i = 0; i <= index; i++) {
            if (i == index) {
                *temp = (*temp)->next;
                size--;
                return true;
            }
            temp = &((*temp)->next);
        }
    }

    bool remove(T element) {
        Node<T> **temp = &head;
        for (int i = 0; i < size; i++) {
            if ((*temp)->data == element) {
                *temp = (*temp)->next;
                size--;
                return true;
            }
            temp = &((*temp)->next);
        }
        return false;
    }

    void clear() {
        head = nullptr;
    }

    void clear(T element) {
        Node<T> **temp = &head;
        for (int i = 0; i < size; i++) {
            if ((*temp)->data == element) {
                *temp = (*temp)->next;
                size--;
                continue;
            }
            temp = &((*temp)->next);
        }
    }

    void clear(int from, int to) {
        Node<T> **temp = &head;
        for (int i = 0; i < from; i++) {
            temp = &((*temp)->next);
        }

        for (int i = from; i < to; i++) {
            *temp = (*temp)->next;
            size--;
        }
    }

    long length() {
        return size;
    }

    void print() {
        Node<T> *temp = head;
        while (temp != nullptr) {
            if (temp->next != nullptr) {
                cout << temp->data << ", ";
            }
            else {
                cout << temp->data << endl;
            }
            temp = temp->next;
        }
    }

};

template<typename T>
class DoubleLinkedList: public LinkedList<T> {
public:
    DoubleLinkedList(T data):
            LinkedList<T>(data) {};
    void insert(T data) {
        this->size++;
        if (this->head == nullptr) {
            this->head = new Node<T>(data);
            return;
        }
        Node<T> *temp = this->head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new Node<T>(data);
        temp->next->prev = temp;
    }
};

int main() {
    DoubleLinkedList<string> list = *new DoubleLinkedList<string>("Hasanga");
    list.insert("Tharushi");
    list.insert("Kaveesha");
    list.insert("Senali");
    list.insert("Rishani");
    list.insert("Dinali");
    list.clear(2, 3);
    list.print();
    return 0;
}
