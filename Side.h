#pragma once

enum class Side
{
	RIGHT = +1, LEFT = -1
};

int operator+(int lhs, Side side);
int operator*(int lhs, Side side);