/**************************************************************
 *
 *                     sudoku.c
 *
 * Assignment: Homework 2 -- iii
 * Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 * Date: October 4, 2021
 *     
 * This file contains the program used to identify valid sudoku
 * solutions. This program operates as a predicate -- that is,
 * the exit code of the program indictes whether the puzzle is
 * solved -- exit(0) -- or an invalid solution -- exit(1).
 *
 **************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "uarray2.h"
#include "pnmrdr.h"

FILE *getFile(int argc, char* argv[]);
UArray2_T fillArray(UArray2_T grid, FILE *file);
bool check(UArray2_T grid, int f(UArray2_T grid, int iteration, int index));

int getFromSquare(UArray2_T grid, int iteration, int index);
int getFromCol(UArray2_T grid, int iteration, int index);
int getFromRow(UArray2_T grid, int iteration, int index);

int main(int argc, char* argv[])
{
    FILE *file = getFile(argc, argv);

    int sudokuBoardSize = 9;
    int intByteSize = 4;
    UArray2_T sudokuGrid = UArray2_new(sudokuBoardSize, sudokuBoardSize,
                                                            intByteSize);
    sudokuGrid = fillArray(sudokuGrid, file);
    fclose(file);

    if (sudokuGrid == NULL) {
        UArray2_free(&sudokuGrid);
        exit(1);
    }

    if (check(sudokuGrid, getFromCol) && check(sudokuGrid, getFromRow) && check(sudokuGrid, getFromSquare)) {
        UArray2_free(&sudokuGrid);
        return 0;
    }
    else {
        UArray2_free(&sudokuGrid);
        exit(1);
    }
}


// return ptr to file -- need to get stdin to work?
FILE *getFile(int argc, char* argv[])
{
    assert(argc == 1 || argc == 2);
    FILE *file = NULL;
    if (argc == 1) {  
        file = stdin;
        return file;
    } 
    else if (argc == 2) { 
        file = fopen(argv[1], "rb");
        return file;
    }

    assert(file != NULL);
    return NULL;
}


UArray2_T fillArray(UArray2_T grid, FILE *file)
{
    // get all the pgm formatting stuff
    Pnmrdr_T reader = Pnmrdr_new(file);

    Pnmrdr_mapdata mapdata = Pnmrdr_data(reader);
    int width = mapdata.width;
    int height = mapdata.height;
    if (width != 9 || height != 9) {
        Pnmrdr_free(&reader);
        UArray2_free(&grid);
        exit(1);
    }
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned data = Pnmrdr_get(reader);
            if (data < 1 || data > 9) {
                Pnmrdr_free(&reader);
                return NULL;
            }
            *(int*) UArray2_at(grid, j, i) = (int) data;
        }
    }
    Pnmrdr_free(&reader);
    return grid;
}


int getFromCol(UArray2_T grid, int iteration, int index) 
{
    return *((int*) UArray2_at(grid, iteration, index)) - 1;
}

int getFromRow(UArray2_T grid, int iteration, int index) 
{
    return *((int*) UArray2_at(grid, index, iteration)) - 1;
}

int getFromSquare(UArray2_T grid, int iteration, int index) 
{
    return  *((int*) UArray2_at(grid, 3*(iteration/3) + index/3, 3*(iteration/3) + index%3)) - 1;
}

bool check(UArray2_T grid, int f(UArray2_T grid, int iteration, int index)) {
    for (int section = 0; section < 9; section++) {
        //                   1      2      3      4      5      6      7      8      9
        bool numbers[9] = {false, false, false, false, false, false, false, false, false};
        for (int i = 0; i < 9; i++) {
            numbers[f(grid, section, i)] = true;
        }
        for (int i = 0; i < 9; i++) {
            if (!numbers[i]) {
                return false;
            }
        }
    }
    return true;
}




/*

void assignFlags(Bit2_T grid, int col, int row) {
    
    int currBit = Bit2_get(grid, col, row);
    int topBit = -1;
    int leftBit = -1;
    if (!(col == 0 && row == 0) && currBit == 1) {
        if (col == 0) {
            topBit = Bit2_get(grid, col, row - 1);
            if (topBit != 0) {
                Bit2_put(grid, col, row, topBit);
            }
        else if (row == 0) {
            leftBit = Bit2_get(grid, col - 1, row);
            if (currBit == 1 && leftBit != 0) {
                Bit2_put(grid, col, row, leftBit);
            }
        }
        else {
            topBit = Bit2_get(grid, col, row - 1);
            leftBit = Bit2_get(grid, col - 1, row);
            
        }
        else {

        }
        int leftBit = Bit2_get(grid, col - 1, row);
        int topBit = Bit2_get(grid, col, row - 1);
        
        if (currBit == 1) {
            if (leftBit != 0 ) {
                Bit2_put(grid, col, row, leftBit);
            }
            else if (topBit != 0) {
                Bit2_put(grid, col, row, topBit);
            }
        }
    }
    
}
*/