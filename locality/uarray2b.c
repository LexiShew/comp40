/**************************************************************
 *
 *                     uarray2b.c
 *
 * Assignment: Homework 3 -- locality
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 14, 2021
 *     
 * This is the UArray2b implementation.
    Representation of the UArray2b Array: 
        Use a UArray2 as the parent array aka the blocks.
        Within the blocks (within each UArray2 element), we have a single 
        UArray.
 *
 **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"
#include <uarray.h>
#include <except.h>
#include <assert.h>
#include <math.h>
#include <mem.h>
#include "uarray2b.h"

#define T UArray2b_T

struct T {
    int width; /*Cells*/
    int height; /*Cells*/
    int size;
    int blocksize;
    int blockArrayHeight; /*Blocks*/
    int blockArrayWidth; /*Blocks*/
    
    UArray2_T blockArray;
};

void mapCell(int col, int row, UArray_T uarray, 
            void apply(int col, int row, T uarray2b, void *elem, void *cl), 
            void *cl);


/*
 * UArray2b_new
 * Behavior: creates a new uarray2b
 * Parameters: width of uarray2b
               height of uarray2b
               size of elements in uarray2b
               blocksize in uarray2b
 * Returns: T (uarray2b)
 * Expectations/errors: all parameters must be greater than 0
 */
T UArray2b_new (int width, int height, int size, int blocksize)
{
    assert(width > 0);
    assert(height > 0);
    assert(size > 0);
    assert(blocksize > 0);

    T uarray2b;
    NEW(uarray2b); 

    /*find how many blocks we need*/
    int blockArrayWidth = ceil((double) width / (double) blocksize);
    int blockArrayHeight = ceil((double) height / (double) blocksize);
    
    // this creates a block matrix (parent array) where each block is
    // spatious enough to contain an entire UArray (representing
    // a collection of individual cells)
    UArray2_T blockArray = UArray2_new(blockArrayWidth, 
                                 blockArrayHeight, 
                                 sizeof(UArray_T));
    // e.g. in the example, there would be a 3x3 block matrix, and each
    // block would contain 16 cells, and each cell has a size of 4 bytes
    // (if they're ints), so the total size of each block would be 
    // blocksize * blocksize * size, so the total size of the entire 
    // UArray2b would be 
    // blockArrayHeight * blockArrayWidth * blocksize * blocksize * size

    /*put single UArray into each block*/
    for (int r = 0; r < blockArrayHeight; r++) {
        for (int c = 0; c < blockArrayWidth; c++) {
            UArray_T emptyUarray = UArray_new(blocksize * blocksize, size);
            *(UArray_T*) UArray2_at(blockArray, c, r) = emptyUarray;
        }
    }
                                
    assert(uarray2b != NULL);

    uarray2b->width = width;
    uarray2b->height = height;
    uarray2b->size = size;
    uarray2b->blocksize = blocksize;
    uarray2b->blockArrayWidth = blockArrayWidth; 
    uarray2b->blockArrayHeight = blockArrayHeight;
    uarray2b->blockArray = blockArray;

    return uarray2b;
}

/*
 * UArray2b_new_64K_block
 * Behavior: creates a new UArray2b with block size 64k. 
            If a single cell can't fit, then block size will be 1.
 * Parameters:  width of uarray2b
                height of uarray2b
                size of cells in uarray2b
 * Returns: UArray2b_T
 * Expectations/errors: width, height, and size are all above 0
 */
T UArray2b_new_64K_block(int width, int height, int size)
{
    assert(width > 0);
    assert(height > 0);
    assert(size > 0);
    // size of the block <= 65504
    int kb64 = 64*1024;
    int totalCells = kb64 / size;
    int blkSize = sqrt(totalCells);
    if (size > kb64) {
        return UArray2b_new(width, height, size, 1);
    }
    else {
        return UArray2b_new(width, height, size, blkSize);
    }
}

/*
 * UArray2b_free
 * Behavior: frees all elements in a given uarray2b
 * Parameters: pointer to UArray2b_T
 * Returns: none
 * Expectations/errors: uarray2b should not be null
 */
