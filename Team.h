#ifndef TEAM_H_
#define TEAM_H_

#include <exception>
#include "wet2util.h"
#include "AVLTree.h"
#include "Player.h"
#include "Tuple.h"
#include "UnionFind.h"
#include "PlayerNode.h"

using namespace std;

// Forward declaration to break circular dependency
class UnionFind;
class PlayerNode;
class Player;

class Team {
public:
    explicit Team(int teamId);
    Team(const Team &team) = default;
    ~Team() = default;

    void addPoints(int pointsToAdd);
    void addGame();
    void setCards(int cards);
    void setGoals(int goals);
    int getNumGoalKeepers() const;
    int getTotalGoals() const;
    int getTotalCards() const;
    int getTotalPoints() const;
    int getTotalGamesPlayed() const;
    int getId() const;
    int getTotalPlayerAbility() const;
    int getTotalTeamAbility() const;
    int getSpiritStrength() const;
    int getNumPlayers() const;
    void addAbility(const int abilityToAdd); // Can also be a negative value
    PlayerNode* getHead();

    int getTotalStats() const;

    void setGoalKeepers(int numGoalkeeper);

    void setHead(PlayerNode* newHead);
    void addNumPlayers(int playersToAdd);
    void incrementNumPlayers();
    void incrementNumGoalKeepers();

    class TeamNotFound: public exception{};
private:
    int teamId;
    int totalPoints;
    int totalCards;
    int totalGoals;
    int totalPlayerAbility;
    int numGoalkeepers;
    int totalGamesPlayed;
    int numPlayers;
    PlayerNode* head;
};

#endif // TEAM_H_
