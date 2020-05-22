#pragma once
#include "PCH.h"

enum CELL_STATE
{
	CELL_DEAD = false,
	CELL_ALIVE = true
};

class Game
{
public:
	Game(int width, int height);

	void Reset();
	void Random();
	void SimulationStep();
	void ShowMap();

	// Getters
	bool GetState(int x, int y);
	int GetWidth();
	int GetHeight();
	int GetNeighbors(int x, int y);

	// Setters
	void SetState(int x, int y, bool state);
protected:
	int width, height;

	std::vector<std::vector<bool>> cellMap;

	void Init();
};