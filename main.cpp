#include <iostream>
#include "SnakeGame.cpp"

// the main method used to run an instance of the Snake game
int main() {
	SnakeGame* s = new SnakeGame(30, 30, 60, true);
	s->run();
	delete s;
	return 0;
}