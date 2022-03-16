/**************************************************************
 *
 *                     ppmdiff.c
 *
 * Assignment: Lab for Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 15, 2021
 *     
 * This program compres 2 images to estimate how similar 
 * they are.
 * Prints to standard output a single number which is the
 * measure of difference between 2 input images.
 *
 **************************************************************/

#include <stdio.h>
#include <string.h>
#include "pnm.h"
#include "a2methods.h"
#include "a2plain.h"
#include "uarray2.h"
#include <mem.h>
#include <math.h>
#include <assert.h>

void checkFiles(int argc, char *argv[], FILE **fp1, FILE **fp2);

int main(int argc, char *argv[])
{
    A2Methods_T methods = uarray2_methods_plain;
    
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;

    checkFiles(argc, argv, &fp1, &fp2);

    assert(!(fp1 == NULL || fp2 == NULL));

    Pnm_ppm ppm1 = Pnm_ppmread(fp1, methods);
    Pnm_ppm ppm2 = Pnm_ppmread(fp2, methods);

    fclose(fp1);
    fclose(fp2);

    
    if (fabs((double) ppm1->width - (double)ppm2->width) > 1) {
        return 0;
    }
    if (fabs((double) ppm1->height - (double)ppm2->height) > 1) {
        return 0;
    }

    int w =  ppm1->width < ppm2->width ? ppm1->width : ppm2->width; 
    int h =  ppm1->height < ppm2->height ? ppm1->height : ppm2->height; 
    
    double sum = 0;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {      
            Pnm_rgb pixel1 = (Pnm_rgb) (methods->at(ppm1->pixels, i, j));
            Pnm_rgb pixel2 = (Pnm_rgb) (methods->at(ppm2->pixels, i, j));
            double d1 = ppm1->denominator;
            double d2 = ppm2->denominator;


            double r1 = (pixel1->red)   / d1;
            double g1 = (pixel1->green) / d1;
            double b1 = (pixel1->blue)  / d1;
            double r2 = (pixel2->red)   / d2;
            double g2 = (pixel2->green) / d2;
            double b2 = (pixel2->blue)  / d2;
    
            sum +=  ((r1 - r2) * (r1 - r2)) +
                    ((g1 - g2) * (g1 - g2)) +
                    ((b1 - b2) * (b1 - b2));
        }
    }
    
    double error = sqrt(sum / (3.0 * w * h));
    printf("ERROR: %f\n", error);

    Pnm_ppmfree(&ppm1);
    Pnm_ppmfree(&ppm2);

}

/*
 * checkFiles
 * Behavior: ensure files provided are valid
 * Parameters: 
 *      int argc 
 *      char *argv[]
 *      FILE **fp1
 *      FILE **fp2
 * Returns: none
 * Expectations/errors: none
 */
void checkFiles(int argc, char *argv[], FILE **fp1, FILE **fp2) {
    printf("argc = %d\n", argc);
    (void) argv;

    if (argc != 3) {
        printf("Invalid Arguments -- must provide two images\n");
        return;
    }

    char *image1 = argv[1];
    char *image2 = argv[2];

    if (strcmp(image1, "-") == 0 && strcmp(image2, "-") != 0) {
        *fp1 = stdin;
    }
    if (strcmp(image2, "-") == 0 && strcmp(image1, "-") != 0) {
        *fp2 = stdin;
    }

    if (*fp1 == NULL) {
        *fp1 = fopen(image1, "r");
        if (*fp1 == NULL) {
            printf("File 1 is null\n");
            return;
        }
    }

    if (*fp2 == NULL) {
        *fp2 = fopen(image2, "r");
        if (*fp2 == NULL) {
            printf("File 2 is null\n");
            return;
        }
    }
}