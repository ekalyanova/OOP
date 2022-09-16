#pragma once
#include "Creator.h"

class Team_Creator final : public Creator {
	enum class team_string_struct {
		ID,
		NAME,
		START_PLAYERS_ID
	};
public:
	Team_Creator() = default;
	virtual ~Team_Creator() = default;
	std::shared_ptr<Product> create_product(std::istream &stream) override;
};