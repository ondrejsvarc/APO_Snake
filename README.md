# APO_Snake

Snake game created for MicroZed APO by Ondrej Svarc and Michal Komanec.

# User Manual

Controls:
  •	Menu
    o	Turn the green knob to select the game mode.
    o	Turn the blue knob to adjust the difficulty level.
    o	Press the green knob to confirm your settings. 
  •	Game
    o	In the 1-player game, you can control only the blue snake.
    o	Use the red knob to control the red snake and the blue knob to control the blue snake.
    o	Rotate the knob left to turn left, right to turn right, and keep it in the same position to continue straight.
    o	To end the game, press and hold both the red and blue knobs simultaneously until the end screen appears.

Rules:
  1.	If a snake eats a yellow fruit, it will grow longer.
  2.	If a snake goes beyond the map boundaries, it will die.
  3.	If a snake collides with its own body or the opponent's body, it will die.
  4.	When both snakes die, the game ends, and the snake with the higher score wins.
  5.	If the game is manually ended by pressing the red and blue knobs, the snake with the higher score wins.

Score:
  •	Every tick the snake is alive its length is added to its score.
  •	When the snake dies, its score is final.



# Technical Documentation

Compilation:
  1.	Change target directory path (PATH_TO_MENU_IMAGE) in draw_tools.h.
  2.	Change target ip address (TARGET_IP) in Makefile.
  3.	Delete “depend” file if it is in the project directory.
  4.	Run command “make run”.

Block Scheme:
  •	ai.h
    o	Contains functions that generates ai moves and generates new fruit positions.
    o	Depends on snake.h.
  •	draw_tools.h
    o	Contains functions for drawing to frame buffer.
    o	Depends on font_types.h.
  •	game.h
    o	Contains functions for starting and running a game of Snake.
    o	Depends on snake.h, mzapo_parlcd.h, input_tools.h, draw_tools.h, ai.h, rgb_tools.h, led_tools.h, score_tools.h.
  •	input_tools.h
    o	Contains functions for translating knob movements to change of directions and different user inputs.
    o	Depends on mzapo_parlcd.h, mzapo_phys.h, mzapo_regs.h.
  •	led_tools.h
    o	Contains functions for manipulating the LED stripe.
    o	Depends on mzapo_parlcd.h, mzapo_phys.h, mzapo_regs.h.
  •	rgb_tools.h
    o	Contains functions for manipulating the RGB LEDs.
    o	Depends on mzapo_parlcd.h, mzapo_phys.h, mzapo_regs.h.
  •	score_tools.h
    o	Contains function for updating the score.
    o	Depends on draw_tools.h, snake.h.
  •	snake.h
    o	Contains Snake struct and functions for moving Snake.
    o	Depends on draw_tools.h
  •	main.c
    o	Contains the main functions for the Snake game.
    o	Depends on mzapo_parlcd.h, mzapo_phys.h, mzapo_regs.h, draw_tools.h, led_tools.h, input_tools.h, font_types.h, rgb_tools.h, game.h.
