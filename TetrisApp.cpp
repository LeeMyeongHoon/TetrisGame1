#include <cstdio>
#include <conio.h>
#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>
#include <cassert>
#include <Windows.h>

#include "TetrisApp.h"
#include "Shape.h"
#include "GoToXY.h"

TetrisApp::~TetrisApp()
{
	delete expectedShape;
	delete shape;
	delete stack;
	delete mtx;
}


void TetrisApp::Run()
{
	_wsetlocale(LC_ALL, L"korean");
	HideCursor();

	Menu menu;
	while ((menu = GetInputMenu()) != Menu::End)
	{
		switch (menu)
		{
		case Menu::GameStart:
		{
			stack = new Stack;
			shape = new Shape;
			expectedShape = new Shape;
			mtx = new std::mutex;

			isGameOver = false;

			system("cls");
			DrawWall();
			DrawNextShape();

			SetExpectedShape();
			DrawExpectedShape();
			shape->Draw();

			std::thread thrd_HandleInputKey([this]() { HandleInputKey(); });

			while (isGameOver == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(400));
				mtx->lock();
				HandleDownKey();
				mtx->unlock();
			}


			GoToXY(Stack::WIDTH + 2, Stack::VALID_HEIGHT / 2);
			puts("Game Over.    ");

			thrd_HandleInputKey.join();

			delete stack;
			stack = nullptr;

			delete shape;
			shape = nullptr;

			delete expectedShape;
			expectedShape = nullptr;

			system("PAUSE");

			break;
		}

		default:
			std::cout << "�߸��� �Է�" << std::endl;
			system("PAUSE");
			break;
		}
	}
}

void TetrisApp::HandleTransformShape()
{
	TransformHandler handler(*this);
	handler.Do();
}


bool TetrisApp::CanMoveSideShape(Side sideOffset) const
{
	for (int blockNum = 0; blockNum < Shape::BLOCK_COUNT; blockNum++)
	{
		auto blockX = shape->GetBlockX(blockNum);
		auto blockY = shape->GetBlockY(blockNum);

		int nextBlockX = blockX + sideOffset;
		int nextBlockY = blockY;
		if (nextBlockX < 0 || nextBlockX >= Stack::WIDTH || stack->GetData(nextBlockX, nextBlockY) == Blank::Block)
		{
			return false;
		}
	}
	return true;
}


bool TetrisApp::CanMoveDownShape() const
{
	return CanMoveDownShape(*shape);
}

bool TetrisApp::CanMoveDownShape(const Shape& shape) const
{
	for (int blockNum = 0; blockNum < Shape::BLOCK_COUNT; blockNum++)
	{
		auto[blockX, blockY] = shape.GetBlockXY(blockNum);

		int nextBlockX = blockX;
		int nextBlockY = blockY - 1;
		if (nextBlockY < 0 || stack->GetData(nextBlockX, nextBlockY) == Blank::Block)
		{
			return false;
		}
	}
	return true;
}


void TetrisApp::HandleInputKey()
{
	while (isGameOver == false)
	{
		if (_kbhit())
		{
			mtx->lock();

			switch (GetInputKey())
			{
			case Key::Up:
			{
				HandleTransformShape();
				break;
			}

			case Key::Down:
			{
				HandleDownKey();
				break;
			}

			case Key::Left:
			{
				HandleSideKey(Side::Left);
				break;
			}
			case Key::Right:
			{
				HandleSideKey(Side::Right);
				break;
			}
			case Key::Space:
			{
				HandleSpaceKey();
				break;
			}
			default:
			{
				break;
			}
			}

			mtx->unlock();
		}
	}
}


void TetrisApp::HandleDownKey()
{
	if (CanMoveDownShape())
	{
		shape->Erase();
		shape->MoveDown();
		shape->Draw();
	}
	else // �Ʒ��� ���������� ���(���ÿ� �׾����� ���)
	{
		HandlePushShape();
	}

}


void TetrisApp::HandleSpaceKey()
{
	shape->Erase();
	HandlePushShape();
}


void TetrisApp::HandleSideKey(Side side)
{
	if (CanMoveSideShape(side))
	{
		shape->Erase();
		expectedShape->Erase();
		shape->MoveSide(side);

		SetExpectedShape();
		DrawExpectedShape();

		shape->Draw();
	}
}


