#include "FootballDataBase.h"
#include "Player.h"
#include "Team.h"

void FootballDataBase::add_member(Product& member) {
	const Member_Types type = member.get_type();
	if (type == Member_Types::PLAYER) {
		const auto ptr = dynamic_cast<Player*>(&member);
		players.emplace(member.get_id(), *ptr);
		return;
	}
	if (type == Member_Types::TEAM) {
		const auto ptr = dynamic_cast<Team*>(&member);
		teams.emplace(member.get_id(), *ptr);
	}	
}
//void FootballDataBase::add_member(std::shared_ptr<Product> member) {
//	const Member_Types type = member->get_type();
//	//std::shared_ptr<Product> tmp_ptr = std::shared_ptr<Product>(&member);
//	std::weak_ptr<Product> ptr = member;
//	switch (type) {
//	case Member_Types::PLAYER:
//		//players.insert(std::make_pair(member.get_id(), dynamic_cast<Player*>(&member)));
//		players.emplace(member->get_id(), ptr);
//		//players.emplace(member.get_id(), (member));
//		//players.emplace(member.get_id(), std::shared_ptr<Product>(&member));
//		return;
//		/*case Member_Types::TEAM:
//			teams.emplace(member.get_id(), std::shared_ptr<Product>(&member));
//			break;*/
//			/*case Member_Types::MATCH:
//				matches.emplace(member.get_id(), member);
//				break;*/
//	}
//}

void FootballDataBase::delete_member(const Product& member) {
	const Member_Types type = member.get_type();
	if(type == Member_Types::PLAYER) {
		players.erase(member.get_id());
		return;
	}
	teams.erase(member.get_id());
}

std::shared_ptr<Product> FootballDataBase::find_object(int id, Member_Types type) {
	if (type == Member_Types::PLAYER) {
		return std::shared_ptr<Product>(&(*players.find(id)).second);
	}
	if (type == Member_Types::TEAM) {
		return std::shared_ptr<Product>(&(*teams.find(id)).second);
	}
	return nullptr;
}

