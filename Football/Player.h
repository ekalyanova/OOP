#pragma once
#include "Product.h"

class Player final: public Product{
	int team_id;
public:
	Player(int id, const std::string& name, int team_id);
	~Player() = default;
	
	Member_Types get_type() const override;
	void print_data(std::ostream& ostream) const override;
};
