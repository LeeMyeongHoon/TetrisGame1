#include <random>
#include <cassert>
#include <limits>

#include "Shape.h"
#include "Stack.h"
#include "GoToXY.h"


const Shape::BlockOffset Shape::BLOCK_OFFSET{};


Location2D Shap	e::GetBlockXY(const int blockNum) const
{
	return Location2D(GetBlockX(blockNum), GetBlockY(blockNum));
}

int Shape::GetLowestBlockY() const
{
		int lowestBlockY = std::numeric_limits<int>::max();
		for (int blockNum = 0; blockNum < Shape::BLOCK_COUNT; blockNum++)
		{
			int blockY = GetBlockY(blockNum);
			if (blockY < lowestBlockY)
			{
				lowestBlockY = blockY;
			}
		}

		return lowestBlockY;
}


void Shape::Transform()
{
	++form;

	if (form == FORM_COUNT)
	{
		form = 0;
	}
}


void Shape::Erase() const
{
	Shape::Draw(L' ');
}


void Shape::MoveDown()
{
	locY = locY - 1;
}


void Shape::MoveLeft(const int offset)
{
	assert(offset >= 0);
	MoveSide(-offset);
}


void Shape::MoveRight(const int offset)
{
	assert(offset >= 0);
	MoveSide(offset);
}


void Shape::MoveSide(const int offset)
{
	locX = locX + offset;
}


void Shape::MoveSide(const Side offset)
{
	MoveSide((int)offset);
}


void Shape::DrawChangedStack() const
{
	for (int blockNum = 0; blockNum < BLOCK_COUNT; blockNum++)
	{
		auto blockX = GetBlockX(blockNum);
		auto blockY = GetBlockY(blockNum);
		GoToXY(blockX, blockY);
		Stack::DrawStackBlock();
	}
}


Shape::Shape()
{
	nextType = MakeRandomType();
	nextForm = MakeRandomForm();
	Reset();
}


Shape::Shape(const Type type, const Form form, const int locX, const int locY)
	: type(type), form(form), locX(locX), locY(locY)
{
}


void Shape::Draw(const wchar_t ch) const
{
	for (int blockNum = 0; blockNum < BLOCK_COUNT; blockNum++)
	{
		auto blockX = GetBlockX(blockNum);
		auto blockY = GetBlockY(blockNum);
		GoToXY(blockX, blockY);
		putwchar(ch);
	}
}


void Shape::Reset()
{
	locX = Stack::WIDTH / 2;
	locY = Stack::VALID_HEIGHT + MAX_BLOCK_DOWN_OFFSET;

	type = nextType;
	form = nextForm;

	nextType = MakeRandomType();
	nextForm = MakeRandomForm();

}


Shape::Type Shape::MakeRandomType()
{
#define TEST
	static const int TypeWeights[(int)Type::COUNT] =
#ifdef TEST
	{ 1,1,1,1,1,1,INT_MAX };
#else
	{ 2, 2, 2, 2, 4, 2, 5 };
#endif

	static std::random_device rd;
	static std::default_random_engine eng(rd());
	static std::discrete_distribution<int> MakeRandType{ std::begin(TypeWeights),std::end(TypeWeights) };

	return (Type)MakeRandType(eng);
}


int Shape::MakeRandomForm()
{
	static std::random_device rd;
	static std::default_random_engine eng(rd());
	static std::uniform_int_distribution<Form> makeRandForm(0, FORM_COUNT - 1);

	return makeRandForm(eng);
}
