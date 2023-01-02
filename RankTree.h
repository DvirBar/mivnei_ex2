#ifndef MIVNEI_EX2_RANKTREE_H
#define MIVNEI_EX2_RANKTREE_H

#include <stdio.h>
#include <iostream>
#include "Pair.h"
#include "Exception.h"

using namespace std;

template <class K, class T>
class RankTree {
    class RankNode {
    public:
        K key;
        T data;
        RankNode *leftChild;
        RankNode *rightChild;
        int height;
        int weight;

        RankNode();
        RankNode(const K& key, const T& data);

        RankNode(const RankNode &) = default;
        RankNode& operator=(const RankNode &) = default;

        void updateHeight();
        void updateWeight();
        bool isLeaf();

        RankNode* RRrotation();
        RankNode* LLrotation();
        RankNode* RLrotation();
        RankNode* LRrotation();
        RankNode* execRotation();
    };

    RankNode* root;
    int numNodes;
    RankNode* execRemove(RankNode* node);

    RankNode* insertByNode(RankNode* node, const K& key, const T& data);
    typename RankTree<K, T>::RankNode* removeAux(const K& key, RankNode* node, T* data);

    RankNode* baseRemove(RankNode* node);
    RankNode* removeInorder(RankNode* node, RankNode* replacedNode);

    void buildNearlyComplete(int size);
    void removeLeavesAux(RankNode* node, RankNode* parent, int size);

    static int getNodeBalanceFactor(RankNode* node);
    static int getNodeHeight(RankNode* node);
    static int getNodeWeight(RankNode* node);
    static void deleteTreeAux(RankNode* node);
    static void buildNearlyCompleteAux(RankNode* node, int height);
    static void inorderToArrayAUX(const RankNode* node, Pair<K,T>* array, int* index);
    static void populateFromArrayAux(RankNode* node, Pair<K, T>* array, int* index);
    static const RankNode* searchByNode(const RankNode* node, const K& key);
    static const T& firstInRangeAux(RankNode *node, T* lastValid, const K &range);

    static const int COUNT = 10;

public:
    RankTree();
    RankTree(const RankTree &tree) = delete;
    RankTree& operator=(const RankTree &tree) = delete;
    ~RankTree();

    RankNode* insert(const K& key, const T& data);
    T remove(const K& key);
    bool isExist(const K& key) const;
    const T& search(const K& key) const;
    const T& nextInorder(const K& currentKey) const;
    const T& prevInorder(const K& currentKey) const;
    void inorderDataToArray(Pair<K,T>* array) const;
    int Rank(const K& key) const;

    int getNumNodes() const;
    const T& findFirstInRange(const K& range) const;
    bool isEmpty() const;
    void printTree() const;
    void populateFromArray(Pair<K, T>* array, int size);
    static void mergeArrays(Pair<K, T>* newArr, int newArrSize, Pair<K, T>* arr1,
                            int arr1Size, Pair<K, T>* arr2, int arr2Size);
    static void print2DUtil(RankNode* node, int space);
    static int maxValue(int value1, int value2);
};

template <class K, class T>
RankTree<K, T>::RankTree():
        root(nullptr),
        numNodes(0)
{}

template <class K, class T>
RankTree<K, T>::~RankTree() {
    if(!isEmpty()) {
        deleteTreeAux(root);
    }
}

template <class K, class T>
int RankTree<K, T>::getNumNodes() const {
    return numNodes;
}

template <class K, class T>
void RankTree<K, T>::deleteTreeAux(RankNode *node)
{
    if (node->leftChild != nullptr)
    {
        deleteTreeAux(node->leftChild);
    }

    if (node->rightChild != nullptr)
    {
        deleteTreeAux(node->rightChild);
    }

    delete node;
}

template<class K, class T>
RankTree<K, T>::RankNode::RankNode(const K& key, const T& data):
        key(key),
        data(data),
        leftChild(nullptr),
        rightChild(nullptr),
        height(0),
        weight(1)
{}

template<class K, class T>
RankTree<K, T>::RankNode::RankNode():
        leftChild(nullptr),
        rightChild(nullptr),
        height(0),
        weight(1)
{}


