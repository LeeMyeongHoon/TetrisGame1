#pragma once

#include <array>

#include "Location2D.h"
#include "Side.h"

class Shape final
{
public:
	enum class Type
	{
		S, Z, J, L, T, O, l, COUNT
	};

	static const int MAX_BLOCK_DOWN_OFFSET = 1;
	static const int MAX_BLOCK_UP_OFFSET = 2;
	static const int BLOCK_COUNT = 4;
	static const int FORM_COUNT = 4;


private:
	using Form = int;


	struct BlockOffset final
	{
	public:
		BlockOffset();
		~BlockOffset() = default;

		const auto operator[](Form form) const { return data[form]; };

	private:
		using Data = std::array<std::array<std::array<Location2D, BLOCK_COUNT>, FORM_COUNT>, (int)Type::COUNT>;

		Data data;
	};

	static const BlockOffset BLOCK_OFFSET;

	static Form MakeRandomForm();
	static Type MakeRandomType();
	
public:
	Shape();
	Shape(const Type type, const Form form, const int locX, const int locY);
	Shape(const Shape& other) = default;

	~Shape() = default;

	Shape& operator=(const Shape& other) = default;

	void Draw(const wchar_t ch = L'¢Ë') const;
	void Erase() const;
	void Reset();
	void Transform();

	void MoveDown();
	void MoveLeft(const int offset = 1);
	void MoveRight(const int offset = 1);
	void MoveSide(const int offset);
	void MoveSide(const Side offset);

	void DrawChangedStack() const;

	Form GetNextForm() const { return nextForm; }
	Form GetForm() const { return form; }
	Type GetType() const { return type; }
	Type GetNextType() const { return nextType; }
	int GetLocY() const { return locY; }
	int GetLocX() const { return locX; }

	int GetBlockX(const int blockNum) const { return locX + BLOCK_OFFSET[(int)type][form][blockNum].x; }
	int GetBlockY(const int blockNum) const { return locY + BLOCK_OFFSET[(int)type][form][blockNum].y; }
	Location2D GetBlockXY(const int blockNum) const;

	int GetLowestBlockY() const;

private:
	int locX;
	int locY;

	Form form;
	Form nextForm;

	Type type;
	Type nextType;
};
