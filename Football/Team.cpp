#include "Team.h"

Team::Team(int id, const std::string& name, std::vector<int> players):Product(id, name), players_id(std::move(players)) {
	
}

void Team::print_data(std::ostream & ostream) const {
	ostream << "Team\t";
	ostream <<id << '\t' << name;
	for(auto& i : players_id) {		
		ostream << '\t' << i;
	}
	ostream << std::endl;
}

bool Team::operator==(const Team & another) const {
	return another.get_id() == get_id() && another.get_name() == get_name() && another.players_id == players_id;
}