template<class K, class T>
typename RankTree<K, T>::RankNode* RankTree<K, T>::RankNode::RRrotation()
{
    RankNode* newParent = rightChild;
    RankNode* rightGrandChild = newParent->leftChild;

    newParent->leftChild = this;
    rightChild = rightGrandChild;

    updateHeight();
    newParent->updateHeight();

    // Update weight
    int newParentWeight = this->weight;
    this->weight = 1+rightGrandChild->weight+leftChild->weight;
    newParent = newParentWeight;

    return newParent;
}

template <class K, class T>
typename RankTree<K, T>::RankNode* RankTree<K, T>::RankNode::LLrotation()
{
    RankNode* newParent = leftChild;
    RankNode* newLeftGrandChild = newParent->rightChild;

    newParent->rightChild = this;
    leftChild = newLeftGrandChild;

    updateHeight();
    newParent->updateHeight();

    // Update weight
    int newParentWeight = this->weight;
    this->weight = 1+newLeftGrandChild->weight+rightChild->weight;
    newParent->weight = newParentWeight;

    return newParent;
}

template <class K, class T>
typename RankTree<K, T>::RankNode* RankTree<K, T>::RankNode::RLrotation()
{
    this->rightChild = rightChild->LLrotation();
    RankNode* newParent = RRrotation();

    return newParent;
}

template <class K, class T>
typename RankTree<K, T>::RankNode* RankTree<K, T>::RankNode::LRrotation()
{
    this->leftChild = leftChild->RRrotation();
    RankNode* newParent = LLrotation();
    return newParent;
}

template <class K, class T>
const typename RankTree<K, T>::RankNode* RankTree<K, T>::searchByNode(const RankTree::RankNode* node, const K& key) {
    if (node == nullptr)
        throw KeyNotFound();

    if (node->key == key)
        return node;

    if (node->key > key)
        return searchByNode(node->leftChild, key);
    else
        return searchByNode(node->rightChild, key);
}

template <class K, class T>
const T& RankTree<K, T>::search(const K &key) const {
    return (searchByNode(root, key))->data;
}

template <class K, class T>
typename RankTree<K, T>::RankNode* RankTree<K, T>::insertByNode(RankTree::RankNode *node,
                                                             const K &key, const T &data) {
    if (node == nullptr) {
        RankTree::RankNode *newLeaf = new RankTree::RankNode(key, data);
        return newLeaf;
    }
    if (node->key > key)
        node->leftChild = insertByNode(node->leftChild, key, data);
    else
        node->rightChild = insertByNode(node->rightChild, key, data);

    node->updateHeight();
    node->updateWeight();
    return node->execRotation();
}

template <class K, class T>
typename RankTree<K, T>::RankNode* RankTree<K, T>::RankNode::execRotation() {
    int nodeBF = getNodeBalanceFactor(this);

    int nodeLeftChildBF = getNodeBalanceFactor(leftChild);
    int nodeRightChildBF = getNodeBalanceFactor(rightChild);

    if ((nodeBF == 2) && (nodeLeftChildBF == -1))
        return LRrotation();

    if ((nodeBF == 2) && (nodeLeftChildBF >= 0))
        return LLrotation();

    if ((nodeBF == -2) && (nodeRightChildBF == 1))
        return RLrotation();

    if ((nodeBF == -2) && (nodeRightChildBF <= 0))
        return RRrotation();

    return this;
}

template <class K, class T>
typename RankTree<K, T>::RankNode *RankTree<K, T>::insert(const K &key, const T &data)
{
    root = insertByNode(root, key, data);
    numNodes++;
    return root;
}

template <class T, class K>
int RankTree<T, K>::getNodeHeight(RankTree::RankNode *node) {
    if (node == nullptr)
        return -1;
    return node->height;
}


template <class T, class K>
int RankTree<T, K>::getNodeWeight(RankTree::RankNode *node) {
    if(node == nullptr)
        return 0;
    return node->weight;
}


template <class K, class T>
void RankTree<K, T>::RankNode::updateHeight() {
    height = maxValue(getNodeHeight(leftChild), getNodeHeight(rightChild)) + 1;
}

template <class K, class T>
int RankTree<K, T>::getNodeBalanceFactor(RankNode* node) {
    if(node == nullptr) {
        return 0;
    }

    return getNodeHeight(node->leftChild) - getNodeHeight(node->rightChild);
}

template <class K, class T>
void RankTree<K, T>::RankNode::updateWeight() {
    weight = getNodeWeight(leftChild) + getNodeWeight(rightChild) + 1;
}

template <class K, class T>
bool RankTree<K, T>::isEmpty() const {
    return root == nullptr;
}

