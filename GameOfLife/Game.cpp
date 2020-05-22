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

	cellMap.resize(width, std::vector<bool>(height, false));
}

void Game::Reset() { Init(); }

void Game::Random()
{
	// Generate random map
}

void Game::SimulationStep()
{
	// Iterate by one step for the simulation
}

void Game::ShowMap()
{
	// Print cellMap
}

// Getters
bool Game::GetState(unsigned int x, unsigned int y) { return cellMap[x][y]; }
unsigned int Game::GetWidth() { return width; }
unsigned int Game::GetHeight() { return height; }

unsigned int Game::GetNeighbors(unsigned int x, unsigned int y)
{
	// Count neighboring cells
}

// Setters
void Game::SetState(unsigned int x, unsigned int y, bool state) { cellMap[x][y] = state; }