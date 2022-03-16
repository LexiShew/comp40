#include <stdbool.h>
#include <stdio.h>
#include "bit2.h"

// sample function for our mapping function
const int DIM1 = 5;
const int DIM2 = 7;
const int MARKER = 1;  /* can only be 1 or 0 */
void check_and_print(int i, int j, Bit2_T a, int b, void *p1);

int main()
{
    Bit2_T testBit2 = Bit2_new(5, 2);

    int putVal = 0;
    (void) putVal;
    int height = Bit2_height(testBit2);
    int width = Bit2_width(testBit2);

    printf("\ntesting width:  %d\n", width);
    printf("\ntesting height: %d\n", height);
    
    printf("testing put:\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Bit2_put(testBit2, j, i, putVal);
            putVal = (putVal + 1) % 2;
        }
    }

    printf("testing get:\n   ");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int getVal = Bit2_get(testBit2, j, i);
            printf("%d ", getVal);
        }
        printf("\n   ");
    }
    printf("\n");

    bool OK = true;
    printf("testing map row major\n");
    Bit2_map_row_major(testBit2, check_and_print, &OK);
    printf("testing map col major\n");
    Bit2_map_col_major(testBit2, check_and_print, &OK);


    printf("testing free:\n");
    Bit2_free(&testBit2);
    printf("Finished testing\n");
    return 0;
}

// sample function for mapping function 
void check_and_print(int i, int j, Bit2_T a, int b, void *p1) 
{
        if ( (i == (DIM1 - 1) ) && (j == (DIM2 - 1) ) ) {
                /* we got the corner */
                *((bool *)p1) &= Bit2_get(a, i, j) == b;
                *((bool *)p1) &= (b == MARKER);
        }

        printf("ar[%d,%d]\n", i, j);
}