#ifndef PLAYER_H_
#define PLAYER_H_

#include "wet2util.h"
#include "AVLTree.h"
#include "Team.h"
#include "Tuple.h"

// Forward declaration to break circular dependancy
class Team;

class Player {
public:
    Player(int playerId, const permutation_t& spirit, int ability, int gamesPlayed,
           int cards, bool goalKeeper);

    // playerId should be unique, so maybe we shouldn't allow copy?
    Player(const Player &player) = delete;
    ~Player() = default;
    StatusType update_stats(int gamesPlayed, int scoredGoals,
                            int cardsReceived);
    int getId() const;

    // TODO: implement
    Team* getTeam() const;
    bool isGoalKeeper() const;
    Player* getRankNext() const;
    Player* getRankPrev() const;
    int getCards() const;
    permutation_t getSpirit() const;
    void setCards(int cards);
    void setIsGoalKeeper(bool isGoalKeeper);
    void setTeam(Team* team);
//    void removeFromTeam();
    void updateNextInRank(Player* next);
    void updatePrevInRank(Player* prev);
    const Tuple getStatsTuple() const;

private:
    int playerId;
    int cards;
    int ability;
    bool goalKeeper;
    Player* prevRank;
    Player* nextRank;
    permutation_t spirit;
};

#endif // PLAYER_H_
