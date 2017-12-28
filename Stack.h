#pragma once

#include <array>

#include "Shape.h"
#include "Blank.h"

class Stack final
{
public:
	static const int VALID_HEIGHT = 20;
	static const int WIDTH = 10;
	static const int OVER_HEIGHT = VALID_HEIGHT + MAX_BLOCK_UP_OFFSET + 3;

	static void DrawStackBlock();

private:
	using Data = std::array<std::array<Blank, OVER_HEIGHT>, WIDTH>;

public:
	Stack();
	~Stack() = default;

	void Reset();
	void BreakRow(const int y);
	void Draw(const int beginY) const;
	void Erase(const int beginY, const int lastY) const;
	void PushShape(const Shape& shape);

	bool IsFull() const;
	bool IsFullLow(const int y) const;

	int GetHighestY() const;
	int FindFullRow(const int beginY, const int lastY) const;

	Blank GetData(const int x, const int y) const;

private:
	int highestBlockY;
	Data data;
};