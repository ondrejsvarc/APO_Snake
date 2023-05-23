#include "draw_tools.h"

int firstLine = 94;
int firstColumn = 119;
int lineModifier = 54;
int lineWidth = 4;
int width = 241;
int height = 49;

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
                draw_pixel( i, j, color, fb );
            }
        } else {
            for ( int j = 0; j < lineWidth; ++j ) {
                draw_pixel( i, firstColumn + j, color, fb );
                draw_pixel( i, firstColumn + width - lineWidth + j, color, fb );
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