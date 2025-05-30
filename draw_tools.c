#include "draw_tools.h"

// Font Descriptor
font_descriptor_t *fdes = &font_winFreeSystem14x16;

// Pixel indexes
int firstRow = 106;
int firstColumn = 24;
int squareModifier = 46;
int squareSize = 7;
int difficultyRow = 254;
int difficultyColumn = 132;

void paint_it_black ( unsigned short *fb ) {
  // Fill buffer with black color
  for ( int i = 0; i < 480; ++i ) {
    for ( int j = 0; j < 320; ++j ) {
      draw_pixel( i, j, COLOR_BLACK, fb );
    }
  }
}

void draw_game_over ( int score1, int score2, unsigned short *fb ) {
  // Paint it black
  paint_it_black( fb );

  // Game Over text
  draw_char(80, 40, 'G', COLOR_BLUE + COLOR_RED, fb, 4);
  draw_char(118, 40, 'A', COLOR_BLUE + COLOR_RED, fb, 4);
  draw_char(150, 40, 'M', COLOR_BLUE + COLOR_RED, fb, 4);
  draw_char(193, 40, 'E', COLOR_BLUE + COLOR_RED, fb, 4);

  draw_char(258, 40, 'O', COLOR_BLUE + COLOR_RED, fb, 4);
  draw_char(296, 40, 'V', COLOR_BLUE + COLOR_RED, fb, 4);
  draw_char(330, 40, 'E', COLOR_BLUE + COLOR_RED, fb, 4);
  draw_char(366, 40, 'R', COLOR_BLUE + COLOR_RED, fb, 4);

  // Color player wins
  if ( score1 > score2 ) {
    // Red
    draw_char(141, 100, 'R', COLOR_RED, fb, 3);
    draw_char(170, 100, 'E', COLOR_RED, fb, 3);
    draw_char(195, 100, 'D', COLOR_RED, fb, 3);

  } else {
    // Blue
    draw_char(128, 100, 'B', COLOR_BLUE, fb, 3);
    draw_char(154, 100, 'L', COLOR_BLUE, fb, 3);
    draw_char(177, 100, 'U', COLOR_BLUE, fb, 3);
    draw_char(203, 100, 'E', COLOR_BLUE, fb, 3);
  }

  //  Wins
  draw_char(253, 100, 'W', COLOR_WHITE, fb, 3);
  draw_char(294, 100, 'I', COLOR_WHITE, fb, 3);
  draw_char(303, 100, 'N', COLOR_WHITE, fb, 3);
  draw_char(330, 100, 'S', COLOR_WHITE, fb, 3);

  // Print Scores
  draw_score( score1, score2, fb );

  // Press Green Knob to Exit To Menu
  draw_char(80, 290, 'P', COLOR_WHITE, fb, 1);
  draw_char(90, 290, 'R', COLOR_WHITE, fb, 1);
  draw_char(100, 290, 'E', COLOR_WHITE, fb, 1);
  draw_char(110, 290, 'S', COLOR_WHITE, fb, 1);
  draw_char(120, 290, 'S', COLOR_WHITE, fb, 1);
  
  draw_char(140, 290, 'G', COLOR_WHITE, fb, 1);
  draw_char(150, 290, 'R', COLOR_WHITE, fb, 1);
  draw_char(160, 290, 'E', COLOR_WHITE, fb, 1);
  draw_char(170, 290, 'E', COLOR_WHITE, fb, 1);
  draw_char(180, 290, 'N', COLOR_WHITE, fb, 1);

  draw_char(200, 290, 'K', COLOR_WHITE, fb, 1);
  draw_char(210, 290, 'N', COLOR_WHITE, fb, 1);
  draw_char(220, 290, 'O', COLOR_WHITE, fb, 1);
  draw_char(230, 290, 'B', COLOR_WHITE, fb, 1);

  draw_char(250, 290, 'T', COLOR_WHITE, fb, 1);
  draw_char(260, 290, 'O', COLOR_WHITE, fb, 1);

  draw_char(280, 290, 'E', COLOR_WHITE, fb, 1);
  draw_char(290, 290, 'X', COLOR_WHITE, fb, 1);
  draw_char(303, 290, 'I', COLOR_WHITE, fb, 1);
  draw_char(310, 290, 'T', COLOR_WHITE, fb, 1);

  draw_char(330, 290, 'T', COLOR_WHITE, fb, 1);
  draw_char(340, 290, 'O', COLOR_WHITE, fb, 1);

  draw_char(358, 290, 'M', COLOR_WHITE, fb, 1);
  draw_char(370, 290, 'E', COLOR_WHITE, fb, 1);
  draw_char(380, 290, 'N', COLOR_WHITE, fb, 1);
  draw_char(390, 290, 'U', COLOR_WHITE, fb, 1);
}

