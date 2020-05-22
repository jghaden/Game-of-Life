#pragma once
#include "PCH.h"

enum CELL_STATE
{
	CELL_DEAD = false,
	CELL_ALIVE = true
};

enum FILE_STATUS
{
	NOT_FOUND,
	MAP_SIZE_FAIL,
	LOADED
};

class Game
{
public:
	Game(int width, int height);

	void Reset();
	void Random();
	void SimulationStep();
	FILE_STATUS LoadGame(const char* file);
	void ShowMap();
	void Info();

	// Getters
	bool GetState(int x, int y);
	int GetWidth();
	int GetHeight();
	int GetNeighbors(int x, int y);

	// Setters
	void SetState(int x, int y, bool state);
private:
	int width, height, generation, population;

	std::vector<std::vector<bool>> cellMap;

	void Init();

	void SetWidth(int width);
	void SetHeight(int height);
};