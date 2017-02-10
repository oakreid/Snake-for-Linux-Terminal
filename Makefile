Snake: main.o SnakeGame.o Food.o SnakePart.o
	g++ main.o SnakeGame.o Food.o SnakePart.o -o Snake
main.o: main.cpp
	g++ -c main.cpp
SnakeGame.o: SnakeGame.cpp
	g++ -c SnakeGame.cpp
Food.o: Food.cpp
	g++ -c Food.cpp
SnakePart.o: SnakePart.cpp
	g++ -c SnakePart.cpp
clean:
	rm -f *.o Snake