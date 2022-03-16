/**************************************************************
 *
 *                     rgb-ypp.h
 *
 * Assignment: Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 27, 2021
 *     
 * Header file for rgb-ypp.c which converts rgb values to
 * component video representation and back.
 * Function declarations include:
 *      rgb_to_ypp_A2
 *      ypp_to_rgb_A2
 * Struct declarations include:
 *      Ypp_struct
 *
 **************************************************************/

#include <stdio.h>
#include "pnm.h"
#include "a2methods.h"
#include <mem.h>

typedef struct Ypp_struct
{
    float y;
    float pb;
    float pr;
} *Ypp_struct;

/*
 * rgb_to_ypp_A2
 * Behavior: converts an rgb_A2 to a ypp_A2
 * Parameters: 
        A2 rgb_A2
        int denominator
 * Returns: A2 of ypps
 * Expectations/errors: rgb_A2 should not be null
 */
extern A2Methods_UArray2 rgb_to_ypp_A2(A2Methods_UArray2 rgb_A2, int denom);

/*
 * ypp_to_rgb_A2
 * Behavior: convert A2 of ypp values to an A2 of rgb values
 * Parameters: 
        A2 of ypp values
 * Returns: A2 of rgb values
 * Expectations/errors: ypp_A2 should not be null
 */
extern A2Methods_UArray2 ypp_to_rgb_A2(A2Methods_UArray2 ypp_A2);