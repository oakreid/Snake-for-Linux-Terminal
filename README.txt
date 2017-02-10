- HOW TO PLAY -

Compile "SnakePart.cpp" "Food.cpp" "SnakeGame.cpp" and "main.cpp" using the 
Makefile and run using the command "./Snake"

IMPORTANT: Make sure your terminal is using the UTF-8 (Unicode) charset. Failure 
to do so will result in distorted graphics.

When prompted, enter either "1" for easy mode or "2" for hard mode and press 
enter.

NOTE: To increase immersion and prevent the viewing of previous frames, decrease 
the size of the terminal window such that it surrounds only the game board 
outlined by the solid border as well as the "Score" value below it.

The head of the snake is the "Θ" symbol and the tail is the "O".

Collecting the food (represented by the "X") will cause the snake to grow larger 
and increase your score.

Running the head of the snake into a "wall" or into a segment of its body or 
tail will result in a game over.

Growing the snake into such a size that it fills up the entire "board" results 
in a win!


- KEYBOARD CONTROLS -

Set the fourth argument of the SnakeGame constructor in the "main.cpp" file to 
"false" to use keyboard controls.

NOTE: Keyboard controls were implemented purely for testing purposes. By using 
the keyboard controls you will only be able to step through the game frame by 
frame, not actually 'play' the game per se.

Enter w, a, s, or d to change the heading of the snake to up, left, down, or 
right, respectively. Then press enter to advance the frame.


- WIIMOTE CONTROLS -

Set the fourth argument of the SnakeGame constructor in the "main.cpp" file to 
"true" to use Wiimote controls (it is set to this by default).

Quickly flick the Wiimote straight up, down, left, or right to change the 
snake's heading to the corresponding direction.

NOTE: The Wiimote is quite sensitive, keeping it completely still when not 
wanting to change direction is ideal. Additionally, flicking the Wiimote in 
non-cardinal directions may result in uxexpected turns by the snake.


- OTHER -

The size of the game board as well as the "framerate" at which the game reads 
Wiimote imput can be changed by editing the appropriate arguments of the 
SnakeGame constructor. See SnakeGame.cpp for details.