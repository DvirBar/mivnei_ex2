#include "UnionFind.h"

UnionFind::UnionFind():
    nodes(INIT_NODES_TABLE_VALUE)
{}

UnionFind::~UnionFind() {
    auto nodesArray = new Pair<int, PlayerNode*>[nodes.size()];

    nodes.extractToArray(nodesArray);
    PlayerNode* currentNode;
    for(int i=0; i<nodes.size(); i++) {
        currentNode = nodesArray[i].getValue();
        delete currentNode->getPlayer();
        delete currentNode;
    }

    delete[] nodesArray;
}

PlayerNode* UnionFind::insert(int playerId, Player* player, Team* team, int initGames) {
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

    auto node = new PlayerNode(player, head, games,
                               insertSpirit, extractSpirit);
    nodes.insert(playerId, node);

    if(team->getNumPlayers() == 0) {
        team->setHead(node);
        node->setTeam(team);
    }

    return node;
}



Player* UnionFind::get(int playerId) const {
    return nodes.lookup(playerId)->getPlayer();
}

PlayerNode* UnionFind::getNode(int playerId) {
    return nodes.lookup(playerId);
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

    if((buyerHead == nullptr && boughtHead == nullptr) || (boughtHead == nullptr)) {
        return;
    }

    if(buyerHead == nullptr) {
        buyer->setHead(boughtHead);
        buyer->getHead()->setTeam(buyer);
        return;
    }
    if(buyer->getId() == 70841) {
        cout << "hello" << endl;
    }
    if(buyer->getNumPlayers() >= bought->getNumPlayers()) {
        // TODO: split to separated functions
        boughtHead->setParent(buyerHead);
        boughtHead->setGames(boughtHead->getGames()-buyerHead->getGames());

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
        boughtHead->setTeam(buyer);
        buyerHead->setGames(buyerHead->getGames()-boughtHead->getGames());

        permutation_t buyerExSpirit = buyerHead->getExtractSpirit();
        permutation_t buyerInSpirit = buyerHead->getInsertSpirit();
        permutation_t boughtExSpirit = boughtHead->getExtractSpirit();
        permutation_t newBoughtExSpirit = buyerExSpirit*buyerInSpirit*boughtExSpirit;
        boughtHead->setExtractSpirit(newBoughtExSpirit);
        buyerHead->setExtractSpirit(newBoughtExSpirit.inv()*buyerExSpirit);
    }

}



Team* UnionFind::find(int playerId) {
    PlayerNode* lookedUpNode = nodes.lookup(playerId);
    int summedNumGames = 0;
    permutation_t multipliedPermutation = permutation_t::neutral();
    PlayerNode* root = findAux(playerId, &summedNumGames, &multipliedPermutation, lookedUpNode);

    compressPaths(lookedUpNode, root, summedNumGames, multipliedPermutation);

    return root->getTeam();
}

PlayerNode* UnionFind::findAux(int playerId, int* summedNumGames, permutation_t* multipliedPermutation, PlayerNode* lookedUpNode) {
    *summedNumGames = 0;
    *multipliedPermutation = permutation_t::neutral();

    while(lookedUpNode->getParent() != nullptr) {
        *summedNumGames += lookedUpNode->getGames();
        *multipliedPermutation = *multipliedPermutation * lookedUpNode->getExtractSpirit();
        lookedUpNode = lookedUpNode->getParent();
    }

    return lookedUpNode;
}

int UnionFind::findGames(int playerId) {
    PlayerNode* lookedUpNode = nodes.lookup(playerId);
    int summedNumGames = 0;
    permutation_t multipliedPermutation = permutation_t::neutral();
    PlayerNode* root = findAux(playerId, &summedNumGames, &multipliedPermutation, lookedUpNode);

    compressPaths(lookedUpNode, root, summedNumGames, multipliedPermutation);

    return summedNumGames+root->getGames();
}

permutation_t UnionFind::findPartialSpirit(int playerId) {
    PlayerNode* lookedUpNode = nodes.lookup(playerId);
    int summedNumGames = 0;
    permutation_t multipliedPermutation = permutation_t::neutral();
    PlayerNode* root = findAux(playerId, &summedNumGames, &multipliedPermutation, lookedUpNode);

    compressPaths(lookedUpNode, root, summedNumGames, multipliedPermutation);

    return root->getExtractSpirit()*multipliedPermutation;
}


void UnionFind::compressPaths(PlayerNode *node, PlayerNode *root, int totalSum, const permutation_t& totalPermutation) {
    PlayerNode* prevNode;
    int sumToSubtract = 0, currentGames = 0;
    permutation_t currentPermutation = permutation_t::neutral();
    permutation_t permutationToSubtract = permutation_t::neutral();

    while(node->getParent() != nullptr) {
        prevNode = node;

        node = node->getParent();

        currentGames = prevNode->getGames();
        prevNode->setGames(totalSum - sumToSubtract);
        sumToSubtract += currentGames;

        currentPermutation = prevNode->getExtractSpirit();
        prevNode->setExtractSpirit(totalPermutation * permutationToSubtract.inv());
        permutationToSubtract = permutationToSubtract * currentPermutation;

        prevNode->setParent(root);
    }
}