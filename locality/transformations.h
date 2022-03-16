
/**************************************************************
 *
 *                     transformations.h
 *
 * Assignment: Homework 3 -- locality
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 14, 2021
 *     
 * This file is the interface for the ppm transformations.
 * The functions declared in this file are the functions used to
 * transform PPM images.
 *
 **************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <mem.h>

#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"

/* Function Declarations */
typedef A2Methods_UArray2 A2;

struct newCl {
    Pnm_ppm *finalPPM;
    A2Methods_T *methods;
};

/*
 * rotate_0
 * Description: Copies pixel from original PPM to same location on new PPM.
 * Parameters: 
        int current column of pixel (c)
        int row of current pixel (r)
        A2 to be copied/transformed (array2)
        A2Methods_Object pointer holding the values of the pixel (ptr)
        void pointer closure (voidCl)
 * Returns: none
 * Expectations/errors: 
        array2, ptr, voidCl should not be null
 */
extern void rotate_0(int c, int r, A2 array2, 
        A2Methods_Object *ptr, void *cl);

/*
 * rotate_90
 * Behavior: Copies pixel from original PPM to appropriate location for a 90
        degree rotation.
 * Parameters: 
        int current column of pixel (c)
        int row of current pixel (r)
        A2 to be copied/transformed (array2)
        A2Methods_Object pointer holding the values of the pixel (ptr)
        void pointer closure (voidCl)
 * Returns: none
 * Expectations/errors: 
        array2, ptr, voidCl should not be null
 */
extern void rotate_90(int i, int j, A2 array2, 
        A2Methods_Object *ptr, void *cl);

/*
 * rotate_180
 * Behavior: Copies pixel from original PPM to appropriate location for a 180
        degree rotation.
 * Parameters: 
        int current column of pixel (c)
        int row of current pixel (r)
        A2 to be copied/transformed (array2)
        A2Methods_Object pointer holding the values of the pixel (ptr)
        void pointer closure (voidCl)
 * Returns: none
 * Expectations/errors: 
        array2, ptr, voidCl should not be null
 */
extern void rotate_180(int i, int j, A2 array2, 
        A2Methods_Object *ptr, void *cl);

/*
 * rotate_270
 * Behavior: Copies pixel from original PPM to appropriate location for a 270
        degree rotation.
 * Parameters: 
        int current column of pixel (c)
        int row of current pixel (r)
        A2 to be copied/transformed (array2)
        A2Methods_Object pointer holding the values of the pixel (ptr)
        void pointer closure (voidCl)
 * Returns: none
 * Expectations/errors: 
        array2, ptr, voidCl should not be null
 */
extern void rotate_270(int i, int j, A2 array2, 
        A2Methods_Object *ptr, void *cl);

/*
 * flip_horiz
 * Behavior: Copies pixel from original PPM to appropriate location for a
        horizontal flip.
 * Parameters: 
        int current column of pixel (c)
        int row of current pixel (r)
        A2 to be copied/transformed (array2)
        A2Methods_Object pointer holding the values of the pixel (ptr)
        void pointer closure (voidCl)
 * Returns: none
 * Expectations/errors: 
        array2, ptr, voidCl should not be null
 */
extern void flip_horiz(int i, int j, A2 array2, 
        A2Methods_Object *ptr, void *cl);

/*
 * flip_vert
 * Behavior: Copies pixel from original PPM to appropriate location for a
        vertical flip.
 * Parameters: 
        int current column of pixel (c)
        int row of current pixel (r)
        A2 to be copied/transformed (array2)
        A2Methods_Object pointer holding the values of the pixel (ptr)
        void pointer closure (voidCl)
 * Returns: none
 * Expectations/errors: 
        array2, ptr, voidCl should not be null
 */
extern void flip_vert(int i, int j, A2 array2, 
        A2Methods_Object *ptr, void *cl);

/*
 * transpose
 * Behavior: Copies pixel from original PPM to appropriate location for
        transpose.
 * Parameters: 
        int current column of pixel (c)
        int row of current pixel (r)
        A2 to be copied/transformed (array2)
        A2Methods_Object pointer holding the values of the pixel (ptr)
        void pointer closure (voidCl)
 * Returns: none
 * Expectations/errors: 
        array2, ptr, voidCl should not be null
 */
extern void transpose(int i, int j, A2 array2, 
        A2Methods_Object *ptr, void *cl);