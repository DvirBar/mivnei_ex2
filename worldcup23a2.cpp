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
        team->getHead()->setTeam(nullptr);
        teams.remove(teamId);
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
    auto player = new Player(playerId, spirit, ability, gamesPlayed, cards,
                                goalKeeper);
    Team* team = teams.search(teamId);
    players.insert(playerId, player, teamId, team, gamesPlayed);
    team->incrementNumPlayers();
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
        UnionFind::PlayerNode* playerNode = players.getNode(playerId);
        int games = 0;

        while(playerNode != nullptr) {
            games += playerNode->getGames();
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
	// TODO: Your code goes here
	return 12345;
}

permutation_t world_cup_t::getPartialSpiritAux(int playerId) {
    UnionFind::PlayerNode* playerNode = players.getNode(playerId);
    permutation_t result = permutation_t::neutral();
    while(playerNode != nullptr) {
        result = playerNode->getExtractSpirit()*result;
        playerNode = playerNode->getParent();
    }

    return result;
}

bool world_cup_t::isActive(int playerId) {
    UnionFind::PlayerNode* playerNode = players.getNode(playerId);
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
        return getPartialSpiritAux(playerId);
    } catch (const bad_alloc& error) {
        return  StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
