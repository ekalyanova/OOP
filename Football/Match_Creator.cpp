#include "Match_Creator.h"
#include "parsing.h"
#include "Match.h"

std::shared_ptr<Product> Match_Creator::create_product(std::istream& stream) {
	const auto data = parsing::get_vector_of_string(stream);
	const int id = stoi(data[size_t(match_string_struct::ID)]);
	const std::string name = data[size_t(match_string_struct::NAME)];
	const int team1_id = stoi(data[size_t(match_string_struct::TEAM1_ID)]);
	const int team2_id = stoi(data[size_t(match_string_struct::TEAM2_ID)]);
	const std::string date = data[size_t(match_string_struct::DATE)];
	const std::string location = data[size_t(match_string_struct::LOCATION)];
	return std::make_shared<Match>(id, name, team1_id, team2_id, date, location);
}

