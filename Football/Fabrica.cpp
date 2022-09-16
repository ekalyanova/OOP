#include "Fabrica.h"
#include "Player_Creator.h"
#include "parsing.h"
#include "TeamCreator.h"
#include "Match_Creator.h"

std::map<Member_Types, std::unique_ptr<Creator>> Fabrica::creators;

Fabrica::Fabrica() {
	init_map_creators();
}

void Fabrica::init_map_creators() {
	creators.emplace(Member_Types::PLAYER, std::make_unique<Player_Creator>());
	creators.emplace(Member_Types::TEAM, std::make_unique<Team_Creator>());
	creators.emplace(Member_Types::MATCH, std::make_unique<Match_Creator>());
}

std::shared_ptr<Product> Fabrica::create_product(std::istream& stream) {
	if (!stream.good()) return nullptr;
	std::string type_of_member;
	stream >> type_of_member;
	if (type_of_member.empty())
		return nullptr;
	const Member_Types type = parsing::get_type(type_of_member);
	if (creators.count(type) == 0) return nullptr;
	return creators[type]->create_product(stream);
}
