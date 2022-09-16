#include "Match.h"

 Match::Match(int id, const std::string& name, int team1, int team2, std::string date, std::string location) :
Product(id, name), team1_id(team1), team2_id(team2), date(std::move(date)), location(std::move(location)){}
 

void Match::print_data(std::ostream & ostream) const{
	ostream << "Match\t";
	ostream << id << '\t' << name << '\t' << team1_id << '\t' << team2_id << '\t';
 	ostream << date << '\t' << location << std::endl;
}
