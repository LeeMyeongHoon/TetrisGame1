#pragma once
#include "Stack.h"

class Shape;

class TetrisApp final
{
public:

private:
	enum class Menu
	{
		GAME_START, END, COUNT
	};

	enum class Key
	{
		NOT_CHAR_KEY = 224,
		ENTER = 13,
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		SPACE = 32
	};

	enum CheckForTransform_ret
	{
		RIGHT_OVER, LEFT_OVER, CANNOT_TRANSFORM, CAN_TRANFORM
	};

	class TransformHandler
	{
	public:
		TransformHandler() = delete;
		TransformHandler(TetrisApp& app);
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