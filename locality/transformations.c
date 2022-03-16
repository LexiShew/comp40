/**************************************************************
 *
 *                     transformations.c
 *
 * Assignment: Homework 3 -- locality
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 14, 2021
 *     
 * This file is the implementation for the ppm transformations.
 * The functions defined in this file are the functions applied to 
 * each pixel in a PPM, causing the result PPM to be a tranformation
 * of the original PPM.
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
#include "cputiming.h"
#include "transformations.h"

/* Function Declarations */
typedef void applyFunction(int c, int r, A2 array2, 
        A2Methods_Object *ptr, void *cl);
applyFunction *transformation;

/*
 * rotate_0
 * Behavior: 
        This function is called on single pixels.
        Copies pixel from original PPM to same location on new PPM.
        The final PPM is passed in a closure (voidCl) along with methods.
        Pixels of the final PPM are set to the rgb values provided in the
            ptr argument.
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
void rotate_0(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl)
{
    assert(voidCl != NULL);
    assert(array2 != NULL);
    assert(ptr != NULL);

    /*access methods and finalPPM from closure argument*/
    struct newCl *cl = voidCl;
    A2Methods_T meth = *(cl->methods);
    Pnm_ppm resultPPM = *(cl->finalPPM);
    A2 resultA2 = resultPPM->pixels;
    /*set pixels in the final PPM*/
    if (resultA2 == NULL) {
        resultA2 = meth->new(meth->width(array2), 
                            meth->height(array2), 
                            meth->size(array2));
    }
    
    /*set the final PPM rgb at specific coordinates to 
        rgb from pointer argument*/
    *(struct Pnm_rgb*) meth->at(resultA2, c, r) = *(struct Pnm_rgb*) ptr;

    /*set pixels, width, and height of final image*/
    resultPPM->pixels = resultA2;
    resultPPM->width = meth->width(resultPPM->pixels);
    resultPPM->height = meth->height(resultPPM->pixels);
}

/*
 * rotate_90
 * Behavior: 
        This function is called on single pixels.
        Copies pixel from original PPM to appropriate location on new PPM
            for 90 degree rotation.
        The final PPM is passed in a closure (voidCl) along with methods.
        Pixels of the final PPM are set to the rgb values provided in the
            ptr argument.
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
void rotate_90(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl)
{
    assert(voidCl != NULL);
    assert(array2 != NULL);
    assert(ptr != NULL);

    /*access methods and finalPPM from closure argument*/
    struct newCl *cl = voidCl;
    A2Methods_T meth = *(cl->methods);
    Pnm_ppm resultPPM = *(cl->finalPPM);

    A2 resultA2 = resultPPM->pixels;
    if (resultA2 == NULL) {
        /* swap width and height */
        resultA2 = meth->new(meth->height(array2), 
                            meth->width(array2), 
                            meth->size(array2));
    }
    
    *(struct Pnm_rgb*) meth->at(resultA2, meth->height(array2) - r - 1, c) =
            *(struct Pnm_rgb*) ptr;

    /*set pixels, width, and height of final image*/
    resultPPM->pixels = resultA2;
    resultPPM->width = meth->width(resultPPM->pixels);
    resultPPM->height = meth->height(resultPPM->pixels);
}

/*
 * rotate_180
 * Behavior:
        This function is called on single pixels.
        Copies pixel from original PPM to appropriate location on new PPM
            for 180 degree rotation.
        The final PPM is passed in a closure (voidCl) along with methods.
        Pixels of the final PPM are set to the rgb values provided in the
            ptr argument.
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
void rotate_180(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl)
{
    assert(voidCl != NULL);
    assert(array2 != NULL);
    assert(ptr != NULL);

    /*access methods and finalPPM from closure argument*/
    struct newCl *cl = voidCl;
    A2Methods_T meth = *(cl->methods);
    Pnm_ppm resultPPM = *(cl->finalPPM);
    A2 resultA2 = resultPPM->pixels;
    if (resultA2 == NULL) {
        resultA2 = meth->new(meth->width(array2), 
                            meth->height(array2), 
                            meth->size(array2));
    }

    int width = meth->width(array2);
    int height = meth->height(array2);
    
    /*set pixels in the final PPM*/
    *(struct Pnm_rgb*) meth->at(resultA2, width - c - 1, height - r - 1) = 
            *(struct Pnm_rgb*) ptr;

    /*set pixels, width, and height of final image*/
    resultPPM->pixels = resultA2;
    resultPPM->width = meth->width(resultPPM->pixels);
    resultPPM->height = meth->height(resultPPM->pixels);
}

