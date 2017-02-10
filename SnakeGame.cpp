#include <iostream>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include "SnakePart.cpp"
#include "Food.cpp"

// represents an instance of the game "Snake"
class SnakeGame {
private:
	int boardWidth;
	int boardHeight;
	Food* snakeFood;
	int score;
	bool wiiRemoteControl;
	std::deque<SnakePart>* snake;
	int tickRate;
	int currentTick;
	bool gameOver;
	int fd;
	int gameSpeed;

	// prints the rendering of the game out to the console
	void render() {
		// draws the "board" state
		std::string board = "┌";
		for (int i = 0; i < this->boardWidth; i++) 
			board += "─";
		board += "┐\n";
		for (int r = 0; r < this->boardHeight; r++) {
			board += "│";
			for (int c = 0; c < this->boardWidth; c++) {
				bool notOccupied = true;
				for (int s = 0; s < this->snake->size(); s++) {
					if (this->snake->at(s).getXPos() == c && this->snake->at(s).getYPos() == r) {
						board += this->printAppropriateChar(s);
						notOccupied = false;
						break;
					}
				}
				if (notOccupied && this->snakeFood->getXPos() == c && this->snakeFood->getYPos() == r)
					board += "X";
				else if (notOccupied)
					board += " ";
			}
			board += "│\n";
		}
		board += "└";
		for (int i = 0; i < this->boardWidth; i++) 
			board += "─";
		board += "┘\n";

		// shows the score and if the game is over or if the player has won
		std::cout << board << "Score: " << this->score;
		if (this->gameOver && this->snake->size() == this->boardHeight * this->boardWidth)
			std::cout << " You Win!";
		else if (this->gameOver)
			std::cout << " Game Over.";
		std::cout << "\n\n";
	}

	// updates the game state
	void update() {
		// updates the current tick of the game
		if (this->currentTick + 1 > this->tickRate)
			this->currentTick = 1;
		else
			this->currentTick++;

		// updates the head of the snake based on user input
		// non-wiimote control implemented for testing purposes only
		if (wiiRemoteControl) {
			int moveCode = 0;

			// read the next 5 data packets from the wiimote
			for (int i = 0; i < 5; i++) {
				// taken from the Lab 5 Wiimote.cc file:
				// Read a packet of 32 bytes from Wiimote
				char buffer[32];
				read(this->fd, buffer, 32);

				// Extract code (byte 10) and value (byte 12) from packet
				int code = buffer[10];
		 		short acceleration = * (short *) (buffer + 12); 

		 		if (acceleration > 300 && code == 3)
		 			moveCode = 4;
		 		else if (acceleration < -1 * 300 && code == 3)
		 			moveCode = 2;
		 		else if (acceleration > 300 && code == 5)
		 			moveCode = 1;
		 		else if (acceleration < -1 * 300 && code == 5)
		 			moveCode = 3;
			}

		 	switch (moveCode) {
			    case 1:
			        if (this->snake->at(0).getDirection() != 3)
			        	this->snake->at(0).setDirection(1);
			        	break;
			    case 4:
				if (this->snake->at(0).getDirection() != 2)
			        	this->snake->at(0).setDirection(4);			        
			        	break;
			    case 3:
				if (this->snake->at(0).getDirection() != 1)
			        	this->snake->at(0).setDirection(3);			        
			        	break;
			    case 2:
				if (this->snake->at(0).getDirection() != 4)
			        	this->snake->at(0).setDirection(2);	
			        	break;
		    }
			

		}
		else {
			// allows one to simulate the snake movement with the keyboard by stepping through each frame
			char key;
			std::cin >> key;
			switch (key) {
			    case 'w':
			        if (this->snake->at(0).getDirection() != 3)
			        	this->snake->at(0).setDirection(1);
			        break;
			    case 'a':
					if (this->snake->at(0).getDirection() != 2)
			        	this->snake->at(0).setDirection(4);			        
			        break;
			    case 's':
					if (this->snake->at(0).getDirection() != 1)
			        	this->snake->at(0).setDirection(3);			        
			        break;
			    case 'd':
					if (this->snake->at(0).getDirection() != 4)
			        	this->snake->at(0).setDirection(2);	
			        break;
		    }
		}

		if (this->currentTick == this->tickRate || (this->gameSpeed == 2 && this->currentTick == this->tickRate / 2)) {
			// check if the head would hit the food in the next move
			if (this->snake->at(0).wouldRunInto(this->snakeFood->getXPos(), this->snakeFood->getYPos())) {
				SnakePart s(this->snakeFood->getXPos(), this->snakeFood->getYPos(), this->snake->at(0).getDirection());
				this->snake->push_front(s);
				this->score++;
				if (this->snake->size() < this->boardWidth * this->boardHeight)
					this->placeNewFood();
			}
			// check to update snake position
			else
				for (int i = snake->size() - 1; i >= 0; i--) {
					switch (this->snake->at(i).getDirection()) {
						case 1:
							this->snake->at(i).setYPos(this->snake->at(i).getYPos() - 1);
							break;
						case 2:
							this->snake->at(i).setXPos(this->snake->at(i).getXPos() + 1);
							break;
						case 3:
							this->snake->at(i).setYPos(this->snake->at(i).getYPos() + 1);
							break;
						default:
							this->snake->at(i).setXPos(this->snake->at(i).getXPos() - 1);
							break;
					}
					if (i > 0) 
						this->snake->at(i).setDirection(this->snake->at(i - 1).getDirection());
				}

			// declares the game over if the snake runs out of bounds or has reached the maximum size
			this->gameOver = (this->snake->at(0).getXPos() < 0
				|| this->snake->at(0).getXPos() >= this->boardWidth
				|| this->snake->at(0).getYPos() < 0
				|| this->snake->at(0).getYPos() >= this->boardHeight
				|| this->snake->size() == this->boardHeight * this->boardWidth);
			
			// declares the game over if the snake head runs into the body
			if (!(this->gameOver)) 
				for (int i = 1; i < this->snake->size(); i++)
					if ((this->snake->at(0).getXPos() == this->snake->at(i).getXPos() && this->snake->at(0).getYPos() == this->snake->at(i).getYPos())) {
						this->gameOver = true;
						break;
					}

		}
	}

