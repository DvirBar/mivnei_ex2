#ifndef MIVNEI_EX2_UNIONFIND_H
#define MIVNEI_EX2_UNIONFIND_H

#include "HashTable.h"

// S - Set, M - Member
template<class S, class M>
class UnionFind {
    // Forward declaration
    class Set;
    class Node {
    public:
        int key;
        M data;
        Set* set;
        Node* parent;

        Node(int key, M data, Set* set, Node* parent);
        Node(const Node& node) = default;
        Node& operator=(const Node& node) = default;
        ~Node() = default;
    };

    class Set {
    public:
        int key;
        S data;
        Node head;
        int numElements;

        Set(int key, S data, Node* head);
        Set(const Set& set) = default;
        Set& operator=(const Set& set) = default;
        ~Set() = default;
    };

    HashTable<Set*> sets;
    HashTable<Node*> nodes;
    int numNodes;
    int numSets;

    static const int INIT_SETS_TABLE_VALUE = 2;
    static const int INIT_NODES_TABLE_VALUE = 2;
public:
    UnionFind();
    UnionFind(const UnionFind<S, M>& uf) = delete;
    UnionFind& operator=(const UnionFind<S, M>& uf) = delete;
    ~UnionFind() = default;

    void insert(int memberKey, M memberData, int setKey, S setData);
    void unite(int set1Key, int set2Key);
    S find(int memberKey);
    M get(int memberKey);
};

template<class S, class M>
UnionFind<S, M>::UnionFind():
    numNodes(0),
    numSets(0),
    sets(INIT_SETS_TABLE_VALUE),
    nodes(INIT_NODES_TABLE_VALUE)
{}

template<class S, class M>
UnionFind<S, M>::Node::Node(int key, M data, Set *set, Node *parent):
    key(key),
    data(data),
    set(set),
    parent(parent)
{}

template<class S, class M>
UnionFind<S, M>::Set::Set(int key, S data, Node* head):
    key(key),
    data(data),
    numElements(1)
{
    head->parent(this);
}

template<class S, class M>
void UnionFind<S, M>::insert(int memberKey, M memberData, int setKey, S setData) {
    Set* set = nullptr;
    Node* newNode = nullptr;
    try {
        set = sets.lookup(setKey);
        newNode = new Node(memberKey, memberData, set, set->head);
    } catch(const KeyNotFound& error) {
        newNode = newNode(memberKey, memberData, nullptr, nullptr);
        set = new Set(setKey, setData, newNode);
        sets.insert(setKey, setData);
    }

    set->numElements++;
    nodes.insert(memberKey, memberData);
}

#endif //MIVNEI_EX2_UNIONFIND_H
