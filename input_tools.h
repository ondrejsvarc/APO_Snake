#include <stdbool.h>


bool pressGreen ( unsigned char *mem_base );

void getValues ( unsigned char *mem_base );

int getDirection ( int value, int previousValue );

int getRedValue ( unsigned char *mem_base );

int getRedMovement ( unsigned char *mem_base, int previousValue );

int getBlueValue ( unsigned char *mem_base );

int getBlueMovement ( unsigned char *mem_base, int previousValue );

int getGreenValue ( unsigned char *mem_base );

int getGreenMovement ( unsigned char *mem_base, int previousValue );