#include <iostream>

// represents a section of a the snake which move around and eats Food to grow larger in the Snake game
class SnakePart {
private:
	// the direction this part is currently traveling in
	// up: 1, right: 2, down: 3, left: 4
	int direction;

	// the x and y position of the SnakePart on the board
	int xPos;
	int yPos;

public:
	// creates a new instance of a Snake object
	SnakePart(int x, int y, int dir) {
		this->xPos = x;
		this->yPos = y;
		this->direction = dir;
	}

	// determines if the current snake part would run into a given coordinate on the next frame
	bool wouldRunInto(int x, int y) {
		return ((this->xPos == x && this->yPos == y - 1 && this->direction == 3)
			|| (this->xPos == x && this->yPos == y + 1 && this->direction == 1)
			|| (this->xPos == x - 1 && this->yPos == y && this->direction == 2)
			|| (this->xPos == x + 1 && this->yPos == y && this->direction == 4));
	}

	// sets the direction of this SnakePart
	void setDirection(int dir) {
		this->direction = dir;
	}

	// retrieves the direction of this SnakePart
	int getDirection() {
		return this->direction;
	}

	// sets the X position of this SnakePart
	void setXPos(int x) {
		this->xPos = x;
	}

	// retrieves the X position of this SnakePart
	int getXPos() {
		return this->xPos;
	}

	// sets the Y position of this SnakePart
	void setYPos(int y) {
		this->yPos = y;
	}

	// retrieves the Y position of this SnakePart
	int getYPos() {
		return this->yPos;
	}
};