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
	Game(unsigned width, unsigned height);

	void Reset();
	void Random();
	void SimulationStep();
	void ShowMap();

	// Getters
	bool GetState(unsigned int x, unsigned int y);
	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetNeighbors(unsigned int x, unsigned int y);

	// Setters
	void SetState(unsigned int x, unsigned int y, bool state);
protected:
	unsigned width, height;

	std::vector<std::vector<bool>> cellMap;

	void Init();
};