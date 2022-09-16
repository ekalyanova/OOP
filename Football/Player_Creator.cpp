#include "Player_Creator.h"
#include "parsing.h"
#include "Player.h"

std::shared_ptr<Product> Player_Creator::create_product(std::istream& stream) {

	const auto data = parsing::get_vector_of_string(stream);
	const int id = std::stoi(data[size_t(player_string_sruct::ID)]);
	const std::string name = data[size_t(player_string_sruct::NAME)];
	const int team_id = stoi(data[size_t(player_string_sruct::TEAM_ID)]);
	return std::make_shared<Player>(id,	name, team_id);
}

