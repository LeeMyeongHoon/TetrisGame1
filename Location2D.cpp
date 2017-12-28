#include <Windows.h>
#include <cstdio>

#include "Location2D.h"

Location2D::Location2D(const int x, const int y)
	: x(x), y(y)
{
}


bool Location2D::operator==(const Location2D& other) const
{
	return x == other.x && y == other.y;
}


bool Location2D::operator!=(const Location2D& other) const
{
	return !(this->operator==(other));
}