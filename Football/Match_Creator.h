#pragma once
#include "Creator.h"

class Match_Creator final : public Creator {
	enum class match_string_struct {
		ID,
		NAME,
		TEAM1_ID,
		TEAM2_ID,
		DATE,
		LOCATION
	};
public:
	Match_Creator() = default;
	virtual ~Match_Creator() = default;
	std::shared_ptr<Product> create_product(std::istream &stream) override;
};