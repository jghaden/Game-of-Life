#include "PCH.h"

#include "Game.h"

int main(void)
{
	ShowConsoleCursor(false);

	Game game(80, 25);

	while (true)
	{
		//// Line
		//game.SetState(39, 11, CELL_ALIVE);
		//game.SetState(40, 11, CELL_ALIVE);
		//game.SetState(41, 11, CELL_ALIVE);

		// Plus
		game.SetState(40, 10, CELL_ALIVE);

		game.SetState(39, 11, CELL_ALIVE);
		game.SetState(40, 11, CELL_ALIVE);
		game.SetState(41, 11, CELL_ALIVE);

		game.SetState(40, 12, CELL_ALIVE);


		for (int i = 0; i < 2000; i++)
		{
			game.ShowMap();
			std::cout << game.GetNeighbors(43, 11);
			getchar();
			game.SimulationStep();
		}

		game.Reset();
	}

	return 0;
}