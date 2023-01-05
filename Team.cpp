#include "Team.h"
#include "AVLTree.h"
#include "Tuple.h"
#include "Pair.h"

Team::Team(int teamId, int points) :
        teamId(teamId),
        totalPoints(points),
        totalCards(0),
        totalGoals(0),
        numGoalkeepers(0),
        teamTopScorer(nullptr),
        nextValidRank(nullptr),
        prevValidRank(nullptr),
        totalGamesPlayed(0),
        numPlayers(0),
        head(nullptr),
        teamPlayersByID(),
        teamPlayersByStats()
{}

int Team::getNumPlayers() const {
    return numPlayers;
}

int Team::getNumGoalKeepers() const {
    return numGoalkeepers;
}

bool Team::isValidTeam() const {
    return ((getNumPlayers() >= 11) && (numGoalkeepers > 0));
}

void Team::addPoints(int pointsToAdd) {
    totalPoints += pointsToAdd;
}

void Team::addGame() {
    totalGamesPlayed++;
}

void Team::setGoalGoalKeepers(int numGoalkeeper) {
    this->numGoalkeepers = numGoalkeeper;
}

void Team::setCards(int cards) {
    totalCards += cards;
}

void Team::setGoals(int goals) {
    totalGoals += goals;
}

void Team::incrementNumPlayers() {
    numPlayers++;
}

int Team::getTotalGoals() const {
    return totalGoals;
}

int Team::getTotalCards() const {
    return totalCards;
}

int Team::getTotalPoints() const {
    return totalPoints;
}

int Team::getTotalGamesPlayed() const {
    return totalGamesPlayed;
}

const AVLTree<Tuple, Player *>& Team::getStatsTree() const {
    return teamPlayersByStats;
}

void Team::uniteTopScorers(Team* team1, Team* team2) {
    if(team1->isEmpty() && team2->isEmpty()) {
        return;
    }

    if(team1->isEmpty()) {
        teamTopScorer = team2->getTopScorer();
        return;
    }

    if(team2->isEmpty()) {
        teamTopScorer = team1->getTopScorer();
        return;
    }

    if(team1->getTopScorer()->getStatsTuple() > team2->getTopScorer()->getStatsTuple()) {
        setTopScorer(team1->getTopScorer());
    }

    else {
        setTopScorer(team2->getTopScorer());
    }
}

void Team::createStatsArray(Pair<Tuple, Player*>* arr) {
    teamPlayersByStats.inorderDataToArray(arr);
}

void Team::createIdsArray(Pair<int, Player*>* arr) {
    teamPlayersByID.inorderDataToArray(arr);
}

void Team::fillStatsFromArray(Pair<Tuple, Player*>* arr, int size) {
    teamPlayersByStats.populateFromArray(arr, size);
}

void Team::fillIdsFromArray(Pair<int, Player*>* arr, int size) {
    teamPlayersByID.populateFromArray(arr, size);
}

Player* Team::findPlayerById(int playerId) {
    return teamPlayersByID.search(playerId);
}

void Team::removePlayer(int playerId) {
    Player* playerToRemove = teamPlayersByID.remove(playerId);
    teamPlayersByStats.remove(playerToRemove->getStatsTuple());
    int playerGoals = playerToRemove->getGoals();
    int playerCards = playerToRemove->getCards();
    setGoals(-playerGoals);
    setCards(-playerCards);

    if(playerToRemove->isGoalKeeper())
        numGoalkeepers--;
}

bool Team::isEmpty() {
    return teamPlayersByID.isEmpty();
}

void Team::addPlayer(Player* playerToInsert) {
    teamPlayersByID.insert(playerToInsert->getId(), playerToInsert);
    teamPlayersByStats.insert(playerToInsert->getStatsTuple(), playerToInsert);
    setGoals(playerToInsert->getGoals());
    setCards(playerToInsert->getCards());
    if(playerToInsert->isGoalKeeper())
        numGoalkeepers++;
}

int Team::getId() const{
    return teamId;
}

Player* Team::getTopScorer() const {
    return teamTopScorer;
}

void Team::setTopScorer(Player* newTopScorer) {
    teamTopScorer = newTopScorer;
}

void Team::setNextValidRank(Team* next) {
    nextValidRank = next;
}

void Team::setPrevValidRank(Team* prev) {
    prevValidRank = prev;
}

void Team::setHead(UnionFind::PlayerNode *newHead) {
    head = newHead;
}

int Team::getTeamId() const {
    return teamId;
}

Team* Team::getNextValidRank() const {
    return nextValidRank;
}

Team* Team::getPrevValidRank() const {
    return prevValidRank;
}

int Team::getTotalStats() const {
    return totalPoints + totalGoals - totalCards;
}

typename UnionFind::PlayerNode* Team::getHead() {
    return head;
}

void Team::updateTopScorer(Player *player) {
    if(teamTopScorer == nullptr ||
       teamTopScorer->getStatsTuple() < player->getStatsTuple())
        teamTopScorer = player;
}

Player* Team::findPrev(Player* player) {
    try {
        return teamPlayersByStats.prevInorder(player->getStatsTuple());
    } catch(const NoPrevInorder& error) {
        return nullptr;
    }

}
