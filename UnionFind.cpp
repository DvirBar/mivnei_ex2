#include "UnionFind.h"

UnionFind::UnionFind():
        numNodes(0),
        numSets(0),
        nodes(INIT_NODES_TABLE_VALUE)
{}

UnionFind::PlayerNode::PlayerNode(int playerId, Player* player, PlayerNode* parent, Team* team,
                              int games, permutation_t& insertSpirit, permutation_t& extractSpirit):
        playerId(playerId),
        player(player),
        parent(parent),
        team(team),
        games(games),
        insertSpirit(insertSpirit),
        extractSpirit(extractSpirit)
{}

typename UnionFind::PlayerNode* UnionFind::insert(int playerId, Player* player,
                                int teamId, Team* team, int initGames) {
    PlayerNode* head = team->getHead();
    int games = initGames;
    permutation_t insertSpirit = permutation_t::neutral();
    permutation_t extractSpirit = player->getSpirit();
    permutation_t headInsertSpirit;

    if(head != nullptr) {
        headInsertSpirit = head->getInsertSpirit()*player->getSpirit();
        extractSpirit = headInsertSpirit;

        head->setInsertSpirit(headInsertSpirit);

        insertSpirit = player->getSpirit();
        games = initGames - head->getGames();
    }

    auto node = new PlayerNode(playerId, player, head, team, games,
                               insertSpirit, extractSpirit);
    nodes.insert(playerId, node);

    return node;
}

void UnionFind::PlayerNode::setTeam(Team* newTeam) {
    team = newTeam;
}

Player* UnionFind::PlayerNode::getPlayer() const{
    return player;
}

Player* UnionFind::get(int playerId) const {
    return nodes.lookup(playerId)->getPlayer();
}

typename UnionFind::PlayerNode* UnionFind::getNode(int playerId) {
    return nodes.lookup(playerId);
}

typename UnionFind::PlayerNode* UnionFind::PlayerNode::getParent() const {
    return parent;
}

int UnionFind::PlayerNode::getGames() const {
    return games;
}

permutation_t UnionFind::PlayerNode::getInsertSpirit() const {
    return insertSpirit;
}

permutation_t UnionFind::PlayerNode::getExtractSpirit() const {
    return extractSpirit;
}

Team* UnionFind::PlayerNode::getTeam() const {
    return team;
}

void UnionFind::PlayerNode::setInsertSpirit(const permutation_t& inSpirit) {
    insertSpirit = inSpirit;
}

void UnionFind::PlayerNode::setExtractSpirit(const permutation_t& exSpirit) {
    extractSpirit = exSpirit;
}

bool UnionFind::isExist(int playerId) const {
    try {
        this->get(playerId);
        return true;
    } catch (const KeyNotFound& error) {
        return false;
    }
}

void UnionFind::unite(Team* buyer, Team* bought) {
    PlayerNode* buyerHead = buyer->getHead();
    PlayerNode* boughtHead = bought->getHead();

    if(buyer->getNumPlayers() > bought->getNumPlayers()) {
        // TODO: split to separated functions
        bought->setHead(buyerHead);
        boughtHead->setParent(buyerHead);
        permutation_t buyerInSpirit = buyerHead->getInsertSpirit();
        permutation_t boughtInSpirit = boughtHead->getInsertSpirit();
        permutation_t boughtExSpirit = boughtHead->getExtractSpirit();
        // TODO: double check the permutations here
        buyerHead->setInsertSpirit(buyerInSpirit*boughtExSpirit*boughtInSpirit);
        boughtHead->setExtractSpirit(buyerInSpirit*boughtInSpirit);
    } else {
//       AKA IF: buyer->getNumPlayers() <= bought->getNumPlayers()
        buyer->setHead(boughtHead);
        buyerHead->setParent(boughtHead);

        permutation_t buyerExSpirit = buyerHead->getExtractSpirit();
        permutation_t buyerInSpirit = buyerHead->getInsertSpirit();
        permutation_t boughtExSpirit = boughtHead->getExtractSpirit();
        permutation_t newBoughtExSpirit = buyerExSpirit*buyerInSpirit*boughtExSpirit;
        boughtHead->setExtractSpirit(newBoughtExSpirit);
        buyerHead->setExtractSpirit(newBoughtExSpirit.inv()*buyerExSpirit);
    }
}

void UnionFind::PlayerNode::setParent(PlayerNode* node) {
    parent = node;
}