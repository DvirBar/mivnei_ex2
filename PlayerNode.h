//
// Created by Dvir Bartov on 07/01/2023.
//

#ifndef MIVNEI_EX2_PLAYERNODE_H
#define MIVNEI_EX2_PLAYERNODE_H

#include "Player.h"
#include "Team.h"
#include "wet2util.h"

class Player;
class Team;

class PlayerNode {
    Player* player;
    PlayerNode* parent;
    Team* team;
    int games;
    permutation_t insertSpirit;
    permutation_t extractSpirit;

public:
    PlayerNode(Player* player, PlayerNode* parent, Team* team,
               int games, permutation_t& insertSpirit, permutation_t& extractSpirit);
    PlayerNode(const PlayerNode& node) = default;
    PlayerNode& operator=(const PlayerNode& node) = default;
    ~PlayerNode() = default;
    void setTeam(Team* newTeam);
    Player* getPlayer() const;
    PlayerNode* getParent() const;
    int getGames() const;
    void setGames(int gamesToSet);
    Team* getTeam() const;
    permutation_t getInsertSpirit() const;
    permutation_t getExtractSpirit() const;
    void setInsertSpirit(const permutation_t& inSpirit);
    void setExtractSpirit(const permutation_t& exSpirit);
    void setParent(PlayerNode* node);
    void incrementGames();
};


#endif //MIVNEI_EX2_PLAYERNODE_H
