#pragma once
#include <string>
#include <map>
#include <memory>
#include "Product.h"
#include "Player.h"
#include "Team.h"

//class Product;

class FootballDataBase final { 
public:
	FootballDataBase() = default;
	~FootballDataBase() = default;
	void add_member(Product& member);
	void delete_member(const Product& member);
	std::shared_ptr<Product> find_object(int id, Member_Types type);
private:
	std::map<int, Player> players;
	std::map<int, Team> teams;
};

