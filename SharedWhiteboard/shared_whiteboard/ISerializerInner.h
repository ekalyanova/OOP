#pragma once
#include "ShapeData.h"

namespace wboard
{

class ISerializerInner
{
public:

	ISerializerInner() = default;
	virtual ~ISerializerInner() = default;

	virtual Package	Serialize(const Shape& shape) const = 0;
	virtual Shape	Deserialize(const Package& pcg) const = 0;
};

using SerializerInner = std::unique_ptr<ISerializerInner>;
	
}

