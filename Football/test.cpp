#include "pch.h"
#include "gtest-memleak.h"
#include "../football/Fabrica.h"
#include "../football/Match.h"
#include "../football/Player.h"
#include "../football/Product.h"
#include "../football/Team.h"
#include <sstream>
//игрок который есть в команде,но нет в базе
TEST(PrintPlayer, AvarageValues) {
	std::string s = "player 1 jk 1\n";	
	std::istringstream is(s);
	Fabrica c;
	auto prod = c.create_product(is);
	(*prod).print_data(std::cout);
	std::ostringstream os;
	(*prod).print_data(os);
	std::string str = "Player\t1\tjk\t1\n";
	ASSERT_EQ(str, os.str());
}
TEST(PrintPlayer, EmptyValues) {
	std::string s = "";
	std::istringstream is(s);
	Fabrica c;
	auto prod = c.create_product(is);
	ASSERT_EQ(prod.get(), nullptr);
}
TEST(PrintTeam, AvarageValues) {
	/*std::string s = "player 1 jk team1\nteam team1 jk";*/
	std::string s = "team 1 team 1 1 2\n";
	std::istringstream is(s);
	Fabrica c;
	auto prod = c.create_product(is);
	(*prod).print_data(std::cout);
	std::ostringstream os;
	(*prod).print_data(os);
	std::string str = "Team\t1\tteam\t1\t1\t2\n";
	ASSERT_EQ(str, os.str());
}
TEST(PrintMatch, AvarageValues) {
	/*std::string s = "player 1 jk team1\nteam team1 jk";*/
	std::string s = "match 1 ma 1 2 12.03.10 asd\n";
	std::istringstream is(s);
	Fabrica c;
	auto prod = c.create_product(is);
	(*prod).print_data(std::cout);
	std::ostringstream os;
	(*prod).print_data(os);
	std::string str = "Match\t1\tma\t1\t2\t12.03.10\tasd\n";
	ASSERT_EQ(str, os.str());
}

