#pragma once

#include <cstdint>
#include <memory>
#include <string>


namespace wboard
{

enum class ShapeType
{
	Line,
	Circle,
	Rect,
	Text
};
	
struct Color
{
	uint16_t	B{ 0 };
	uint16_t	G{ 0 };
	uint16_t	R{ 0 };
};

struct Point
{
	int		X{ 0 };
	int		Y{ 0 };
};
	
struct ShapeBase
{
	ShapeType	Type;
	Color		ShapeColor;

	Point		P1;
	Point		P2;

	int			Thickness { 2 };
};

struct Circle : ShapeBase
{
	Circle()
	{
		Type = ShapeType::Circle;
	}
};
	
struct Line : ShapeBase
{
	Line()
	{
		Type = ShapeType::Line;
	}
};

struct Rect : ShapeBase
{
	Rect()
	{
		Type = ShapeType::Rect;
	}
};

using Data = std::unique_ptr<uint8_t>;
constexpr size_t MAX_PCG_SIZE{ 512 };
	
struct Package final
{
	size_t	Emount;
	uint8_t	RowData[MAX_PCG_SIZE];
};

using Shape = std::shared_ptr<ShapeBase>;
	
}
