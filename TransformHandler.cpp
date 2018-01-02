#include <cassert>

#include "TetrisApp.h"

TetrisApp::TransformHandler::TransformHandler(TetrisApp& app)
	: app(app), oldShape(nullptr)
{
}

TetrisApp::TransformHandler::~TransformHandler()
{
	delete oldShape;
}

void TetrisApp::TransformHandler::Do()
{
	if (app.shape->GetType() == Shape::Type::O)
	{
		return;
	}

	oldShape = new Shape(*(app.shape));
	app.shape->Transform();

	if (IsBottomOver())
	{
		delete app.shape;

		app.shape = oldShape;	// move
		oldShape = nullptr;

		return;
	}

	bool shouldMove = false;
	for (int blockNum = 0; blockNum < Shape::BLOCK_COUNT; blockNum++)
	{
		int blockX = app.shape->GetBlockX(blockNum);
		if (blockX < 0)
		{
			shouldMove = true;
			obstacleX = blockX;
			moveDirection = Side::Right;
			break;
		}
		else if (blockX >= Stack::WIDTH)
		{
			shouldMove = true;
			obstacleX = blockX;
			moveDirection = Side::Left;
			break;
		}
		else
		{
			int blockY = app.shape->GetBlockY(blockNum);
			if (app.stack->GetData(blockX, blockY) == Blank::Block)
			{
				shouldMove = true;
				obstacleX = blockX;
				moveDirection = obstacleX < app.shape->GetLocX() ? Side::Right : Side::Left;
				break;
			}
		}
	}

	if (shouldMove)
	{
		Side obstacleSide = (Side)((-1) * moveDirection);
		app.shape->MoveSide(moveDirection);
		while (IsShapeAttachedToObstacle(obstacleSide))
		{
			bool canDrawShape = true;
			for (int blockNum = 0; blockNum < Shape::BLOCK_COUNT; blockNum++)
			{
				auto blockX = app.shape->GetBlockX(blockNum);
				auto blockY = app.shape->GetBlockY(blockNum);
				if (blockX < 0 || blockX >= Stack::WIDTH || app.stack->GetData(blockX, blockY) == Blank::Block)
				{
					canDrawShape = false;
					break;
				}
			}
			if (canDrawShape)
			{
				DrawTranformedShape();
				return;
			}
			else
			{
				app.shape->MoveSide(moveDirection);
			}
		}

		// cannot transform
		delete app.shape;
		app.shape = oldShape; // move
		oldShape = nullptr;
	}

	else // if ( !shouldMove ) 
	{
		DrawTranformedShape();
	}
}


void TetrisApp::TransformHandler::DrawTranformedShape()
{
	oldShape->Erase();
	app.expectedShape->Erase();

	app.SetExpectedShape();
	app.DrawExpectedShape();
	app.shape->Draw();

	delete oldShape;
	oldShape = nullptr;
}

bool TetrisApp::TransformHandler::IsBottomOver() const
{
	int oldShapeBottom = oldShape->GetLowestBlockY();
	for (int blockNum = 0; blockNum < Shape::BLOCK_COUNT; blockNum++)
	{
		int blockX = app.shape->GetBlockX(blockNum);
		int blockY = app.shape->GetBlockY(blockNum);
		if (blockY < 0 || (blockX >= 0 && blockX < Stack::WIDTH && app.stack->GetData(blockX, blockY) == Blank::Block && blockY < oldShapeBottom))
		{
			return true;
		}
	}
	return false;
}

bool TetrisApp::TransformHandler::IsShapeAttachedToObstacle(Side side) const
{
	for (int blockNum = 0; blockNum < Shape::BLOCK_COUNT; blockNum++)
	{
		int blockX = app.shape->GetBlockX(blockNum);
		if (blockX + side == obstacleX)
		{
			return true;
		}
	}
	return false;
}