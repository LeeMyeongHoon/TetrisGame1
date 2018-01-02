#pragma once

enum class Side
{
	Right = +1, Left = -1
};

int operator+(int lhs, Side side);
int operator*(int lhs, Side side);