void draw_score ( int score1, int score2, unsigned short *fb ) {
    // draw black boxes
    for ( int i = 0; i < 48; ++i ) {
        for ( int j = 0; j < 16; ++j ) {
            draw_pixel( i, j, 0, fb );
        }
    }

    for ( int i = 432; i < 480; ++i ) {
        for ( int j = 0; j < 16; ++j ) {
            draw_pixel( i, j, 0, fb );
        }
    }

    // Get number strings
    char num1[7], num2[7];
    to_string( num1, score1 );
    to_string( num2, score2 );

    // Print score1
    draw_char(0, 0, num1[0], COLOR_WHITE, fb, 1);
    draw_char(8, 0, num1[1], COLOR_WHITE, fb, 1);
    draw_char(16, 0, num1[2], COLOR_WHITE, fb, 1);
    draw_char(24, 0, num1[3], COLOR_WHITE, fb, 1);
    draw_char(32, 0, num1[4], COLOR_WHITE, fb, 1);
    draw_char(40, 0, num1[5], COLOR_WHITE, fb, 1);

    // Print score2
    draw_char(432, 0, num2[0], COLOR_WHITE, fb, 1);
    draw_char(440, 0, num2[1], COLOR_WHITE, fb, 1);
    draw_char(448, 0, num2[2], COLOR_WHITE, fb, 1);
    draw_char(456, 0, num2[3], COLOR_WHITE, fb, 1);
    draw_char(464, 0, num2[4], COLOR_WHITE, fb, 1);
    draw_char(472, 0, num2[5], COLOR_WHITE, fb, 1);
}

void draw_pixel_big(int x, int y, unsigned short color, unsigned short *fb, int scale ) {
  int i,j;
  for (i=0; i<scale; i++) {
    for (j=0; j<scale; j++) {
      draw_pixel(x+i, y+j, color, fb );
    }
  }
}
 
int char_width(int ch) {
  int charWidth;
  if (!fdes->width) {
    charWidth = fdes->maxwidth;
  } else {
    charWidth = fdes->width[ch-fdes->firstchar];
  }
  return charWidth;
}
 
void draw_char(int x, int y, char ch, unsigned short color, unsigned short *fb, int scale ) {
  int w = char_width(ch);
  const font_bits_t *ptr;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    if (fdes->offset) {
      ptr = &fdes->bits[fdes->offset[ch-fdes->firstchar]];
    } else {
      int bw = (fdes->maxwidth+15)/16;
      ptr = &fdes->bits[(ch-fdes->firstchar)*bw*fdes->height];
    }
    int i, j;
    for (i=0; i<fdes->height; i++) {
      font_bits_t val = *ptr;
      for (j=0; j<w; j++) {
        if ((val&0x8000)!=0) {
          draw_pixel_big(x+scale*j, y+scale*i, color, fb, scale);
        }
        val<<=1;
      }
      ptr++;
    }
  }
}

void to_string ( char str[], int num ) {
    int i, rem, len = 6;
    if ( num >= 999999 ) {
        // Make the number 999999
        for ( i = 0; i < len; ++i ) {
            str[i] = 9 + '0';
        }
    } else {
        // Transfer number to string
        for (i = 0; i < len; i++)
        {
            rem = num % 10;
            num = num / 10;
            str[len - (i + 1)] = rem + '0';
        }
    }
    str[len] = '\0';
}

void draw_pixel ( int x, int y, unsigned short color, unsigned short *fb ) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}

void draw_tile (int index, unsigned short color, unsigned short *fb ) {
  // Get initial information
  int x = index % 24;
  int y = ( index - x ) / 24;
  int startX = x * 20;
  int maxX = startX + 20;
  int startY = y * 20;
  int maxY = startY + 20;

  // Draw the tile
  for ( int i = startX; i < maxX; ++ i ) {
      for ( int j = startY; j < maxY; ++j ) {
          draw_pixel( i, j, color, fb );
      }
  }
}

