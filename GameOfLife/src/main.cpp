#include "PCH.h"

#include "Game.h"

int main(void)
{
	SetWindowSize(680, 695);
	SetFontSize(12, 12);
	ShowConsoleCursor(false);

	Game game(80, 40);

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

		game.Random();

		for (int i = 0; i < 100; i++)
		{
			game.ShowMap();

			//getchar();

			game.SimulationStep();
		}

		game.Reset();
	}

	return 0;
}