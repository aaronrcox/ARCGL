
#include "Game1.h"
#include <iostream>

int main(int argc, char **argv)
{
	Game1 *game = new Game1(600, 400);
	game->Run();
	delete game;

	return 0;
}