void draw_fruit (int index, unsigned short *fb ) {
  // Get initial information
  int x = index % 24;
  int y = ( index - x ) / 24;
  int startX = x * 20 + 5;
  int maxX = startX + 10;
  int startY = y * 20 + 5;
  int maxY = startY + 10;

  // Draw the fruit
  for ( int i = startX; i < maxX; ++ i ) {
      for ( int j = startY; j < maxY; ++j ) {
          draw_pixel( i, j, COLOR_YELLOW, fb );
      }
  }
}

void draw_menu_choice (int choice, unsigned short color, unsigned short *fb ) {
  // Get initial information
  int rowStart = firstRow + choice * squareModifier;
  int rowEnd = rowStart + squareSize;
  int lastColumn = firstColumn + squareSize;

  // Draw menu choice
  for ( int i = rowStart; i < rowEnd; ++i ) {
      for ( int j = firstColumn; j < lastColumn; ++j ) {
          draw_pixel( j, i, color, fb );
      }
  }
}

void draw_difficulty_choice (int choice, unsigned short *fb ) {
  // Get initial information
  int row = difficultyRow;
  int col = difficultyColumn;
  unsigned short color = COLOR_WHITE;

  // Draw black box
  for ( int i = row; i < row + 200; ++i ) {
      for ( int j = col; j < col + 40; ++j ) {
          draw_pixel( i, j, 0, fb );
      }
  }

  // Draw choice
  switch ( choice ) {
  case 0:
      // EASY
      draw_char(270, 140, 'E', color, fb, 2);
      draw_char(291, 140, 'A', color, fb, 2);
      draw_char(309, 140, 'S', color, fb, 2);
      draw_char(333, 140, 'Y', color, fb, 2);
      break;
  case 1:
      // MEDIUM
      draw_char(270, 140, 'M', color, fb, 2);
      draw_char(291, 140, 'E', color, fb, 2);
      draw_char(309, 140, 'D', color, fb, 2);
      draw_char(333, 140, 'I', color, fb, 2);
      draw_char(346, 140, 'U', color, fb, 2);
      draw_char(364, 140, 'M', color, fb, 2);
      break;
  case 2:
      // HARD
      draw_char(270, 140, 'H', color, fb, 2);
      draw_char(291, 140, 'A', color, fb, 2);
      draw_char(309, 140, 'R', color, fb, 2);
      draw_char(333, 140, 'D', color, fb, 2);
      break;
  default:
      break;
  }
}

void draw_menu(unsigned short *fb) {
  // Open ppm menu image
  FILE *menu_img_file = fopen(PATH_TO_MENU_IMAGE, "rb");
  if (menu_img_file == NULL) {
      fprintf(stderr, "Error opening snake.ppm");
      exit(1);
  }

  // Create menu image buffer
  unsigned char *menu_img_buffer = (unsigned char*) malloc(320*480*3);
  if (menu_img_buffer == NULL) {
      fprintf(stderr, "Couldn't allocate memory for menu image buffer!");
      exit(1);
  }

  // Eat useless data
  char *random_string = (char*)malloc(50);
  for (int i = 0; i < 4; i++) {
      fscanf(menu_img_file, "%s\n", random_string);
  }
  
  // Load menu image to the buffer
  fread(menu_img_buffer, sizeof(unsigned char), 320*480*3, menu_img_file);
  for (int i = 0; i < 320*480; i++) {
      //fb[i] = (((((menu_img_buffer[i*3]/0xff)*0x3f)<<11)&0xf800) + ((((menu_img_buffer[i*3+1]/0xff)*0x7f)<<5)&0x7ff) + (((menu_img_buffer[i*3+2]/0xff)*0x3f)&0x1f));        
      fb[i] = ((((menu_img_buffer[i*3]/0xff)*0x1f)<<11) + (((menu_img_buffer[i*3+1]/0xff)*0x3f)<<5)) + (((menu_img_buffer[i*3+2]/0xff)*0x1f));        
  }

  // Draw initial game mode and difficulty choices
    draw_menu_choice(0, 0x7e0, fb);
    draw_difficulty_choice(0, fb);

  // Free useless data
  free(random_string);
}
