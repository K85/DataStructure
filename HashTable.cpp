#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;

template<typename K, typename V>
class HashTable {

public:
    class Pair {
    public:
        K key;
        V value;

    public:
        Pair(K key, V value) : key(key), value(value){}

    public:
        Pair() {}
    };

public:
    Pair * A;
    int A_SIZE;
    int table_size;

public:
    HashTable(int A_SIZE) {
        this->A = new Pair[A_SIZE];
        this->A_SIZE = A_SIZE;
        this->table_size = 0;

        memset(A, 0, A_SIZE * sizeof(A));
    }

public:
    bool empty() {
        return size() == 0;
    }

public:
    int size() {
        return table_size;
    }

public:
    int search(const K& key) const {

        // If search failed, we must return j = i.
        // If search successfully, we may return j = i;
        // HomeBucket
        hash<K> H;
        int i = (unsigned int) H(key) % this->A_SIZE;
         int j = i;
         do {
             if (&A[j] == nullptr || A[j].key == key) return j; // find true bucket ?
             j = (j + 1) % this->A_SIZE; // try next bucket.
         } while(j != i); // back to starting point ?

         // hash table is full.
         return j;
    }
public:
    Pair * find(const K& key) const {
        // search index.
        int i = search(key);

        // match ?
        if (A[i] == nullptr || A[i]->key != key) {
            return nullptr;
        } else return A[i];
    }

public:
    void erase(const K& key) {
        // search index.
        int i = search(key);

        // match ?
        if (A[i] == nullptr || A[i]->key != key) {
            return;
        } else A[i] = nullptr;
    }

public:
    void insert(const Pair & pair) {

       // search index.
       int i = search(pair.key);

       // Case1: pair not exist.
       if (&A[i] == nullptr) {
           HashTable<K, V>::Pair * targetPair =new Pair(pair.key, pair.value);
        A[i] = *targetPair;

        this->table_size++;
       } else if (A[i].key == pair.key) {
           // Case2: pair already exist. (Update it)
           A[i] = pair;
       } else {
           // Case3: table full.
           printf("INSERT failed ! the table is full !");
       }
    }

public:
    void trace() {
        for (int i = 0; i < this->A_SIZE; i++) {
            cout << i << " = {" << A[i].key << ", " << A[i].value << "}" << endl;
        }
    }

};


int main() {

    HashTable<int, string> ht(30);

    printf("Before inserts: \n");
    ht.trace();
    auto pair1 = new HashTable<int, string>::Pair(5, "hello");
    ht.insert(*pair1);

    auto pair2 = new HashTable<int, string>::Pair(10, "world");
    ht.insert(*pair2);

    auto pair3 = new HashTable<int, string>::Pair(15, "alice");
    ht.insert(*pair3);

    printf("After inserts: \n");
    ht.trace();
    return 0;
}
