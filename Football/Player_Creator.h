#pragma once
#include "Creator.h"

class Player_Creator final : public Creator {
	enum class player_string_sruct {
		ID,
		NAME,
		TEAM_ID
	};
public:
	Player_Creator() = default;
	virtual ~Player_Creator() = default;
	std::shared_ptr<Product> create_product(std::istream &stream) override;
};

