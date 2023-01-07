#ifndef PLAYER_H_
#define PLAYER_H_

#include "wet2util.h"
#include "AVLTree.h"
#include "Team.h"
#include "Tuple.h"
#include "PlayerNode.h"

// Forward declaration to break circular dependancy
class Team;
class UnionFind;

class Player {
public:
    Player(const permutation_t& spirit, int gamesPlayed,
           int cards, bool goalKeeper);

    Player(const Player &player) = default;
    ~Player() = default;
    int getId() const;

    // TODO: implement
    bool isGoalKeeper() const;
    int getCards() const;
    void addCards(int cards);
    permutation_t getSpirit() const;
    void setCards(int cards);
    void setIsGoalKeeper(bool isGoalKeeper);
//    void removeFromTeam();

private:
    int cards;
    bool goalKeeper;
    permutation_t spirit;
};

#endif // PLAYER_H_
