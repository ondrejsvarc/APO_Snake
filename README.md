# APO_Snake

> Snake game created for MicroZed APO by Ondrej Svarc and Michal Komanec.

## User Manual

### Controls:
  -	**Menu**
    -	Turn the green knob to select the game mode.
    -	Turn the blue knob to adjust the difficulty level.
    -	Press the green knob to confirm your settings. 
  -	**Game**
    -	In the 1-player game, you can control only the blue snake.
    -	Use the red knob to control the red snake and the blue knob to control the blue snake.
    -	Rotate the knob left to turn left, right to turn right, and keep it in the same position to continue straight.
    -	To end the game, press and hold both the red and blue knobs simultaneously until the end screen appears.

### Rules:
  1.	If a snake eats a yellow fruit, it will grow longer.
  2.	If a snake goes beyond the map boundaries, it will die.
  3.	If a snake collides with its own body or the opponent's body, it will die.
  4.	When both snakes die, the game ends, and the snake with the higher score wins.
  5.	If the game is manually ended by pressing the red and blue knobs, the snake with the higher score wins.

### Score:
  -	Every tick the snake is alive its length is added to its score.
  -	When the snake dies, its score is final.



## Technical Documentation

### Compilation:
  1.	Change target directory path (PATH_TO_MENU_IMAGE) in draw_tools.h.
  2.	Change target ip address (TARGET_IP) in Makefile.
  3.	Delete “depend” file if it is in the project directory.
  4.	Run command “make run”.

### Block Scheme:
  -	**ai.h**
    -	Contains functions that generates ai moves and generates new fruit positions.
    -	Depends on *snake.h*.
  -	**draw_tools.h**
    -	Contains functions for drawing to frame buffer.
    -	Depends on *font_types.h*.
  -	**game.h**
    -	Contains functions for starting and running a game of Snake.
    -	Depends on *snake.h, mzapo_parlcd.h, input_tools.h, draw_tools.h, ai.h, rgb_tools.h, led_tools.h, score_tools.h*.
  -	**input_tools.h**
    -	Contains functions for translating knob movements to change of directions and different user inputs.
    -	Depends on *mzapo_parlcd.h, mzapo_phys.h, mzapo_regs.h*.
  -	**led_tools.h**
    -	Contains functions for manipulating the LED stripe.
    -	Depends on *mzapo_parlcd.h, mzapo_phys.h, mzapo_regs.h*.
  -	**rgb_tools.h**
    -	Contains functions for manipulating the RGB LEDs.
    -	Depends on *mzapo_parlcd.h, mzapo_phys.h, mzapo_regs.h*.
  -	**score_tools.h**
    -	Contains function for updating the score.
    -	Depends on *draw_tools.h, snake.h*.
  -	**snake.h**
    -	Contains Snake struct and functions for moving Snake.
    -	Depends on *draw_tools.h*.
  -	**main.c**
    -	Contains the main functions for the Snake game.
    -	Depends on *mzapo_parlcd.h, mzapo_phys.h, mzapo_regs.h, draw_tools.h, led_tools.h, input_tools.h, font_types.h, rgb_tools.h, game.h*.
