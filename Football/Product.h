#pragma once
#include <iostream>
#include <utility>
#include <memory>

class FootballDataBase;

enum class Member_Types {
	TEAM,
	PLAYER,
	MATCH
};

class Product {
public:
	Product(int id, const std::string & name) : id(id), name(name) {}
	virtual ~Product() = default;
	
	virtual void print_data(std::ostream& ostream) const = 0;
	virtual Member_Types get_type() const = 0;
	
	const std::string& get_name() const { return name; }
	int get_id() const { return id; }
protected:
	std::string name;
	int id;
	static std::shared_ptr<FootballDataBase> data_base;	
};