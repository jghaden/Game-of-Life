#include "PCH.h"

#include "Game.h"

Game::Game(unsigned width, unsigned height)
{
	this->width = width;
	this->height = height;

	Init();
}

void Game::Init()
{
	cellMap.clear();

	cellMap.resize(width, std::vector<bool>(height, CELL_DEAD));
}

void Game::Reset() { Init(); }

void Game::Random()
{
	bool state;

	for (int x = 0; x < GetWidth(); x++)
	{
		for (int y = 0; y < GetHeight(); y++)
		{
			state = static_cast<bool>(rand() % 2);

			SetState(x, y, state);
		}
	}
}

void Game::SimulationStep()
{
	int neighbors;

	Game tmp(GetWidth(), GetHeight());

	for (int x = 0; x < GetWidth(); x++)
	{
		for (int y = 0; y < GetHeight(); y++)
		{
			neighbors = GetNeighbors(x, y);

			// Rules
			if (neighbors == 2 || neighbors == 3)
				SetState(x, y, CELL_ALIVE);
			else if (neighbors == 3)
				SetState(x, y, CELL_ALIVE);
			else
				SetState(x, y, CELL_DEAD);
		}
	}

	cellMap = tmp.cellMap;
}

void Game::ShowMap()
{
	for (int x = 0; x < GetWidth(); x++)
	{
		for (int y = 0; y < GetHeight(); y++)
		{
			if (GetState(x, y))
			{
				WriteAt(x, y, 'Û');
			}
			else
			{
				WriteAt(x, y, ' ');
			}
		}

		std::cout << std::endl;
	}
}

// Getters
bool Game::GetState(unsigned int x, unsigned int y) { return cellMap[x][y]; }
unsigned int Game::GetWidth() { return width; }
unsigned int Game::GetHeight() { return height; }

unsigned int Game::GetNeighbors(unsigned int x, unsigned int y)
{
	int count = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int neighbor_x = x + i;
			int neighbor_y = y + j;

			if (i == 0 && j == 0)
			{
				// Skip current cell
			}
			// Edge of the map
			else if (neighbor_x < 0 || neighbor_y < 0 || neighbor_x >= GetWidth() || neighbor_y >= GetHeight())
			{
				count++;
			}
			// Inside of the map
			else if (GetState(neighbor_x, neighbor_y))
			{
				count++;
			}
		}
	}

	return count;
}

// Setters
void Game::SetState(unsigned int x, unsigned int y, bool state) { cellMap[x][y] = state; }