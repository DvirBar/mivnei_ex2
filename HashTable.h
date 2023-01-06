#ifndef MIVNEI_EX2_HASHTABLE_H
#define MIVNEI_EX2_HASHTABLE_H

#include "AVLTree.h"
#include "Exception.h"
#include "Pair.h"
#include <iostream>

using namespace std;

template<class T>
class HashTable {
    AVLTree<int ,T>* table;
    int numElements;
    int tableSize;

    int hash(int key) const;
    void createAndCopyTable(int newSize);
    void expandTable();
    void shrinkTable();
    void extractToArray(Pair<int, T>* array);
    void createTableFromArray(Pair<int, T>* array, AVLTree<int, T>* newTable);
    void insertToCell(int key, T data, AVLTree<int, T>* tableToInsert);

    static const int MIN_SIZE = 2;
    static const int EXPANSION_RATE = 2;
    static const int SHRINKING_RATE = 4;

public:
    explicit HashTable(int initSize);

    // TODO: Should we delete these?
    HashTable(const HashTable<T>& hTable) = delete;
    HashTable& operator=(const HashTable<T>& hTable) = delete;
    ~HashTable();

    void insert(int key, T data);
    T lookup(int key) const;
    T remove(int key);
    int size();
    void print();
};

template<class T>
HashTable<T>::HashTable(int initSize):
    tableSize(initSize),
    numElements(0)
{
        if(initSize < MIN_SIZE) {
            throw InvalidArguments();
        }

        table = new AVLTree<int, T>[initSize]();
}

template<class T>
HashTable<T>::~HashTable() {
    // TODO: When should we delete the trees?
    delete[] table;
}

template<class T>
int HashTable<T>::hash(int key) const {
    return key%tableSize;
}

template<class T>
void HashTable<T>::insert(int key, T data) {
    insertToCell(key, data, table);
    numElements++;
    if(numElements >= tableSize) {
        expandTable();
    }
}

template<class T>
void HashTable<T>::insertToCell(int key, T data, AVLTree<int, T>* tableToInsert) {
    tableToInsert[hash(key)].insert(key, data);
}

template<class T>
void HashTable<T>::expandTable() {
    createAndCopyTable(tableSize*EXPANSION_RATE);
}

template<class T>
void HashTable<T>::createAndCopyTable(int size) {
    auto helperArray = new Pair<int, T>[numElements]();

    extractToArray(helperArray);

    tableSize = size;
    auto newTable = new AVLTree<int, T>[tableSize]();

    createTableFromArray(helperArray, newTable);

    delete[] table;
    table = newTable;
}

template<class T>
void HashTable<T>::extractToArray(Pair<int, T>* array) {
    for(int i=0; i<tableSize; i++) {
        if(!table[i].isEmpty()) {
            table[i].inorderDataToArray(array);
            array += table[i].getNumNodes();
        }
    }
}

template<class T>
void HashTable<T>::createTableFromArray(Pair<int, T>* array, AVLTree<int, T>* newTable) {
    for(int i=0; i<numElements; i++) {
        Pair<int, T> currentElem = array[i];
        insertToCell(currentElem.getKey(), currentElem.getValue(), newTable);
    }
}

template<class T>
T HashTable<T>::lookup(int key) const {
    table[hash(key)].search(key);
}

template<class T>
T HashTable<T>::remove(int key) {
    // ASSUMPTION - T has copy c'tor
    T removedData = table[hash(key)].remove(key);
    numElements--;

    if(numElements <= tableSize/SHRINKING_RATE) {
        shrinkTable();
    }

    return removedData;
}

template<class T>
void HashTable<T>::shrinkTable() {
    createAndCopyTable(tableSize/EXPANSION_RATE);
}

template<class T>
void HashTable<T>::print() {
    for(int i=0; i<tableSize; i++) {
        cout << "index: " << i << endl;
        if(table[i].isEmpty()) {
            cout << "--EMPTY--" << endl;
        } else {
            table[i].printTree();
        }
        cout << "-------------------------------" << endl;
    }
}

template<class T>
int HashTable<T>::size() {
    return numElements;
}

#endif //MIVNEI_EX2_HASHTABLE_H
