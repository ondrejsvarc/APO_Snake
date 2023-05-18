unsigned short *fb;
fb  = (unsigned short *)malloc(320*480*2);

void draw_pixel(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}

void drawTile ( int index, unsigned short color ) {
    int x = index % 24;
    int y = ( index - x ) / 16;
    int startX = x * 20;
    int maxX = startX + 20;
    int startY = y * 20;
    int maxY = startY + 20;

    for ( int i = startX; i < maxX; ++ i ) {
        for ( int j = startY; j < maxY; ++j ) {
            draw_pixel( i, j, color );
        }
    }

}

for (ptr = 0; ptr < 480*320 ; ptr++) {
    parlcd_write_data(parlcd_mem_base, fb[ptr]);
}