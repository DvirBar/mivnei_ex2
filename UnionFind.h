#ifndef MIVNEI_EX2_UNIONFIND_H
#define MIVNEI_EX2_UNIONFIND_H

#include "HashTable.h"
#include "wet2util.h"
#include "Player.h"
#include "Team.h"
#include "PlayerNode.h"

class Team;
class PlayerNode;
class Player;

class UnionFind {
public:
    UnionFind();
    UnionFind(const UnionFind& uf) = delete;
    UnionFind& operator=(const UnionFind& uf) = delete;
    ~UnionFind();

    PlayerNode* insert(int playerId, Player* player, Team* team, int initGames);
    void unite(Team* buyer, Team* bought);
    Team* find(int playerId);
    int findGames(int playerId);
    permutation_t findPartialSpirit(int playerId);
    PlayerNode* findAux(int playerId, int* summedNumGames, permutation_t* multipliedPermutation, PlayerNode* lookedUpNode);
    Player* get(int playerId) const;
    PlayerNode* getNode(int playerId);
    bool isExist(int playerId) const;

private:
    HashTable<PlayerNode*> nodes;
    
    static const int INIT_NODES_TABLE_VALUE = 2;

    static void compressPaths(PlayerNode* node, PlayerNode* root, int totalSum, const permutation_t& totalPermutation);
};

#endif //MIVNEI_EX2_UNIONFIND_H
