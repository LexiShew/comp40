#ifndef UM_RUN_H_INCLUDED
#define UM_RUN_H_INCLUDED


/*****************************************************************************
 *
 *                                  um_run.h
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the interface for the um_run sub-driver file, which contains
 * the one function, um_run, which handles unpacking and running the
 * instructions of the program.
 *
 ****************************************************************************/


/*
 * um_run
 * Behavior: executes the instructions found in the m[0] array
 * Parameters: uint32_t *m0 -- pointer to the first element of the m[0] array
 * Expectations/errors: m0 must end with a halt instruction, therefore also
 *                      can't be empty
 */
extern void um_run(uint32_t *m0);

#endif