	// place a new snake Food in a random location when the snake picks up the current one
	void placeNewFood() {
		std::deque<Food*>* temp = new std::deque<Food*>();
		for (int r = 0; r < this->boardHeight; r++)
			for (int c = 0; c < this->boardWidth; c++)
				if (unoccupiedBySnake(c, r)) {
					Food* f = new Food(c, r);
					temp->push_front(f);
				}
		this->snakeFood = temp->at(rand() % temp->size());
		delete temp;
	}

	// checks if a certain coordinate is occupied by a SnakePart
	bool unoccupiedBySnake(int x, int y) {
		for (int s = 0; s < this->snake->size(); s++)
			if (this->snake->at(s).getXPos() == x && this->snake->at(s).getYPos() == y)
				return false;
		return true;
	}

	// creates the "snake" look for the snake by returning the appropriate ASCII character for each SnakePart
	std::string printAppropriateChar(int sec) {
		if (sec == 0)
			return "Θ";
		else if (sec == this->snake->size() - 1)
			return "O";
		else {
			int thisXPos = this->snake->at(sec).getXPos();
			int thisYPos = this->snake->at(sec).getYPos();
			int prevXPos = this->snake->at(sec + 1).getXPos();
			int prevYPos = this->snake->at(sec + 1).getYPos();
			int nextXPos = this->snake->at(sec - 1).getXPos();
			int nextYPos = this->snake->at(sec - 1).getYPos();

			if (prevXPos == nextXPos)
				return "║";
			else if (prevYPos == nextYPos)
				return "═";
			else if ((prevXPos < thisXPos && nextXPos == thisXPos && prevYPos == thisYPos && nextYPos > thisYPos)
					|| (prevXPos == thisXPos && nextXPos < thisXPos && prevYPos > thisYPos && nextYPos == thisYPos))
				return "╗";
			else if ((prevXPos < thisXPos && nextXPos == thisXPos && prevYPos == thisYPos && nextYPos < thisYPos)
					|| (prevXPos == thisXPos && nextXPos < thisXPos && prevYPos < thisYPos && nextYPos == thisYPos))
				return "╝";
			else if ((prevXPos > thisXPos && nextXPos == thisXPos && prevYPos == thisYPos && nextYPos > thisYPos)
					|| (prevXPos == thisXPos && nextXPos > thisXPos && prevYPos > thisYPos && nextYPos == thisYPos))
				return "╔";
			else
				return "╚";
		}
	}

public:
	/*
	creates a new instance of a SnakeGame object
	parameters boardWidth and boardHeight represent the respective dimensions of the area the snake may travel in
	parameter tickRate represents the rate at which packet information from the Wiimote is read by the game
	parameter wiiRemoteControl should be set to true when wanting to control the game with the Wiimote and false when wanting to test the game with keyboard control
	*/
	SnakeGame(int boardWidth, int boardHeight, int tickRate, bool wiiRemoteControl) {
		// instantiate all game variables
		this->score = 0;
		this->currentTick = 0;
		this->gameOver = false;
		this->snakeFood = new Food(9, 9);
		this->snake = new std::deque<SnakePart>();
		this->wiiRemoteControl = wiiRemoteControl;
		this->gameSpeed = 2;

		// instantiates the file directory to read wiimote commands
		if (this->wiiRemoteControl)
			this->fd = open("/dev/input/event0", O_RDONLY);
		else
			this->fd = 0;

		// instantiates the width of the game board with a minimum of 10
		if (boardWidth < 10)
			this->boardWidth = 10;
		else
			this->boardWidth = boardWidth;

		// instantiates the height of the game board with a minimum of 10
		if (boardHeight < 10)
			this->boardHeight = 10;
		else
			this->boardHeight = boardHeight;

		// sets the tick rate of the game in ticks per second, uses 2 for keyboard testing purposes
		if (wiiRemoteControl)
			this->tickRate = tickRate;
		else
			this->tickRate = 2;

		// initialize the snake with 6 parts
		for (int i = 0; i < 6; i++) {
			SnakePart s(9, i + 1, 3);
			this->snake->push_front(s);
		}
	}

	// wipe the memory
	~SnakeGame() {
		delete this->snake;
		delete this->snakeFood;
		if (this->wiiRemoteControl)
			close(this->fd);
	}

	// run the game proper
	void run() {
		// initialize random seed for use in placing Food
		srand(time(NULL));

		// set the speed of the game
		if (this->wiiRemoteControl)
			for(;;) {
				std::cout << "Select the difficulty (\"1\" for easy, \"2\" for hard): ";
				std::cin >> this->gameSpeed;
				if (this->gameSpeed == 1 || this->gameSpeed == 2)
					break;
			}

		// continues to run the game until you win or lose
		while (!(this->gameOver)) {
			// update the game then display the updated image twice per second
			this->update();
			if (this->currentTick == this->tickRate || (this->gameSpeed == 2 && this->currentTick == this->tickRate / 2))
				this->render();

			// update the game to recieve input from the wiimote on every tick
			usleep(1000000 / this->tickRate);
		}
	}
};
