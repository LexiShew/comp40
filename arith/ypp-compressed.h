/**************************************************************
 *
 *                     ypp-compressed.h
 *
 * Assignment: Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 27, 2021
 *     
 * Header file for ypp-compressed.c.
 * Contains declarations for functions:
    ypp_to_compressed_A2
    compressed_to_ypp_A2
 *
 **************************************************************/
#include <stdio.h>

#include "pnm.h"
#include "a2methods.h"
#include <mem.h>

 /*
 * ypp_to_compressed_A2
 * Behavior: convert A2 of ypps to a compressed A2
 * Parameters: A2 of ypps
 * Returns: A2 of compressed values
 * Expectations/errors: 
 */
extern A2Methods_UArray2 ypp_to_compressed_A2(A2Methods_UArray2 ypp_A2);

/*
 * compressed_to_ypp_A2
 * Behavior: convert compressed A2 to an A2 of ypp values
 * Parameters: A2 compressed_A2
 * Returns: A2 of ypp values
 * Expectations/errors: compressed_A2 is not null
 */
extern A2Methods_UArray2 compressed_to_ypp_A2(A2Methods_UArray2 compressed_A2);