#include "parsing.h"


Member_Types parsing::get_type(const std::string& str) {
	if (str == "team")
		return Member_Types::TEAM;
	if (str == "match")
		return Member_Types::MATCH;
	return Member_Types::PLAYER;
}

std::vector<std::string> parsing::get_vector_of_string(std::istream &stream) {
	std::string str;
	std::vector<std::string> buf;
	/*std::vector<Product*> products;
	while (getline(stream, s))
	{
		istringstream is(s);
		copy(istream_iterator<string>(is), {}, back_inserter(v));
		v.clear();
	}*/
	std::getline(stream, str);
	std::istringstream is(str);
	std::copy(std::istream_iterator<std::string>(is), {}, std::back_inserter(buf));
	return buf;
}