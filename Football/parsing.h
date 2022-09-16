#pragma once
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>
#include "Product.h"

namespace parsing
{
	Member_Types get_type(const std::string& str);
	std::vector<std::string> get_vector_of_string(std::istream &stream);
}


