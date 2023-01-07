#include "worldcup23a2.h"
#include <iostream>

const int world_cup_t::WINNER_PTS = 3;
const int world_cup_t::TIE_PTS = 1;
const int world_cup_t::TIE = 0;
const int world_cup_t::FIRST_BY_ABILITY = 1;
const int world_cup_t::FIRST_BY_SPIRIT = 2;
const int world_cup_t::SECOND_BY_ABILITY = 3;
const int world_cup_t::SECOND_BY_SPIRIT = 4;


world_cup_t::world_cup_t():
    teams(),
    teamsByAbility(),
    players()
{ }

world_cup_t::~world_cup_t()
{
	auto teamsArray = new Pair<int, Team*>[teams.getNumNodes()];
    for(int i = 0; i < teams.getNumNodes(); i++) {
        delete teamsArray[i].getValue();
    }

    delete[] teamsArray;
}

StatusType world_cup_t::add_team(int teamId)
{
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;

    if(teams.isExist(teamId))
        return StatusType::FAILURE;

    try {
        Team* newTeam = new Team(teamId);
        teams.insert(teamId, newTeam);
        teamsByAbility.insert(Pair<int,int>(0, teamId), newTeam);
    }
    catch (const bad_alloc& badAlloc) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Team* team = teams.search(teamId);
        if(team->getNumPlayers() > 0) {
            team->getHead()->setTeam(nullptr);
        }

        teams.remove(teamId);
        teamsByAbility.remove(Pair<int, int>(team->getTeamAbility(), teamId));
        delete team;
        return StatusType::SUCCESS;
    } catch(const KeyNotFound& error) {
        return StatusType::FAILURE;
    } catch(const bad_alloc& error) {
        return StatusType::ALLOCATION_ERROR;
    }
}

void world_cup_t::addPlayerAux(int playerId, int teamId,
                               const permutation_t &spirit, int gamesPlayed,
                               int ability, int cards, bool goalKeeper) {
    auto player = new Player(spirit, gamesPlayed, cards, goalKeeper);
    Team* team = teams.search(teamId);

    players.insert(playerId, player, team, gamesPlayed);
    team->incrementNumPlayers();

    teamsByAbility.remove(Pair<int, int>(team->getTeamAbility(), teamId));
    team->addAbility(ability);
    teamsByAbility.insert(Pair<int, int>(team->getTeamAbility(), teamId), team);

    if(goalKeeper) {
        team->incrementNumGoalKeepers();
    }
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	if(playerId <= 0 || teamId <= 0 || !spirit.isvalid() || gamesPlayed < 0 || cards < 0) {
        return StatusType::INVALID_INPUT;
    }

    if(players.isExist(playerId) || !teams.isExist(teamId)) {
        return StatusType::FAILURE;
    }

    try {
        // TODO: we're ignoring KeyNotFound because we check it earlier
        addPlayerAux(playerId, teamId, spirit, gamesPlayed, ability, cards, goalKeeper);
        return StatusType::SUCCESS;
    } catch (const bad_alloc& error) {
        return StatusType::ALLOCATION_ERROR;
    }
}


