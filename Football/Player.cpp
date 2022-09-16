#include "Player.h"
#include "FootballDataBase.h"
#include "Product.h"

//Player::Player(int id, const std::string& name, int team_id) : id(id), name(name), team_id((team_id)) {
//	data_base->add_member(*this);
//}

Player::Player(int id, const std::string& name, int team_id) : Product(id, name), team_id(team_id) {
	Product::data_base->add_member(*this);
}

void Player::print_data(std::ostream & ostream) const{
	ostream << "Player\t";
	ostream << id << '\t' << name << '\t';
	ostream << team_id << std::endl;
}

Member_Types Player::get_type() const {
	return Member_Types::PLAYER;
}

//int Player::get_id() const {
//	return id;
//}
//bool Player::operator==(const Player & another) const {
//	return another.get_id() == get_id() && another.get_name() == get_name() && another.team_id == team_id;   
//}