/*
 * rotate_270
 * Behavior: 
        This function is called on single pixels.
        Copies pixel from original PPM to appropriate location on new PPM
            for 270 degree rotation.
        The final PPM is passed in a closure (voidCl) along with methods.
        Pixels of the final PPM are set to the rgb values provided in the
            ptr argument.
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
void rotate_270(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl)
{
    assert(voidCl != NULL);
    assert(array2 != NULL);
    assert(ptr != NULL);

    /*access methods and finalPPM from closure argument*/
    struct newCl *cl = voidCl;
    A2Methods_T meth = *(cl->methods);
    Pnm_ppm resultPPM = *(cl->finalPPM);

    A2 resultA2 = resultPPM->pixels;
    if (resultA2 == NULL) {
        /* swap width and height */
        resultA2 = meth->new(meth->height(array2), 
                            meth->width(array2), 
                            meth->size(array2));
    }
    
    /*set pixels in the final PPM*/
    *(struct Pnm_rgb*) meth->at(resultA2, r, meth->width(array2) - c - 1) = 
            *(struct Pnm_rgb*) ptr;

    /*set pixels, width, and height of final image*/
    resultPPM->pixels = resultA2;
    resultPPM->width = meth->width(resultPPM->pixels);
    resultPPM->height = meth->height(resultPPM->pixels);
}

/*
 * flip_horiz
 * Behavior: 
        This function is called on single pixels.
        Copies pixel from original PPM to appropriate location on new PPM
            for a horizontal flip.
        The final PPM is passed in a closure (voidCl) along with methods.
        Pixels of the final PPM are set to the rgb values provided in the
            ptr argument.
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
void flip_horiz(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl)
{
    assert(voidCl != NULL);
    assert(array2 != NULL);
    assert(ptr != NULL);

    /*access methods and finalPPM from closure argument*/
    struct newCl *cl = voidCl;
    A2Methods_T meth = *(cl->methods);
    Pnm_ppm resultPPM = *(cl->finalPPM);
    A2 resultA2 = resultPPM->pixels;
    int width = meth->width(array2);
    if (resultA2 == NULL) {
        resultA2 = meth->new(width, meth->height(array2), meth->size(array2));
    }
    
    /*set pixels in the final PPM*/
    *(struct Pnm_rgb*) meth->at(resultA2, width - c - 1, r) = 
            *(struct Pnm_rgb*) ptr;

    /*set pixels, width, and height of final image*/
    resultPPM->pixels = resultA2;
    resultPPM->width = meth->width(resultPPM->pixels);
    resultPPM->height = meth->height(resultPPM->pixels);
}

/*
 * flip_vert
 * Behavior: 
        This function is called on single pixels.
        Copies pixel from original PPM to appropriate location on new PPM
            for a vertical flip.
        The final PPM is passed in a closure (voidCl) along with methods.
        Pixels of the final PPM are set to the rgb values provided in the
            ptr argument.
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
void flip_vert(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl)
{
    assert(voidCl != NULL);
    assert(array2 != NULL);
    assert(ptr != NULL);

    /*access methods and finalPPM from closure argument*/
    struct newCl *cl = voidCl;
    A2Methods_T meth = *(cl->methods);
    Pnm_ppm resultPPM = *(cl->finalPPM);
    A2 resultA2 = resultPPM->pixels;
    int height = meth->height(array2);
    if (resultA2 == NULL) {
        resultA2 = meth->new(meth->width(array2), height, meth->size(array2));
    }
    
    /*set pixels in the final PPM*/
    *(struct Pnm_rgb*) meth->at(resultA2, c, height - r - 1) = 
            *(struct Pnm_rgb*) ptr;

    /*set pixels, width, and height of final image*/
    resultPPM->pixels = resultA2;
    resultPPM->width = meth->width(resultPPM->pixels);
    resultPPM->height = meth->height(resultPPM->pixels);
}

/*
 * transpose
 * Behavior: 
        This function is called on single pixels.
        Copies pixel from original PPM to appropriate location on new PPM
            for transpose.
        The final PPM is passed in a closure (voidCl) along with methods.
        Pixels of the final PPM are set to the rgb values provided in the
            ptr argument.
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
void transpose(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl)
{
    assert(voidCl != NULL);
    assert(array2 != NULL);
    assert(ptr != NULL);

    /*access methods and finalPPM from closure argument*/
    struct newCl *cl = voidCl;
    A2Methods_T meth = *(cl->methods);
    Pnm_ppm resultPPM = *(cl->finalPPM);

    A2 resultA2 = resultPPM->pixels;
    if (resultA2 == NULL) {
        /* swap width and height */
        resultA2 = meth->new(meth->height(array2), 
                            meth->width(array2), 
                            meth->size(array2));
    }
    
    /*set pixels in the final PPM*/
    *(struct Pnm_rgb*) meth->at(resultA2, r, c) = *(struct Pnm_rgb*) ptr;

    /*set pixels, width, and height of final image*/
    resultPPM->pixels = resultA2;
    resultPPM->width = meth->width(resultPPM->pixels);
    resultPPM->height = meth->height(resultPPM->pixels);
}