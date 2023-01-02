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
	// TODO: Your code goes here
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
	// TODO: Your code goes here
	return StatusType::SUCCESS;
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
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    try {
        Team* team = teams.search(teamId);
        return output_t<int>(team->getTotalPoints());
    } catch(const KeyNotFound& error) {
        return output_t<int>(StatusType::FAILURE);
    } catch(const bad_alloc& error) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
