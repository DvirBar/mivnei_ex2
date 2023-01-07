#include "Team.h"
#include "AVLTree.h"
#include "Tuple.h"
#include "Pair.h"

Team::Team(int teamId) :
        teamId(teamId),
        totalPoints(0),
        totalCards(0),
        totalGoals(0),
        totalPlayerAbility(0),
        numGoalkeepers(0),
        totalGamesPlayed(0),
        teamSpirit(permutation_t::neutral()),
        numPlayers(0),
        head(nullptr)
{}

int Team::getNumPlayers() const {
    return numPlayers;
}

int Team::getNumGoalKeepers() const {
    return numGoalkeepers;
}

void Team::addPoints(int pointsToAdd) {
    totalPoints += pointsToAdd;
}

void Team::addGame() {
    totalGamesPlayed++;
}

void Team::setGoalKeepers(int numGoalkeeper) {
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

void Team::incrementNumGoalKeepers() {
    numGoalkeepers++;
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

int Team::getId() const{
    return teamId;
}

void Team::addAbility(const int abilityToAdd) {
    totalPlayerAbility += abilityToAdd;
}

int Team::getTotalPlayerAbility() const {
    return totalPlayerAbility;
}

int Team::getTotalTeamAbility() const {
    return totalPlayerAbility + totalPoints;
}

int Team::getSpiritStrength() const {
    return teamSpirit.strength();
}

void Team::setHead(PlayerNode *newHead) {
    head = newHead;
}

int Team::getTotalStats() const {
    return totalPoints + totalGoals - totalCards;
}

void Team::addNumPlayers(int playersToAdd) {
    numPlayers += playersToAdd;
}

PlayerNode* Team::getHead() {
    return head;
}

