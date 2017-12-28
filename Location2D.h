#pragma once

#include "Side.h"

struct Location2D final
{
	int x;
	int y;

	Location2D() = default;

	Location2D(const int x, const int y);
	
	bool operator==(const Location2D& other) const;
	bool operator!=(const Location2D& other) const;

};