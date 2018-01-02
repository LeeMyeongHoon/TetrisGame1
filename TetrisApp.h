#pragma once
#include "Stack.h"

class Shape;
namespace std
{
	class mutex;
}

class TetrisApp final
{
public:

private:
	enum class Menu
	{
		GameStart, End, Count
	};

	enum class Key
	{
		NotCharKey = 224,
		Enter = 13,
		Up = 72,
		Down = 80,
		Left = 75,
		Right = 77,
		Space = 32
	};

	enum class CheckForTransform_ret
	{
		RightOver, LeftOver, CannotTransform, CanTransform
	};

	class TransformHandler final
	{
	public:
		TransformHandler() = delete;
		TransformHandler(TetrisApp& app);
		TransformHandler(const TransformHandler& other) = delete; // shallow_copy 방지
		~TransformHandler();

		void Do();

	private:
		int obstacleX;
		Side moveDirection;
		Shape* oldShape;
		TetrisApp& app;

		void DrawTranformedShape();

		bool IsBottomOver() const;
		bool IsShapeAttachedToObstacle(Side side) const;
	};

	static const int NEXT_SHAPE_X = Stack::WIDTH + 3;
	static const int NEXT_SHAPE_Y = Stack::VALID_HEIGHT - 2;

	static void EraseNextShape();
	static void DrawBreakRows(const int rows[], int breakRowCount);
	static void HideCursor();
	static void DrawWall();
	static void DrawWallBlock();

	static Key GetInputKey();
	static Menu GetInputMenu();

public:
	TetrisApp() = default;
	~TetrisApp();

	TetrisApp(const TetrisApp& other) = delete;	// shallow copy 방지(혹시몰라...)

	void Run();

private:
	bool isGameOver;

	Stack* stack;
	Shape* shape;
	Shape* expectedShape;
	std::mutex* mtx;


	void HandleTransformShape();
	void HandleInputKey();
	void HandleDownKey();
	void HandleSpaceKey();
	void HandleSideKey(Side side);
	void HandlePushShape();

	void DrawNextShape() const;
	void SetExpectedShape();
	void DrawExpectedShape() const;

	bool CanMoveDownShape() const;
	bool CanMoveDownShape(const Shape& shape) const;
	bool CanMoveSideShape(Side sideOffset) const;
};