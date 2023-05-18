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