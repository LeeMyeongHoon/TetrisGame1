#include <algorithm>
#include <cstdio>
#include <string>
#include <cassert>

#include "Stack.h"
#include "GoToXY.h"

void Stack::DrawStackBlock()
{
	putwchar(L'□');
}


Stack::Stack()
{
	Reset();
}


void Stack::Reset()
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < OVER_HEIGHT; y++)
		{
			data[x][y] = Blank::EMPTY;
		}
	}

	highestBlockY = 0;
}


bool Stack::IsFull() const
{
	return highestBlockY >= VALID_HEIGHT;
}


int Stack::FindFullRow(const int beginY, const int lastY) const
{
	int y;
	for (y = beginY; y <= lastY; y++)
	{
		if (IsFullLow(y))
		{
			return y;
		}
	}
	return -1;
}


void Stack::BreakRow(const int keyY)
{
	// 1줄씩 아래로 당긴다.
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = brokenRow; y < highestBlockY; y++)
		{
			data[x][y] = data[x][y + 1];
		}
		data[x][highestBlockY] = Blank::EMPTY;
	}
	highestBlockY--;
}


void Stack::Draw(const int beginY) const
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = beginY; y <= highestBlockY; y++)
		{
			if (data[x][y] == Blank::BLOCK)
			{
				GoToXY(x, y);
				DrawStackBlock();
			}
		}
	}
}


void Stack::Erase(const int beginY, const int lastY) const
{
	static const std::string ERASE_ROW_STRING(WIDTH * 2, ' ');

	for (int y = beginY; y <= lastY; y++)
	{
		GoToXY(0, y);
		printf("%s", ERASE_ROW_STRING.data());
	}

}


void Stack::PushShape(const Shape& shape)
{
	for (int blockNum = 0; blockNum < Shape::BLOCK_COUNT; blockNum++)
	{
		auto blockX = shape.GetBlockX(blockNum);
		auto blockY = shape.GetBlockY(blockNum);

		data[blockX][blockY] = Blank::BLOCK;

		if (blockY > highestBlockY)
		{
			highestBlockY = blockY;
		}
	}
}

Blank Stack::GetData(const int x, const int y) const
{
	return data[x][y];
}


int Stack::GetHighestY() const
{
	return highestBlockY;
}


bool Stack::IsFullLow(const int y) const
{
	for (int x = 0; x < WIDTH; x++)
	{
		if (data[x][y] == Blank::EMPTY)
		{
			return false;
		}
	}
	return true;
}