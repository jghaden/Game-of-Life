#include "PCH.h"

#include "Game.h"

Game::Game(int width, int height)
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

void Game::SetWidth(int width) { this->width = width; }
void Game::SetHeight(int height) { this->height = height; }

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

	Game tmpGame(GetWidth(), GetHeight());

	for (int x = 0; x < GetWidth(); x++)
	{
		for (int y = 0; y < GetHeight(); y++)
		{
			neighbors = GetNeighbors(x, y);

			// Rules
			if ((neighbors == 2 || neighbors == 3) && GetState(x, y))
				tmpGame.SetState(x, y, CELL_ALIVE);
			else if (neighbors == 3)
				tmpGame.SetState(x, y, CELL_ALIVE);
			else
				tmpGame.SetState(x, y, CELL_DEAD);
		}
	}

	cellMap = tmpGame.cellMap;
}

FILE_STATUS Game::LoadGame(const char* file)
{
	bool tmpState;
	int tmpWidth, tmpHeight;

	std::ifstream inFile;
	inFile.open(file);

	if (inFile.is_open())
	{
		inFile >> tmpWidth >> tmpHeight;
		inFile.ignore(1, '\n');

		if (tmpWidth > GetWidth() || tmpHeight > GetHeight())
		{
			return MAP_SIZE_FAIL;
		}
		else
		{
			Game tmpGame(tmpWidth, tmpHeight);

			std::cout << tmpGame.GetWidth() << std::endl;
			std::cout << tmpGame.GetHeight() << std::endl;

			getchar();

			for (int x = 0; x < tmpGame.GetWidth(); x++)
			{
				for (int y = 0; y < tmpGame.GetHeight(); y++)
				{
					inFile >> tmpState;

					tmpGame.SetState(x, y, tmpState);

					inFile.ignore(1, ',');
				}

				
			}

			cellMap = tmpGame.cellMap;
		}
	}
	else
	{
		return NOT_FOUND;
	}

	return LOADED;
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
bool Game::GetState(int x, int y) { return cellMap[x][y]; }
int Game::GetWidth() { return width; }
int Game::GetHeight() { return height; }

int Game::GetNeighbors(int x, int y)
{
	int count = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int neighbor_x = x + i;
			int neighbor_y = y + j;

			if ((i == 0 && j == 0) || (neighbor_x < 0 || neighbor_y < 0 || neighbor_x >= GetWidth() || neighbor_y >= GetHeight()))
			{
				// Skip current cell
			}
			// Edge of the map
			else if (neighbor_x < 0 || neighbor_y < 0 || neighbor_x >= GetWidth() || neighbor_y >= GetHeight())
			{
				// Skip edge
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
void Game::SetState(int x, int y, bool state) { cellMap[x][y] = state; }