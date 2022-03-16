#include <stdbool.h>
#include <stdio.h>
#include "uarray2.h"

// these are test functions that can be arguemnts for our map functions
void add10MapFunction(int col, int row, UArray2_T uarray2, void *startVal,
                                                                void *cl);
void check_and_print(int i, int j, UArray2_T a, void *p1, void *p2);



int main()
{
    UArray2_T testArray2 = UArray2_new(5, 2, 4);
    int num = 0;
    int height = UArray2_height(testArray2);
    int width = UArray2_width(testArray2);

    printf("\ntesting width:  %d\n", width);
    printf("\ntesting height: %d\n", height);
    printf("\ntesting size:   %d\n", UArray2_size(testArray2));
    

    printf("\ntesting at:\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("(%d, %d)\n", j, i);
            // Note: if uarray2 has a zero width or height, these loops dont
            // run so this line is never called
            *(int*) UArray2_at(testArray2, j, i) = num;
            num++;
        }
    }

    int plsError = *(int*) UArray2_at(testArray2, 0, 0);
    (void) plsError;

    // printf("\ntesting print:\n");
    // UArray2_print(testArray2);

    printf("\ntesting row_major:\n");
    bool OK = true;
    UArray2_map_row_major(testArray2, check_and_print, &OK);
    printf("\ntesting col_major:\n");
    UArray2_map_col_major(testArray2, check_and_print, &OK);
    
    printf("\ntesting free:\n");
    UArray2_free(&testArray2);
    
    printf("\nFinished testing! Remember to check valgrind\n");
    return 0;
}



// FUNCTIONS FOR MAPPING
void add10MapFunction(int col, int row, UArray2_T uarray2, void *startVal,
                                                                void *cl)
{
    printf("In add10 function\n");
    (void) col;
    (void) row;
    (void) uarray2;
    *(int*) startVal += 10;
    *(int*) cl += 1;
    printf("leaving add10\n");

}

typedef long number;

const int DIM1 = 5;
const int DIM2 = 7;
const int ELEMENT_SIZE = sizeof(number);
const int MARKER = 99;
void
check_and_print(int i, int j, UArray2_T a, void *p1, void *p2) 
{
        //p1 is a pointer to a long
        //p1 is our current value 
        number *entry_p = p1;
        
        //p2 is a pointer to a boolean value
        //p2 stores whether or not the value at the speciifed index is the expected value
        *((bool *)p2) &= (UArray2_at(a, i, j) == entry_p);

        // if at the corner
        //sets p2 to whether or not there is a marker in the corner
        if ( (i == (DIM1 - 1) ) && (j == (DIM2 - 1) ) ) {
                /* we got the corner */
                // marker = 99, just a sentinel value?
                *((bool *)p2) &= (*entry_p == MARKER);
        }

        //prints out current index
        printf("ar[%d,%d]\n", i, j);
}