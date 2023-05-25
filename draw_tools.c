#include "draw_tools.h"

int firstLine = 94;
int firstColumn = 119;
int lineModifier = 54;
int lineWidth = 4;
int width = 241;
int height = 49;

void draw_score ( int score1, int score2, unsigned short *fb ) {
    // draw black boxes
    for ( int i = 0; i < 40; ++i ) {
        for ( int j = 0; i < 16; ++j ) {
            draw_pixel( i, j, 0, fb );
        }
    }

    for ( int i = 440; i < 480; ++i ) {
        for ( int j = 0; i < 16; ++j ) {
            draw_pixel( i, j, 0, fb );
        }
    }

    // Get number strings
    char num1[6], num2[6];
    toString( num1, score1 );
    toString( num2, score2 );

    // Print score1
    draw_char(0, 0, num1[0], 0xffff);
    draw_char(8, 0, num1[1], 0xffff);
    draw_char(16, 0, num1[2], 0xffff);
    draw_char(24, 0, num1[3], 0xffff);
    draw_char(32, 0, num1[4], 0xffff);

    // Print score2
    draw_char(440, 0, num2[0], 0xffff);
    draw_char(448, 0, num2[1], 0xffff);
    draw_char(456, 0, num2[2], 0xffff);
    draw_char(464, 0, num2[3], 0xffff);
    draw_char(472, 0, num2[4], 0xffff);

}

void draw_pixel_big(int x, int y, unsigned short color) {
  int i,j;
  for (i=0; i<scale; i++) {
    for (j=0; j<scale; j++) {
      draw_pixel(x+i, y+j, color);
    }
  }
}
 
int char_width(int ch) {
  int width;
  if (!fdes->width) {
    width = fdes->maxwidth;
  } else {
    width = fdes->width[ch-fdes->firstchar];
  }
  return width;
}
 
void draw_char(int x, int y, char ch, unsigned short color) {
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
          draw_pixel_big(x+scale*j, y+scale*i, color);
        }
        val<<=1;
      }
      ptr++;
    }
  }
}

void toString ( char str[], int num ) {
    int i, rem, len = 6;

    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

void draw_pixel ( int x, int y, unsigned short color, unsigned short *fb ) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}

void drawTile ( int index, unsigned short color, unsigned short *fb ) {
    int x = index % 24;
    int y = ( index - x ) / 16;
    int startX = x * 20;
    int maxX = startX + 20;
    int startY = y * 20;
    int maxY = startY + 20;

    for ( int i = startX; i < maxX; ++ i ) {
        for ( int j = startY; j < maxY; ++j ) {
            draw_pixel( i, j, color, fb );
        }
    }

}

void drawFruit ( int index, unsigned short *fb ) {
    int x = index % 24;
    int y = ( index - x ) / 16;
    int startX = x * 20 + 5;
    int maxX = startX + 10;
    int startY = y * 20 + 5;
    int maxY = startY + 10;

    for ( int i = startX; i < maxX; ++ i ) {
        for ( int j = startY; j < maxY; ++j ) {
            draw_pixel( i, j, 0xf800, fb );
        }
    }
}

void drawMenuChoice ( int choice, unsigned short color, unsigned short *fb ) {
    int lineStart = firstLine + choice * lineModifier;
    int lineEnd = lineStart + height;
    int firstLineEnd = lineStart + lineWidth;
    int secondLineStart = lineStart + height - lineWidth;
    int lastColumn = firstColumn + width;

    for ( int i = lineStart; i < lineEnd; ++i ) {
        if ( i  < firstLineEnd || i > secondLineStart ) {
            for ( int j = firstColumn; j < lastColumn; ++j ) {
                draw_pixel( j, i, color, fb );
            }
        } else {
            for ( int j = 0; j < lineWidth; ++j ) {
                draw_pixel( firstColumn + j, i, color, fb );
                draw_pixel( firstColumn + width - lineWidth + j, i, color, fb );
            }
        }
    }
}

void drawMenu(unsigned short *fb) {
    FILE *menu_img_file = fopen("/tmp/komanmi1/snake.ppm", "rb");
    if (menu_img_file == NULL) {
        fprintf(stderr, "Error opening snake.ppm");
        exit(1);
    }

    unsigned char *menu_img_buffer = (unsigned char*) malloc(320*480*3);
    if (menu_img_buffer == NULL) {
        fprintf(stderr, "Couldn't allocate memory for menu image buffer!");
        exit(1);
    }

    char *random_string = (char*)malloc(50);
    for (int i = 0; i < 4; i++) {
        fscanf(menu_img_file, "%s\n", random_string);
    }
    
    fread(menu_img_buffer, sizeof(unsigned char), 320*480*3, menu_img_file);
    for (int i = 0; i < 320*480; i++) {
        //fb[i] = (((((menu_img_buffer[i*3]/0xff)*0x3f)<<11)&0xf800) + ((((menu_img_buffer[i*3+1]/0xff)*0x7f)<<5)&0x7ff) + (((menu_img_buffer[i*3+2]/0xff)*0x3f)&0x1f));        
        fb[i] = (((((menu_img_buffer[i*3]/0xff)*0x3f)>>1)<<12) + ((((menu_img_buffer[i*3+1]/0xff)*0x7f)>>1)<<6)) + (((menu_img_buffer[i*3+2]/0xff)*0x3f)>>1);        
    }

    drawMenuChoice(0, 0x7e0, fb);

    free(random_string);
}