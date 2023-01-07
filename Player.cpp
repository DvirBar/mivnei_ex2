#include "Player.h"
#include "Team.h"
#include "Exception.h"
#include "Tuple.h"

Player::Player(int playerId, const permutation_t& spirit, int gamesPlayed,
        int cards, bool goalKeeper):
        playerId(playerId),
        cards(cards),
        goalKeeper(goalKeeper),
        spirit(spirit)
{}

permutation_t Player::getSpirit() const {
    return spirit;
};

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


