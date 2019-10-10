#include <iostream>
#include <SDL.h>
#include "Game.h"
#include <time.h>

int main(int argc, char** argv) {
	srand(time(NULL));
	Game game;

	std::cout << "Hello" << std::endl;

	if (!game.Run()) {
		std::cerr << "*** Something horrible has happened" << std::endl;
		return 1;
	}

	std::cout << "Goodbye" << std::endl;

	return 0;
}