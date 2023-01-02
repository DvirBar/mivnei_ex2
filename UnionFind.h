#ifndef MIVNEI_EX2_UNIONFIND_H
#define MIVNEI_EX2_UNIONFIND_H

#include "HashTable.h"

// S - Set, M - Member
template<class S, class M>
class UnionFind {
public:
    UnionFind();
    UnionFind(const UnionFind<S, M>& uf) = delete;
    UnionFind& operator=(const UnionFind<S, M>& uf) = delete;
    ~UnionFind() = default;

    class Node {
        int key;
        M data;
        Node* parent;
        S set;

    public:
        Node(int key, M data, Node* parent, S set);
        Node(const Node& node) = default;
        Node& operator=(const Node& node) = default;
        ~Node() = default;
    };

    Node* insert(int memberKey, M memberData, Node* parent, int setKey, S setData);
    void unite(int set1Key, int set2Key);
    S find(int memberKey);
    M get(int memberKey);

private:
    HashTable<Node*> nodes;
    int numNodes;
    int numSets;

    static const int INIT_SETS_TABLE_VALUE = 2;
    static const int INIT_NODES_TABLE_VALUE = 2;
};

template<class S, class M>
UnionFind<S, M>::UnionFind():
    numNodes(0),
    numSets(0),
    nodes(INIT_NODES_TABLE_VALUE)
{}

template<class S, class M>
UnionFind<S, M>::Node::Node(int key, M data, Node *parent, S set):
    key(key),
    data(data),
    parent(parent)
{}

template<class S, class M>
typename UnionFind<S, M>::Node* UnionFind<S, M>::insert(int memberKey, M memberData, Node* parent, int setKey, S setData) {
    Node* node = new Node(memberKey, memberData, parent, setKey, setData);
    nodes.insert(memberKey, node);

    return node;
}

#endif //MIVNEI_EX2_UNIONFIND_H
