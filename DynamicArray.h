//
// Created by 222ro on 27-Dec-22.
//

#ifndef MIVNEI_EX2_DYNAMICARRAY_H
#define MIVNEI_EX2_DYNAMICARRAY_H


template <class T>
class DynamicArray {
private:
    int arraySize;
    int index;
    T* dataArray;
    void growArray();
    void shrinkArray();
    void copyArray(int newSize);
    static const int INITIAL_SIZE = 2;
    static const int EXPAND_RATE = 2;
    static const int SHRINKING_CONDITION = 4;

public:
    DynamicArray();
    DynamicArray(const DynamicArray& dynamicArray);
    DynamicArray& operator=(const DynamicArray& dynamicArray);
    ~DynamicArray();

    void push(const T& newData);
    const T& top() const;
    T pop();


};

template <class T>
DynamicArray<T>::DynamicArray() :
    arraySize(INITIAL_SIZE),
    index(0),
    dataArray(new T[INITIAL_SIZE])
{ }

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &dynamicArray) :
    arraySize(dynamicArray.arraySize),
    index(dynamicArray.index),
    dataArray(new T[dynamicArray.arraySize])
{
    for(int i = 0; i < arraySize; i++) {
        dataArray[i] = dynamicArray.dataArray[i];
    }
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& dynamicArray) {
    if(this == &dynamicArray) {
        return *this;
    }

    T* newArray = new T[dynamicArray.arraySize];
    for(int i = 0; i < arraySize; i++) {
        newArray[i] = dynamicArray.dataArray[i];
    }

    delete[] dynamicArray.dataArray;
    dataArray = newArray;
    arraySize = dynamicArray.arraySize;
    index = dynamicArray.index;
}

template <class T>
DynamicArray<T>::~DynamicArray() {
    delete[] dataArray;
}

template <class T>
void DynamicArray<T>::copyArray(int newSize) {
    T* newData = new T[newSize];
    for(int i = 0; i < arraySize; i++) {
        newData[i] = dataArray[i];
    }

    delete[] dataArray;
    dataArray = newData;
    arraySize = newSize;
}


template <class T>
void DynamicArray<T>::growArray() {
    int newSize = arraySize * EXPAND_RATE;
    copyArray(newSize);
}

template <class T>
void DynamicArray<T>::shrinkArray() {
    int newSize = arraySize / EXPAND_RATE;
    copyArray(newSize);
}

template <class T>
void DynamicArray<T>::push(const T& newData) {
    if(index >= arraySize)
        growArray();
    dataArray[index] = newData;
    index++;
}

template <class T>
const T& DynamicArray<T>::top() const {
    return dataArray[index - 1];
}

template <class T>
T DynamicArray<T>::pop() {
    if(index <= arraySize / SHRINKING_CONDITION)
        shrinkArray();
    T poppedData = dataArray[index - 1]; // T Assumption : Copy Constructor
    index--;
    return poppedData;
}










#endif //MIVNEI_EX2_DYNAMICARRAY_H
