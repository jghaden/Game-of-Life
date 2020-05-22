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
	this->generation = 0;

	cellMap.clear();
	cellMap.resize(height, std::vector<bool>(width, CELL_DEAD));

	previousTicks = std::clock();
}

float Game::Time()
{
	// Calculate time between each draw
	currentTicks = std::clock();
	deltaTicks = (float)(currentTicks - previousTicks);
	previousTicks = currentTicks;

	deltaTime = (deltaTicks / (float)CLOCKS_PER_SEC);

	return deltaTime;
}

void Game::SetWidth(int width) { this->width = width; }
void Game::SetHeight(int height) { this->height = height; }

void Game::Reset() { Init(); }

void Game::Random()
{
	bool state;

	for (int y = 0; y < GetHeight(); y++)
	{
		for (int x = 0; x < GetWidth(); x++)
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

	for (int y = 0; y < GetHeight(); y++)
	{
		for (int x = 0; x < GetWidth(); x++)
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

	generation++;

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

			for (int y = 0; y < GetHeight(); y++)
			{
				for (int x = 0; x < GetWidth(); x++)
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
	std::string out;

	for (int y = 0; y < GetHeight(); y++)
	{
		out = "";
		for (int x = 0; x < GetWidth(); x++)
		{
			if (GetState(x, y))
			{
				//WriteAt(x, y, 'Û');
				out += 'Û';
			}
			else
			{
				//WriteAt(x, y, ' ');
				out += ' ';
			}
		}

		WriteAt(0, y, out);
	}
}

void Game::Info()
{
	gotoXY(0, GetHeight() + 1);

	std::cout << "Generation: " << deltaTime << std::endl;
}

// Getters
bool Game::GetState(int x, int y) { return cellMap[y][x]; }
int Game::GetWidth() { return width; }
int Game::GetHeight() { return height; }

int Game::GetNeighbors(int x, int y)
{
	int count = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int neighbor_y = y + j;
			int neighbor_x = x + i;

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
void Game::SetState(int x, int y, bool state) { cellMap[y][x] = state; }