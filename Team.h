#ifndef TEAM_H_
#define TEAM_H_

#include <exception>
#include "wet2util.h"
#include "AVLTree.h"
#include "Player.h"
#include "Tuple.h"
#include "UnionFind.h"

using namespace std;

// Forward declaration to break circular dependancy
class UnionFind;
class Player;

class Team {
public:
    Team(int teamId);
    Team(const Team &team);
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
    UnionFind::PlayerNode* getHead();
    const AVLTree<Tuple, Player*>& getStatsTree() const;
    StatusType get_all_players(int* const output);
    void addPlayer(Player* player);
    void removePlayer(int playerId);

    int getTotalStats() const;

    void setGoalKeepers(int numGoalkeeper);

    void setHead(UnionFind::PlayerNode* newHead);
    void incrementNumPlayers();
    Player* findPlayerById(int playerId);
    bool isEmpty();

    class TeamNotFound: public exception{};
private:
    int teamId;
    int totalPoints;
    int totalCards;
    int totalGoals;
    int totalPlayerAbility;
    int numGoalkeepers;
    int totalGamesPlayed;
    permutation_t teamSpirit;
    int numPlayers;
    Player* teamTopScorer;
    Team* nextValidRank;
    Team* prevValidRank;
    UnionFind::PlayerNode* head;
};

#endif // TEAM_H_
