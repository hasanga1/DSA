//
// Created by Hasanga Ranasinghe on 2023-06-07.
//

#include <iostream>

using namespace std;

template <typename K, typename V>
class Bucket {
public:
    K key;
    V value;

    Bucket(K key, V value) {
        this->key = key;
        this->value = value;
    }
};

template <typename K, typename V>
class HashTable {
private:
    long capacity = 16;
    long size = 0;
    double loadFactor = 0.75;
    Bucket<K, V>* *bucketList;

    void rehash() {
        Bucket<K, V>* *newBucketList = new Bucket<K, V>*[capacity * 2];
        for (int i = 0; i < capacity; i++) {
            newBucketList[i] = bucketList[i];
        }

        this->capacity *= 2;

        bucketList = newBucketList;

        delete[] newBucketList;
    }

public:
    HashTable() {
        this->bucketList = new Bucket<K, V>*[capacity];
    }

    HashTable(long capacity) {
        this->capacity = capacity;
        this->bucketList = new Bucket<K, V>*[capacity];
    }

    HashTable(long capacity, double loadFactor) {
        this->capacity = capacity;
        this->loadFactor;
        this->bucketList = new Bucket<K, V>*[capacity];
    }

    HashTable(double loadFactor) {
        this->bucketList = new Bucket<K, V>*[capacity];
        this->loadFactor;
    }

    std::size_t hash(const K& key) const {
        std::hash<K> hasher;
        return hasher(key) % this->capacity;
    }

    void put(K key, V value) {
        if ((size * 1.00) / capacity >= loadFactor) {
            this->rehash();
        }
        long index = this->hash(key);

        if (this->bucketList[index] == nullptr) {
            bucketList[index] = new Bucket<K, V>(key, value);
            size++;
            return;
        }

        index++;
        for (int i = 0; i < this->capacity - 1; i++) {
            if (index == capacity - 1) {
                index = 0;
            }
            if (this->bucketList[index] != nullptr) {
                index++;
                continue;
            }
            this->bucketList[index] = new Bucket<K, V>(key, value);
            size++;
            return;
        }
    }

    bool remove(K key) {
        long index = this->hash(key);

        for (int i = 0; i < this->capacity - 1; i++) {
            if (index == capacity) {
                index = 0;
            }
            if (this->bucketList[index]->key == key) {
                this->bucketList[index] = nullptr;
                size--;
                return true;
            }

            index++;
        }

        return false;
    }

    bool set(K key, V value) {
        long index = this->hash(key);

        for (int i = 0; i < this->capacity - 1; i++) {
            if (index == capacity - 1) {
                index = 0;
            }
            if (this->bucketList[index]->key == key) {
                this->bucketList[index]->value = value;
                return true;
            }

            index++;
        }

        return false;
    }

    V get(K key) {
        long index = this->hash(key);

        for (int i = 0; i < this->capacity - 1; i++) {
            if (index == capacity) {
                index = 0;
            }
            if (this->bucketList[index] != nullptr && this->bucketList[index]->key == key) {
                return bucketList[index]->value;
            }

            index++;
        }
        return V();
    }

    void print() {
        for (int i = 0; i < capacity; i++) {
            if (bucketList[i] != nullptr) {
                cout << this->bucketList[i]->key << ": " << this->bucketList[i]->value << endl;
            }
        }
    }
};

int main() {
    HashTable<int, string> *hashTable = new HashTable<int, string>();

    hashTable->put(210515, "Hasanga");
    hashTable->put(210678, "Shadow");
    hashTable->put(211345, "Unknown");

    hashTable->print();

    cout << hashTable->get(210515) << endl;

    hashTable->print();

    hashTable->remove(210515);

    cout << hashTable->get(210515) << endl;

    hashTable->print();
}