template <class K, class T>
T RankTree<K, T>::remove(const K& key) {
    if(isEmpty()) {
        throw KeyNotFound();
    }

    T data;
    root = removeAux(key, root, &data);
    numNodes--;
    return data;
}

template <class K, class T>
typename RankTree<K, T>::RankNode* RankTree<K, T>::removeAux(const K& key, RankNode* node, T* data) {
    if(node == nullptr) {
        throw KeyNotFound();
    }

    if(node->key == key) {
        *data = node->data;
        return execRemove(node);
    }

    if(node->key > key) {
        node->leftChild = removeAux(key, node->leftChild, data);
    }

    if(node->key < key) {
        node->rightChild = removeAux(key, node->rightChild, data);
    }

    node->updateWeight();

    return node->execRotation();
}


template <class K, class T>
typename RankTree<K, T>::RankNode* RankTree<K, T>::execRemove(RankNode* node) {
    if(node->leftChild != nullptr && node->rightChild != nullptr) {
        node->rightChild = removeInorder(node->rightChild, node);
        return node->execRotation();

    }

    return baseRemove(node);
}


template <class K, class T>
typename RankTree<K, T>::RankNode* RankTree<K, T>::removeInorder(RankNode* node, RankNode* replacedNode) {
    if(node->leftChild == nullptr) {
        replacedNode->key = node->key;
        replacedNode->data = node->data;
        return baseRemove(node);
    }


    node->leftChild = removeInorder(node->leftChild, replacedNode);
    return node->execRotation();
}

template<class K, class T>
typename RankTree<K, T>::RankNode* RankTree<K, T>::baseRemove(RankNode* node) {
    RankNode* nodeToReturn;
    if(node->leftChild != nullptr) {
        nodeToReturn = node->leftChild;
    } else {
        nodeToReturn = node->rightChild;
    }

    delete node;
    return nodeToReturn;
}




template<class K, class T>
const T& RankTree<K, T>::nextInorder(const K& currentKey) const {
    const RankNode* node = searchByNode(root, currentKey);
    RankNode* next = node->rightChild;
    if(next != nullptr) {
        while(next->leftChild != nullptr) {
            next = next->leftChild;
        }

        return next->data;
    }

    next = nullptr;

    RankNode* treeRoot = root;
    while(treeRoot != nullptr) {
        if(node->key < treeRoot->key) {
            next = treeRoot;
            treeRoot = treeRoot->leftChild;
        } else if(node->key > treeRoot->key) {
            treeRoot = treeRoot->rightChild;
        } else if(next != nullptr) {
            return next->data;
        } else {
            break;
        }
    }

    throw NoNextInorder();
}

template<class K, class T>
const T& RankTree<K, T>::prevInorder(const K& currentKey) const {
    const RankNode* node = searchByNode(root, currentKey);
    RankNode* next = node->leftChild;
    if(next != nullptr) {
        while(next->rightChild != nullptr) {
            next = next->rightChild;
        }

        return next->data;
    }

    next = nullptr;

    RankNode* treeRoot = root;
    while(treeRoot != nullptr) {
        if(node->key < treeRoot->key) {
            treeRoot = treeRoot->leftChild;
        }  else if(node->key > treeRoot->key) {
            next = treeRoot;
            treeRoot = treeRoot->rightChild;
        } else if(next != nullptr) {
            return next->data;
        } else {
            break;
        }
    }

    throw NoPrevInorder();
}

template<class K, class T>
void RankTree<K, T>::print2DUtil(RankNode* root, int space) {
    if (root == nullptr) {
        return;
    }

    space += COUNT;

    print2DUtil(root->rightChild, space);
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->key;
    print2DUtil(root->leftChild, space);
}

template<class K, class T>
void RankTree<K, T>::printTree() const {
    print2DUtil(root, 0);
    cout << endl;
    cout << "---------------" << endl;
}

template<class K, class T>
void RankTree<K, T>::inorderToArrayAUX(const RankNode* node, Pair<K, T>* array, int* index) {
    if(node != nullptr) {
        inorderToArrayAUX(node->leftChild, array, index);
        array[*index] = Pair<K, T>(node->key, node->data);
        (*index)++;
        inorderToArrayAUX(node->rightChild, array, index);
    }
}

template<class K, class T>
void RankTree<K, T>::inorderDataToArray(Pair<K,T>* array) const {
    int index = 0;
    inorderToArrayAUX(root, array, &index);
}

