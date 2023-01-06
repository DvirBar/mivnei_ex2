#include "Player.h"
#include "Team.h"
#include "Exception.h"
#include "Tuple.h"

Player::Player(
        int playerId, const permutation_t& spirit, int ability, int gamesPlayed,
        int cards, bool goalKeeper):
        goalKeeper(goalKeeper),
        prevRank(nullptr),
        nextRank(nullptr),
        ability(ability),
        playerId(playerId),
        cards(cards)
{}

int Player::getId() const {
    return playerId;
}

permutation_t Player::getSpirit() const {
    return spirit;
};

void Player::updateNextInRank(Player* next) {
    nextRank = next;
}

void Player::updatePrevInRank(Player* prev) {
    prevRank = prev;
}

//const Tuple Player::getStatsTuple() const {
//    return Tuple(goals, cards, playerId);
//}

int Player::getCards() const {
    return cards;
}

bool Player::isGoalKeeper() const {
    return goalKeeper;
}

void Player::addCards(int cards) {
    this->cards += cards;
}

void Player::setCards(int cards) {
    this->cards = cards;
}

void Player::setIsGoalKeeper(bool isGoalKeeper) {
    this->goalKeeper = isGoalKeeper;
}

Player* Player::getRankNext() const {
    return nextRank;
}

Player* Player::getRankPrev() const {
    return prevRank;
}

