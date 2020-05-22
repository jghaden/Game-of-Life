#include "PCH.h"

#include "Game.h"

int main(void)
{
	SetWindowSize(845, 900);
	SetFontSize(12, 12);
	ShowConsoleCursor(false);

	Game game(100, 50);

	while (true)
	{
		//// Line
		//game.SetState(39, 11, CELL_ALIVE);
		//game.SetState(40, 11, CELL_ALIVE);
		//game.SetState(41, 11, CELL_ALIVE);

		//// Plus
		//game.SetState(40, 10, CELL_ALIVE);

		//game.SetState(39, 11, CELL_ALIVE);
		//game.SetState(40, 11, CELL_ALIVE);
		//game.SetState(41, 11, CELL_ALIVE);

		//game.SetState(40, 12, CELL_ALIVE);

		//game.LoadGame("games/glider.bin");

		game.Random();

		for (int i = 0; i < 500; i++)
		{
			game.ShowMap();

			game.SimulationStep();

			game.Info();
		}

		game.Reset();

		ClearScreen();
	}

	return 0;
}