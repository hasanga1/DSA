//
// Created by Hasanga Ranasinghe on 2023-06-07.
//
#include <iostream>

using namespace std;

template <typename K, typename V>
class Node {
public:
    Node *next = nullptr;
    K key;
    V val;

    Node (K key, V val) {
        this->key = key;
        this->val = val;
    }
};

template <typename K, typename V>
class HashTable {
private:
    Node<K, V>* *array;
    long capacity;
    double loadFactor = 0.75;
    long size = 0;

    void reHash() {
        Node<K, V>* *newArray = new Node<K, V>*[capacity * 2];

        for (int i = 0; i < capacity; i++) {
            newArray[i] = array[i];
        }

        this->capacity *= 2;

        array = newArray;
        delete *newArray;
    }
public:
    HashTable(long capacity) {
        this->capacity = capacity;
        array = new Node<K, V>*[capacity];
    }

    HashTable() {
        this->capacity = 16;
        array = new Node<K, V>*[capacity];
    }

    HashTable(long capacity, double loadFactor) {
        this->capacity = capacity;
        this->loadFactor = loadFactor;
        array = new Node<K, V>*[capacity];
    }

    std::size_t hash(const K& key) const {
        std::hash<K> hasher;
        return hasher(key) % this->capacity;
    }

    void put(K key, V val) {
        if ((size * 1.00) / capacity == loadFactor) {
            this->reHash();
        }

        long index = hash(key);

        if (array[index] == nullptr) {
            array[index] = new Node<K, V>(key, val);
            return;
        }

        Node<K, V> **temp = &array[index];
        while ((*temp) != nullptr) {
            temp = &((*temp)->next);
        }

        (*temp) = new Node<K, V>(key, val);

        this->size++;
    }

    bool remove(K key) {
        long index = hash(key);

        Node<K, V> **temp = &(array[index]);
        while ((*temp)->next != nullptr) {
            if ((*temp)->key == key) {
                (*temp) = (*temp)->next;
                this->size--;
                return true;
            }
            temp = &((*temp)->next);
        }
        if ((*temp)->key == key) {
            (*temp) = nullptr;
            this->size--;
            return true;
        }

        return false;
    }

    bool set(K key, V value) {
        long index = hash(key);

        Node<K, V> **temp = &array[index];
        while ((*temp) != nullptr) {
            if ((*temp)->key == key) {
                (*temp)->val = value;
                return true;
            }
            temp = &((*temp)->next);
        }

        return false;
    }

    V get(K key) {
        long index = hash(key);

        Node<K, V> **temp = &array[index];
        while ((*temp) != nullptr) {
            if ((*temp)->key == key) {
                return (*temp)->val;
            }
            temp = &((*temp)->next);
        }
        return V();
    }

    void print() {
        for (int i = 0; i < this->capacity; i++) {
            Node<K, V> **temp = &(array[i]);
            while ((*temp) != nullptr) {
                cout << (*temp)->key << ": " << (*temp)->val << endl;
                temp = &((*temp)->next);
            }
        }
    }

};

int main() {
    HashTable<int, string> *hashTable = new HashTable<int, string>(2);

    hashTable->put(210515, "Hasanga");
    hashTable->put(210678, "Shadow");
    hashTable->put(211345, "Unknown");

    cout << hashTable->get(210515) << endl;

    hashTable->print();

    hashTable->remove(210515);

    cout << hashTable->get(210515) << endl;

    hashTable->print();
}