template<class K, class T>
bool RankTree<K, T>::isExist(const K &key) const {
    try {
        search(key);
    }
    catch(const KeyNotFound& keyNotFound) {
        return false;
    }
    return true;
}

template<class K, class T>
void RankTree<K, T>::mergeArrays(Pair<K, T>* newArr, int newArrSize, Pair<K, T>* arr1,
                                int arr1Size, Pair<K, T>* arr2, int arr2Size) {
    int newArrIndex = 0, arr1Index = 0, arr2Index = 0;

    while(arr1Index < arr1Size &&
          arr2Index < arr2Size &&
          newArrIndex < newArrSize) {
        if(arr1[arr1Index].getKey() < arr2[arr2Index].getKey()) {
            newArr[newArrIndex] = arr1[arr1Index];
            arr1Index++;
        } else {
            newArr[newArrIndex] = arr2[arr2Index];
            arr2Index++;
        }

        newArrIndex++;
    }

    while(arr1Index < arr1Size) {
        newArr[newArrIndex] = arr1[arr1Index];
        arr1Index++;
        newArrIndex++;
    }

    while(arr2Index < arr2Size) {
        newArr[newArrIndex] = arr2[arr2Index];
        arr2Index++;
        newArrIndex++;
    }
}

template<class K, class T>
const T& RankTree<K, T>::firstInRangeAux(RankNode* node, T* lastValid, const K &range) {
    if(node == nullptr) {
        if(lastValid == nullptr) {
            throw KeyNotFound();
        }

        return *lastValid;
    }


    if(node->key < range) {
        return firstInRangeAux(node->rightChild, lastValid, range);
    }

    lastValid = &(node->data);
    return firstInRangeAux(node->leftChild, lastValid, range);
}

template<class K, class T>
const T& RankTree<K, T>::findFirstInRange(const K& range) const {
    return firstInRangeAux(root, nullptr, range);
}

template<class K, class T>
int RankTree<K, T>::maxValue(int value1, int value2) {
    if(value1 >= value2)
        return value1;
    else
        return value2;
}

template<class K, class T>
void RankTree<K, T>::populateFromArray(Pair<K, T>* array, int size) {
    buildNearlyComplete(size);

    int index = 0;

    populateFromArrayAux(root, array, &index);
}

template<class K, class T>
void RankTree<K, T>::populateFromArrayAux(RankNode* node, Pair<K, T>* array, int* index) {
    if(node != nullptr) {
        populateFromArrayAux(node->leftChild, array, index);
        node->key = array[*index].getKey();
        node->data = array[*index].getValue();
        (*index)++;
        populateFromArrayAux(node->rightChild, array, index);
    }
}

template<class K, class T>
void RankTree<K, T>::buildNearlyComplete(int size) {
    if(size <= 0) {
        return;
    }
    int height = 0;
    int fullTreeSize = 1;

    while(fullTreeSize-1<size) {
        height++;
        fullTreeSize*=2;
    }

    root = new RankNode();
    buildNearlyCompleteAux(root, height-1);
    numNodes = fullTreeSize-1;
    removeLeavesAux(root, nullptr, size);
}

template<class K, class T>
void RankTree<K, T>::removeLeavesAux(RankNode* node, RankNode* parent, int size) {
    if(numNodes > size && node->isLeaf()) {
        if(parent->leftChild == node) {
            parent->leftChild = nullptr;
        } else {
            parent->rightChild = nullptr;
        }

        delete node;

        numNodes--;
        return;
    }

    if(size == numNodes) {
        return;
    }

    removeLeavesAux(node->rightChild, node, size);
    removeLeavesAux(node->leftChild, node, size);
}

template<class K, class T>
void RankTree<K, T>::buildNearlyCompleteAux(RankNode* node, int height) {
    if(height <= 0) {
        node->leftChild = nullptr;
        node->rightChild = nullptr;
        return;
    }

    node->leftChild = new RankNode();
    buildNearlyCompleteAux(node->leftChild, height-1);
    node->rightChild = new RankNode();
    buildNearlyCompleteAux(node->rightChild, height-1);
}

template<class K, class T>
bool RankTree<K, T>::RankNode::isLeaf() {
    return this->leftChild == nullptr && this->rightChild == nullptr;
}



#endif //MIVNEI_EX2_RANKTREE_H