void UArray2b_free (T *uarray2b)
{
    assert(*uarray2b != NULL && uarray2b != NULL);
    for (int r = 0; r < (*uarray2b)->blockArrayHeight; r++) {
        for (int c = 0; c < (*uarray2b)->blockArrayWidth; c++) {
            UArray_T cells = *(UArray_T*) UArray2_at((*uarray2b)->blockArray,
                                                                        c, r);
            UArray_free(&cells);
        }
    }
    UArray2_free(&(*uarray2b)->blockArray);
    FREE(*uarray2b);
}

/*
 * UArray2b_width
 * Behavior: provides width of given uarray2b
 * Parameters: uarray2b
 * Returns: integer representing the width of the uarray2b
 * Expectations/errors: uarray2b must not be NULL
 */
int UArray2b_width (T uarray2b)
{
    assert(uarray2b != NULL);
    return uarray2b->width;
}

/*
 * UArray2b_height
 * Behavior: provides height of given uarray2b
 * Parameters: uarray2b
 * Returns: integer representing height of uarray2b
 * Expectations/errors: uarray2b must not be NULL
 */
int UArray2b_height (T uarray2b)
{
    assert(uarray2b != NULL);
    return uarray2b->height;
}

/*
 * UArray2b_size
 * Behavior: provides size of elements in a given uarray2b
 * Parameters: uarray2b
 * Returns: integer representing size of elements of uarray2b
 * Expectations/errors: uarray2b must not be NULL
 */
int UArray2b_size (T uarray2b)
{
    assert(uarray2b != NULL);
    return uarray2b->size;
}

/*
 * UArray2b_blocksize
 * Behavior: provides the blocksize in a given uarray2b
 * Parameters: uarray2b
 * Returns: integer representing blocksize
 * Expectations/errors: uarray2b is not NULL
 */
int UArray2b_blocksize(T uarray2b)
{
    assert(uarray2b != NULL);
    return uarray2b->blocksize;
}

/*
 * UArray2b_at
 * Behavior: provides element at position (col, row) in uarray2b
 * Parameters: uarray2b
               integer representing the wanted element's col
               integer representing the wanted element's row
 * Returns: void pointer to the element at position (col, row)
 * Expectations/errors: uarray2b is not NULL
                        column is within range
                        row is within range
 */
void *UArray2b_at(T uarray2b, int col, int row) //TODO
{
    assert(uarray2b != NULL);
    assert(col >= 0 && col < uarray2b->width);
    assert(row >= 0 && row < uarray2b->height);
    int blksize = uarray2b->blocksize;
    /* get the block that the cell is stored in */    
    UArray_T currBlock = *(UArray_T*) UArray2_at(uarray2b->blockArray, 
                                                        col / blksize,
                                                        row / blksize);

    UArray_T *currCell = UArray_at(currBlock, (row % blksize) * (blksize) + (col % blksize));

    return currCell;
}

/*
 * UArray2b_map
 * Behavior: visits every cell in one block and applies function to each
             before moving to another block
 * Parameters: uarray2b
               void function
               void pointer to closure
 * Returns: none
 * Expectations/errors: uarray2b is not NULL
 */
void UArray2b_map(T uarray2b,
            void apply(int col, int row, T uarray2b, void *elem, void *cl),
            void *cl)
{
    assert(uarray2b != NULL);
    
    for (int r = 0; r < uarray2b->blockArrayHeight; r++) {
        for (int c = 0; c < uarray2b->blockArrayWidth; c++) {
            UArray_T currBlock = *(UArray_T*) UArray2_at(uarray2b->blockArray, c, r);
            for (int i = 0; i < pow(uarray2b->blocksize, 2); i++) {
                int imageCol = c * uarray2b->blocksize + i % uarray2b->blocksize;
                int imageRow = r * uarray2b->blocksize + i / uarray2b->blocksize;

                if (imageCol < uarray2b->width && imageRow < uarray2b->height) {
                    void *currCell = UArray_at(currBlock, i);
                
                    if (imageCol >= 0 && imageCol < uarray2b->width && imageRow >= 0 && imageRow < uarray2b->height) {
                        apply(imageCol, imageRow, uarray2b, currCell, cl);
                    }
                }
            }
        }
    }
}