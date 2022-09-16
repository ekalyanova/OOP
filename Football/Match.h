#pragma once
#include <string>
#include <vector>
#include "Product.h"

class Match final : public Product {
	std::string date;
	std::string location;
	int team1_id, team2_id;
public:
	Match(int id, const std::string& name, int team1, int team2, std::string date,
		std::string location);
	virtual ~Match() = default;
	void print_data(std::ostream& ostream) const override;
	Member_Types get_type() const override { return Member_Types::MATCH; }
};
