//
// Created by Dvir Bartov on 07/01/2023.
//

#include "PlayerNode.h"

PlayerNode::PlayerNode(Player* player, PlayerNode* parent, Team* team, int games, permutation_t& insertSpirit,
                       permutation_t& extractSpirit):
        player(player),
        parent(parent),
        team(team),
        games(games),
        insertSpirit(insertSpirit),
        extractSpirit(extractSpirit)
{}

void PlayerNode::setTeam(Team* newTeam) {
    team = newTeam;
}

Player* PlayerNode::getPlayer() const{
    return player;
}

PlayerNode* PlayerNode::getParent() const {
    return parent;
}

int PlayerNode::getGames() const {
    return games;
}

permutation_t PlayerNode::getInsertSpirit() const {
    return insertSpirit;
}

permutation_t PlayerNode::getExtractSpirit() const {
    return extractSpirit;
}

Team* PlayerNode::getTeam() const {
    return team;
}

void PlayerNode::setInsertSpirit(const permutation_t& inSpirit) {
    insertSpirit = inSpirit;
}

void PlayerNode::setExtractSpirit(const permutation_t& exSpirit) {
    extractSpirit = exSpirit;
}

void PlayerNode::setParent(PlayerNode* node) {
    parent = node;
}

void PlayerNode::setGames(int gamesToSet) {
    games = gamesToSet;
}

void PlayerNode::incrementGames() {
    games++;
}