// �˰���,���� �߿�
void TetrisApp::HandlePushShape()
{
	stack->PushShape(*expectedShape);
	expectedShape->DrawChangedStack();

	//  shape�� ���κп����� breakRow�� �߻��ǹǷ�
	int maxShapeBlockY = expectedShape->GetLocY() + Shape::MAX_BLOCK_UP_OFFSET;
	int minShapeBlockY = expectedShape->GetLocY() - Shape::MAX_BLOCK_DOWN_OFFSET;
	if (minShapeBlockY < 0)
	{
		minShapeBlockY = 0;
	}

	// FullRow�� �����ϴ��� Ȯ��
	int y;
	if ((y = stack->FindFullRow(minShapeBlockY, maxShapeBlockY)) != -1)
	{
		int oldHighestY = stack->GetHighestY();
		stack->BreakRow(y);
		maxShapeBlockY--;

		int brokenRows[Shape::BLOCK_COUNT];
		brokenRows[0] = y;

		int brokenRowCount = 1;

		// FullRow���ã��
		while ((y = stack->FindFullRow(y, maxShapeBlockY)) != -1)
		{
			stack->BreakRow(y);
			brokenRows[brokenRowCount++] = y + brokenRowCount; // �˰��� stack.BreakRow(y); �ڵ�� ���� offset �ٽ� ����ؾ���.
			maxShapeBlockY--;
		}

		DrawBreakRows(brokenRows, brokenRowCount);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));

		stack->Erase(brokenRows[0], oldHighestY);
		stack->Draw(brokenRows[0]);
	}


	EraseNextShape();
	if (stack->IsFull())
	{
		isGameOver = true;
		return;
	}
	DrawNextShape();

	shape->Reset();
	shape->Draw();

	SetExpectedShape();
	DrawExpectedShape();
}


void TetrisApp::DrawNextShape() const
{
	Shape(shape->GetNextType(), shape->GetNextForm(), NEXT_SHAPE_X, NEXT_SHAPE_Y).Draw();
}


void TetrisApp::SetExpectedShape()
{
	*expectedShape = *shape;
	while (CanMoveDownShape(*expectedShape))
	{
		expectedShape->MoveDown();
	}
}


void TetrisApp::DrawExpectedShape() const
{
	expectedShape->Draw(L'��');
}

TetrisApp::Key TetrisApp::GetInputKey()
{
	int inputKey = _getch();
	if (inputKey == (int)(Key::NotCharKey))
	{
		inputKey = _getch();
	}
	return (Key)inputKey;
}


TetrisApp::Menu TetrisApp::GetInputMenu()
{
	static const char* MENU_STRINGS[(int)Menu::Count] = { "���� ����","���� ����" };

	system("cls");
	std::cout << "**��Ʈ���� ����**" << '\n';
	for (int menuNum = 0; menuNum < (int)Menu::Count; menuNum++)
	{
		std::cout << '[' << menuNum << "] " << MENU_STRINGS[menuNum] << "\n";
	}
	std::cout << "���� : ";

	Menu menu;
	std::cin >> (int&)menu;

	if (std::cin.fail())
	{
		std::cerr << "Error : Invalid menu input\n";
		exit(0);
	}

	return menu;
}

//
void TetrisApp::EraseNextShape()
{
	for (int y = NEXT_SHAPE_Y - Shape::MAX_BLOCK_DOWN_OFFSET; y <= NEXT_SHAPE_Y + Shape::MAX_BLOCK_UP_OFFSET; y++)
	{
		GoToXY(NEXT_SHAPE_X - 2, y);
		printf("          ");
	}
}


void TetrisApp::DrawBreakRows(const int breakRows[], int breakRowCount)
{
	static const std::wstring BROKEN_ROW_STRING(Stack::WIDTH, L'��');

	for (int blockNum = 0; blockNum < breakRowCount; blockNum++)
	{
		GoToXY(0, breakRows[blockNum]);
		wprintf(L"%s", BROKEN_ROW_STRING.data());
	}
}


void TetrisApp::HideCursor()
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void TetrisApp::DrawWall()
{
	for (int y = 0; y < Stack::VALID_HEIGHT; y++)
	{
		//���� �� ���
		GoToXY(-1, y);
		DrawWallBlock();

		//������ �� ���
		GoToXY(Stack::WIDTH, y);
		DrawWallBlock();
	}

	//�ٴ� ���
	for (int x = -1; x <= Stack::WIDTH; x++)
	{
		GoToXY(x, -1);
		DrawWallBlock();
	}
}


void TetrisApp::DrawWallBlock()
{
	putwchar(L'��');
}
