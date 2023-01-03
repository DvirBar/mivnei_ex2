#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
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
        team->getHead()->changeSet(nullptr);
        teams.remove(teamId);
        delete team;
        return StatusType::SUCCESS;
    } catch(const KeyNotFound& error) {
        return StatusType::FAILURE;
    } catch(const bad_alloc& error) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	if(teamId1 == teamId2 || teamId1 <= 0 || teamId2 <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);
    Team* team1;
    Team* team2;
    try {
        team1 = teams.search(teamId1);
        team2 = teams.search(teamId2);
    }

    catch(const KeyNotFound& keyNotFound) {
        return output_t<int>(StatusType::FAILURE);
    }

    catch(const bad_alloc& badAlloc) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }

    if(team1->getNumGoalKeepers() == 0 || team2->getNumGoalKeepers() == 0)
        return  StatusType::FAILURE;

    int team1Ability = team1->getTotalTeamAbility();
    int team2Ability = team2->getTotalTeamAbility();
    int team1SpiritStrength = team1->getSpiritStrength();
    int team2SpiritStrength = team2->getSpiritStrength();
    UnionFind<Team*, Player*>::Node* team1Head = team1->getHead();
    UnionFind<Team*, Player*>::Node* team2Head = team2->getHead();
    team1->addGame();
    team1Head->incrementNumData();
    team2->addGame();
    team2Head->incrementNumData();

    if(team1Ability > team2Ability) {
        team1->addPoints(WINNER_PTS);
        return output_t<int>(FIRST_BY_ABILITY);
    }

    if(team1Ability < team2Ability) {
        team2->addPoints(WINNER_PTS);
        return output_t<int>(SECOND_BY_ABILITY);
    }

    if(team1Ability == team2Ability) {
        if(team1SpiritStrength > team2SpiritStrength) {
            team1->addPoints(WINNER_PTS);
            return output_t<int>(FIRST_BY_SPIRIT);
        }

        if(team1SpiritStrength < team2SpiritStrength) {
            team2->addPoints(WINNER_PTS);
            return output_t<int>(SECOND_BY_SPIRIT);
        }
    }

    team1->addPoints(TIE_PTS);
    team2->addPoints(TIE_PTS);
    return output_t<int>(TIE);
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId) {
    if(playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        UnionFind<Team*, Player*>::Node* playerNode = players.getNode(playerId);
        int games = 0;

        while(playerNode->getParent() != nullptr) {
            games += playerNode->getNumData();
            playerNode = playerNode->getParent();
        }

        return games;
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
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    try {
        Player* checkPlayer = players.get(playerId);
        return output_t<int>(checkPlayer->getCards());
    }

    catch (const KeyNotFound& keyNotFound) {
        return output_t<int>(StatusType::FAILURE);
    }

    catch (const bad_alloc& badAlloc) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    try {
        Team* team = teams.search(teamId);
        return output_t<int>(team->getTotalPoints());
    }

    catch(const KeyNotFound& error) {
        return output_t<int>(StatusType::FAILURE);
    }

    catch(const bad_alloc& error) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	if(i < 0 || i > teams.getNumNodes()) {
        return output_t<int>(StatusType::FAILURE);
    }

    try {
        return output_t<int>(teamsByAbility.Select(i)->getId());
    }

    catch (KeyNotFound& keyNotFound) {
        return output_t<int>(StatusType::FAILURE);
    }

    catch (bad_alloc& badAlloc) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	if(teamId1 == teamId2 || teamId1 <= 0 || teamId2 <= 0)
        return StatusType::INVALID_INPUT;

    try {
        Team* checkTeam1 = teams.search(teamId1);
        Team* checkTeam2 = teams.search(teamId2);
    }

    catch(KeyNotFound& keyNotFound) {
        return StatusType::FAILURE;
    }

    catch(bad_alloc& badAlloc) {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}
