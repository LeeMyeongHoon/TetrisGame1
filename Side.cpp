#include "Side.h"

int operator+(int lhs, Side side)
{
	return lhs + (int)side;
}

int operator*(int lhs, Side side)
{
	return lhs * (int)side;
}