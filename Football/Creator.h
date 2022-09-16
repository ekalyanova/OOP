#pragma once
#include "Product.h"
#include <memory>
#include "Product.h"
#include <vector>
#include <string>

//class Player_Creator;

class Creator {
public:
	Creator() = default;
	virtual ~Creator() = default;
	virtual std::shared_ptr<Product> create_product(std::istream &stream) = 0;
};

