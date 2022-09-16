#pragma once
#include  <map>
#include "Creator.h"

class Fabrica final{
	static std::map<Member_Types, std::unique_ptr<Creator>> creators;
	static void init_map_creators();
public:
	Fabrica();
	~Fabrica() = default;
	std::shared_ptr<Product> create_product(std::istream &stream);
};