#include "TeamCreator.h"
#include "parsing.h"
#include "Team.h"

std::shared_ptr<Product> Team_Creator::create_product(std::istream& stream) {
	const auto data = parsing::get_vector_of_string(stream);
	const int id = std::stoi(data[size_t(team_string_struct::ID)]);
	const std::string name = data[size_t(team_string_struct::NAME)];
	std::vector<int> players_id;
	for (int i = (int)team_string_struct::START_PLAYERS_ID; i != data.size(); i++) {
			players_id.push_back(stoi(data[i]));
		}
	return std::make_shared<Team>(id, name, players_id);
}
