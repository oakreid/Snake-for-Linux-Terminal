#include <iostream>

// represents the "food" object the snake picks up in the Snake game
class Food {
private:
	// the x and y position of the Food on the board
	int xPos;
	int yPos;

public:
	// creates a new instance of a Food object
	Food(int x, int y) {
		this->xPos = x;
		this->yPos = y;
	}

	// sets the X position of this Food
	void setXPos(int x) {
		this->xPos = x;
	}

	// retrieves the X position of this Food
	int getXPos() {
		return this->xPos;
	}

	// sets the Y position of this Food
	void setYPos(int y) {
		this->yPos = y;
	}

	// retrieves the Y position of this Food
	int getYPos() {
		return this->yPos;
	}
};