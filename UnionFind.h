#ifndef MIVNEI_EX2_UNIONFIND_H
#define MIVNEI_EX2_UNIONFIND_H

#include "HashTable.h"
#include "wet2util.h"
#include "Player.h"
#include "Team.h"

// Forward declaration
class Team;

class UnionFind {
public:
    UnionFind();
    UnionFind(const UnionFind& uf) = delete;
    UnionFind& operator=(const UnionFind& uf) = delete;
    ~UnionFind() = default;

    class PlayerNode {
        int playerId;
        Player* player;
        PlayerNode* parent;
        Team* team;
        int games;
        permutation_t insertSpirit;
        permutation_t extractSpirit;

    public:
        PlayerNode(int playerId, Player* player, PlayerNode* parent, Team* team,
                   int games, permutation_t& insertSpirit, permutation_t& extractSpirit);
        PlayerNode(const PlayerNode& node) = default;
        PlayerNode& operator=(const PlayerNode& node) = default;
        ~PlayerNode() = default;
        void setTeam(Team* newTeam);
        Player* getPlayer() const;
        PlayerNode* getParent() const;
        int getGames() const;
        Team* getTeam() const;
        permutation_t getInsertSpirit() const;
        permutation_t getExtractSpirit() const;
        void setInsertSpirit(const permutation_t& inSpirit);
        void setExtractSpirit(const permutation_t& exSpirit);
        void setParent(PlayerNode* node);
        void incrementGames();
    };

    PlayerNode* insert(int playerId, Player* player,
                       int teamId, Team* team, int initGames);
    void unite(Team* buyer, Team* bought);
    Team* find(int memberKey);
    Player* get(int memberKey) const;
    PlayerNode* getNode(int memberKey);
    bool isExist(int playerId) const;

private:
    HashTable<PlayerNode*> nodes;
    int numNodes;
    int numSets;

    static const int INIT_SETS_TABLE_VALUE = 2;
    static const int INIT_NODES_TABLE_VALUE = 2;

    static void compressPaths(PlayerNode* node, PlayerNode* root);
};

#endif //MIVNEI_EX2_UNIONFIND_H
