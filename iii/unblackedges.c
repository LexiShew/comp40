/**************************************************************
 *
 *                     unblackedges.c
 *
 * Assignment: Homework 2 -- iii
 * Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 * Date: October 4, 2021
 *     
 * This file contains the program used to remove black pixels from the
 * edges of PBM images. This program takes in PBMs as input from stdin
 * or command-line arguments, then creates a new PBM that removes all edge
 * balck pixels.
 * --------QUESTIONS FOR TA'S--------------
 * 1. Is it better practice to create a variable if we only
      use it once but its clearer?
   2. How specific do our comments have to be, what do we do with
      the headers?
   3. What does it mean we might recieve a P4
 **************************************************************/

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include "pnmrdr.h"
#include "bit2.h"

FILE *getFile(int argc, char* argv[]);
Bit2_T makeBitImage(FILE *file);
void unblackEdges(Bit2_T image);
void printImage(Bit2_T image);
void iterate(Bit2_T grid);
int flag(Bit2_T grid, Bit2_T flagGrid, int layer, int col, int row);
void initializeEmptyGrid(Bit2_T grid);
int findMin(int a, int b);
void deleteEdge(Bit2_T grid, Bit2_T flagGrid);

int main(int argc, char* argv[])
{
    FILE *file = getFile(argc, argv);
    Bit2_T image = makeBitImage(file);
    iterate(image);
    Bit2_free(&image);
    return 0;
}


FILE *getFile(int argc, char* argv[])
{
    assert( argc == 1 || argc == 2);
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


Bit2_T makeBitImage(FILE *file)
{
    Pnmrdr_T reader = Pnmrdr_new(file);
    Pnmrdr_mapdata mapdata = Pnmrdr_data(reader);

    int width = (int) mapdata.width;
    int height = (int) mapdata.height;

    assert(width != 0);
    assert(height != 0);

    Bit2_T image = Bit2_new(width, height);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned data = Pnmrdr_get(reader);
            Bit2_put(image, j, i, (int) data);
        }
    }
    Pnmrdr_free(&reader);
    return image;
}

void printImage(Bit2_T image)
{
    assert(image != NULL);
    printf("P1\n");
    int width = Bit2_width(image);
    int height = Bit2_height(image);
    printf("%u ", width);
    printf("%u\n", height);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d", Bit2_get(image, j, i));
        }
        printf("\n");
    }
}




void iterate(Bit2_T grid)
{
    int height = Bit2_height(grid);
    int width = Bit2_width(grid);
    //find the minimum between height and width and use ceiling division
    int maxLayers = findMin(width, height)/2 + (findMin(width, height) % 2 != 0) - 1;

    //create a new empty grid to store the "flagged" edges
    Bit2_T flagGrid = Bit2_new(width, height);
    initializeEmptyGrid(flagGrid);

    int layer = 0;
    bool spiral_out = false;
    bool finished = false;
    int changes = 0;
    
     while (!finished) {
        // if we reached the maximum number of layers, 
        // spiral back out
        if (layer == maxLayers &&  spiral_out == false) {
            spiral_out = true;
        }
        // if our current layer is 0, then check if any
        // new changes were detected, if not, then finish
        if (layer == 0 && spiral_out == true) {
            if ( changes == 0) {
                finished = true;
            } else {
                changes = 0;
                spiral_out = false;
            }
        }
        //checking the top row
        for ( int i = layer; i < width - layer; i++) {
            changes += flag(grid, flagGrid, layer, i, layer);
            changes += flag(grid, flagGrid, layer, width  - 1 - i, layer);
            
        } 
        //checking the rightmost column
        for ( int j = layer; j < height - layer; j++) {
            changes += flag(grid, flagGrid, layer, width - 1 - layer, j);
            changes += flag(grid, flagGrid, layer, width - 1 - layer, height - 1 - j);
           
        }
        //checking the bottom row
        for ( int i = width - layer - 1; i >= layer; i--) {
            changes += flag(grid, flagGrid, layer, i, height - 1 - layer);
            changes += flag(grid, flagGrid, layer, width  - 1 - i, height - 1 - layer);
            
        } 
        //checking the leftmost row
        for ( int j = height - layer - 1; j >= layer; j--) {
            changes += flag(grid, flagGrid, layer, layer, j);
            changes += flag(grid, flagGrid, layer, layer, height  - 1 - j);
           
        }
        if (spiral_out == false) {
            layer ++;
        } else {
            layer --;
        }
    }
    
    deleteEdge(grid, flagGrid);
    Bit2_free(&flagGrid);
    printImage(grid);
    
}

int flag(Bit2_T grid, Bit2_T flagGrid, int layer, int col, int row)
{
    int currBit = Bit2_get(grid, col, row);
    int currFlagBit = Bit2_get(flagGrid, col, row);
    bool changed = false;

    if ( currBit == 1 && currFlagBit != 1) {    
        if ( layer != 0) {
            int leftBit = Bit2_get(flagGrid, col - 1, row);
            int rightBit = Bit2_get(flagGrid, col + 1, row);
            int topBit = Bit2_get(flagGrid, col, row - 1);
            int botBit = Bit2_get(flagGrid, col, row + 1);

            if ( leftBit != 0 || rightBit != 0 || \
                topBit != 0 || botBit != 0 ) {
                Bit2_put(flagGrid, col, row, 1);
                return 1;
            }
        }
        else if ( layer == 0) {
            Bit2_put(flagGrid, col, row, 1);
            return 1;
        }
    }
    return changed;
}

void initializeEmptyGrid(Bit2_T grid) {
    int height = Bit2_height(grid);
    int width = Bit2_width(grid);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Bit2_put(grid, j, i, 0);   
        }
    }
}

int findMin(int a, int b) {
    if ( a < b) {
        return a;
    }
    return b;
}

void deleteEdge(Bit2_T grid, Bit2_T flagGrid) {
    int height = Bit2_height(grid);
    int width = Bit2_width(grid);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ( Bit2_get(flagGrid, j, i ) == 1) {
                Bit2_put(grid, j, i, 0);
            } 
        }
    }
}