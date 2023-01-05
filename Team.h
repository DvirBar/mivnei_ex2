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
class Player;

class Team {
public:
    Team(int teamId, int points);
    Team(const Team &team);
    ~Team() = default;

    void addPoints(int pointsToAdd);
    void addGame();
    void setCards(int cards);
    void setGoals(int goals);
    int getNumPlayers() const;
    void updateTopScorer(Player* player);
    int getNumGoalKeepers() const;
    bool isValidTeam() const;
    int getTotalGoals() const;
    int getTotalCards() const;
    int getTotalPoints() const;
    int getTotalGamesPlayed() const;
    int getId() const;
    UnionFind::PlayerNode* getHead();
    const AVLTree<Tuple, Player*>& getStatsTree() const;
    StatusType get_all_players(int* const output);
    void addPlayer(Player* player);
    void removePlayer(int playerId);

    void createStatsArray(Pair<Tuple, Player*>* arr);
    void createIdsArray(Pair<int, Player*>* arr);

    // TODO: implement
    void fillStatsFromArray(Pair<Tuple, Player*>* arr, int size);
    void fillIdsFromArray(Pair<int, Player*>* arr, int size);
    Team* getNextValidRank() const;
    Team* getPrevValidRank() const;
    int getTeamId() const;
    int getTotalStats() const;

    Player* getTopScorer() const;
    void setTopScorer(Player* newTopScorer);
    void setNextValidRank(Team* next);
    void setPrevValidRank(Team* prev);
    void setGamesPlayed(int games);
    void setGoalGoalKeepers(int numGoalkeeper);
    void setHead(UnionFind::PlayerNode* newHead);
    void incrementNumPlayers();
    Player* findPlayerById(int playerId);
    bool isEmpty();
    static Team* unite_teams(Team* team1, Team* team2, int newTeamId);
    // TODO: implement
    static void mergeArrays(Player** newArr, int newArrSize, Player** arr1,
                            int arr1Size, Player** arr2, int arr2Size);
    Player* findPrev(Player *player);

    class TeamNotFound: public exception{};
private:
    int teamId;
    int totalPoints;
    int totalCards;
    int totalGoals;
    int numGoalkeepers;
    int numPlayers;
    Player* teamTopScorer;
    Team* nextValidRank;
    Team* prevValidRank;
    int totalGamesPlayed;
    AVLTree<int, Player*> teamPlayersByID;
    AVLTree<Tuple, Player*> teamPlayersByStats;
    UnionFind::PlayerNode* head;


    void uniteTopScorers(Team* team1, Team* team2);
};

#endif // TEAM_H_