// TODO: I think we should add an aux function
output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	if(teamId1 == teamId2 || teamId1 <= 0 || teamId2 <= 0)
        return StatusType::INVALID_INPUT;

    Team* team1;
    Team* team2;
    try {
        team1 = teams.search(teamId1);
        team2 = teams.search(teamId2);
    }

    catch(const KeyNotFound& keyNotFound) {
        return StatusType::FAILURE;
    }

    catch(const bad_alloc& badAlloc) {
        return StatusType::ALLOCATION_ERROR;
    }

    if(team1->getNumGoalKeepers() == 0 || team2->getNumGoalKeepers() == 0)
        return  StatusType::FAILURE;

    int team1Ability = team1->getTotalTeamAbility();
    int team2Ability = team2->getTotalTeamAbility();
    int team1SpiritStrength = team1->getSpiritStrength();
    int team2SpiritStrength = team2->getSpiritStrength();
    PlayerNode* team1Head = team1->getHead();
    PlayerNode* team2Head = team2->getHead();
    team1->addGame();
    team1Head->incrementGames();
    team2->addGame();
    team2Head->incrementGames();

    if(team1Ability > team2Ability) {
        team1->addPoints(WINNER_PTS);
        return FIRST_BY_ABILITY;
    }

    if(team1Ability < team2Ability) {
        team2->addPoints(WINNER_PTS);
        return SECOND_BY_ABILITY;
    }

    if(team1Ability == team2Ability) {
        if(team1SpiritStrength > team2SpiritStrength) {
            team1->addPoints(WINNER_PTS);
            return FIRST_BY_SPIRIT;
        }

        if(team1SpiritStrength < team2SpiritStrength) {
            team2->addPoints(WINNER_PTS);
            return SECOND_BY_SPIRIT;
        }
    }

    team1->addPoints(TIE_PTS);
    team2->addPoints(TIE_PTS);
    return TIE;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId) {
    if(playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        return players.findGames(playerId);
    } catch (const KeyNotFound& error) {
        return StatusType::FAILURE;
    } catch (const bad_alloc& error) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if(playerId <= 0 || cards < 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Player* checkPlayer = players.get(playerId);
        if(players.find(playerId) == nullptr) {
            return StatusType::FAILURE;
        }
        checkPlayer->addCards(cards);
    } catch (const KeyNotFound& keyNotFound) {
        return StatusType::FAILURE;
    } catch (const bad_alloc& badAlloc) {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if(playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Player* checkPlayer = players.get(playerId);
        return checkPlayer->getCards();
    }

    catch (const KeyNotFound& keyNotFound) {
        return StatusType::FAILURE;
    }

    catch (const bad_alloc& badAlloc) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Team* team = teams.search(teamId);
        return team->getTotalPoints();
    } catch(const KeyNotFound& error) {
        return StatusType::FAILURE;
    } catch(const bad_alloc& error) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	if(i < 0 || i >= teams.getNumNodes()) {
        return StatusType::FAILURE;
    }

    try {
        return teamsByAbility.Select(i + 1)->getId();
    }

    catch (KeyNotFound& keyNotFound) {
        return StatusType::FAILURE;
    }

    catch (bad_alloc& badAlloc) {
        return StatusType::ALLOCATION_ERROR;
    }
}

bool world_cup_t::isActive(int playerId) {
    PlayerNode* playerNode = players.getNode(playerId);
    while(playerNode->getParent() != nullptr) {
        playerNode = playerNode->getParent();
    }

    return playerNode->getTeam() != nullptr;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	if(playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if(!players.isExist(playerId) || !isActive(playerId)) {
        return StatusType::FAILURE;
    }

    try {
        return players.findPartialSpirit(playerId);
    } catch (const bad_alloc& error) {
        return  StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	if(teamId1 == teamId2 || teamId1 <= 0 || teamId2 <= 0)
        return StatusType::INVALID_INPUT;

    try {
        Team* buyingTeam = teams.search(teamId1);
        Team* boughtTeam = teams.search(teamId2);
        teams.remove(teamId2);

        teamsByAbility.remove(Pair<int,int>(buyingTeam->getTotalPlayerAbility(), teamId1));
        teamsByAbility.remove(Pair<int, int>(boughtTeam->getTotalPlayerAbility(), teamId2));

        buyingTeam->addPoints(boughtTeam->getTotalPoints());
        buyingTeam->addAbility(boughtTeam->getTotalPlayerAbility());
        int buyingTeamGoalKeepers = buyingTeam->getNumGoalKeepers();
        buyingTeam->setGoalKeepers(buyingTeamGoalKeepers + boughtTeam->getNumGoalKeepers());

        players.unite(buyingTeam, boughtTeam);
        teamsByAbility.insert(Pair<int, int>(buyingTeam->getTotalPlayerAbility(), teamId1), buyingTeam);

        delete boughtTeam;
    }


    catch(KeyNotFound& keyNotFound) {
        return StatusType::FAILURE;
    }

    catch(bad_alloc& badAlloc) {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}
