#pragma once
#include <string>
#include <vector>
#include "Product.h"
#include   <memory>

class Team final : public Product{
	std::vector<int> players_id;
public:
	Team(int id, const std::string& name, std::vector<int>);
	~Team() = default;
	void print_data(std::ostream& ostream) const override;
	bool operator==(const Team& another) const;
	Member_Types get_type() const override { return Member_Types::TEAM; }
};