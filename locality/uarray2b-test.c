#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "uarray2b.h"

// these are test functions that can be arguemnts for our map functions
void printValue(int col, int row, UArray2b_T array2b, void *elem, void *cl) {
    (void) elem;
    (void) cl;
    printf(" value: %d\n", *(int*)UArray2b_at(array2b, col, row));
    // printf("(%d, %d): %d\n", col, row, *(int*)UArray2b_at(array2b, col, row));
}

// static void check_and_increment(int i, int j, UArray2b_T a, void *elem, void *cl) 
// {
//     (void)i;
//     (void)j;
//     (void)a;
//     int *p = elem;
//     int *counter = cl;

//     assert(*p == *counter);
//     *counter += 1;   /* NOT *counter++! */
// }


int main()
{
    UArray2b_T testArray2b = UArray2b_new(3, 4, 4, 1);
    if (testArray2b == NULL) {
        printf("test array 2b is null");
    }

    int num = 0;
    int height = UArray2b_height(testArray2b);
    int width = UArray2b_width(testArray2b);

    printf("\ntesting width:     %d\n", width);
    printf("\ntesting height:    %d\n", height);
    printf("\ntesting size:      %d\n", UArray2b_size(testArray2b));
    printf("\ntesting blksize:   %d\n", UArray2b_blocksize(testArray2b));
    

    printf("\ntesting at:\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("(%d, %d)\n", j, i);
            // Note: if uarray2 has a zero width or height, these loops dont
            // run so this line is never called
            *(int*) UArray2b_at(testArray2b, j, i) = num;
            num++;
        }
    }

    printf("\ntesting print:\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("(%d, %d): %d\n", j, i, *(int*) UArray2b_at(testArray2b, j, i));
        }
    }

    printf("\ntesting map:\n");
    int counter = 0;
    UArray2b_map(testArray2b, printValue, &counter);
    

    printf("\ntesting free:\n");
    UArray2b_free(&testArray2b);
    
    printf("\nFinished testing! Remember to check valgrind\n");
    return 0;
    

}
