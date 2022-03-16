/*
    Lexi Shewchuk (ashewc01) and Deanna Oei (doei01)
    Homework 3
    This is the ppmtrans implementation. 
    It allows users to provide a ppm file and specific transformations
    to be performed. It also keeps track how long each transformation
    takes and gives the option to write it to a file.
    Utilizes transformation functions declared and defined in
    transformations.h and transformations.c.
*/

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

#define SET_METHODS(METHODS, MAP, WHAT) do {            \
    methods = (METHODS);                                \
    assert(methods != NULL);                            \
    map = methods->MAP;                                 \
    if (map == NULL) {                                  \
        fprintf(stderr, "%s does not support "          \
                WHAT "mapping\n",                       \
                argv[0]);                               \
        exit(1);                                        \
    }                                                   \
} while (0)

static void usage(const char *progname)
{
    fprintf(stderr, "Usage: %s [-rotate <angle>] "
            "[-{row,col,block}-major] [filename]\n",
            progname);
    exit(1);
}

/* Function Declarations */

A2Methods_applyfun *transformation;

void readCommands(int argc, char *argv[], int rotation, char *time_file_name);
void printImage();
Pnm_ppm transform(A2Methods_applyfun appFunc, Pnm_ppm origPPM,
                                A2Methods_T *methods, A2Methods_mapfun *map);
void write_time(char* time_file_name, double time_used, FILE *time_file, 
                Pnm_ppm ppm_image, char* trans_type, int rotation);

int main(int argc, char *argv[]) 
{
    int   rotation = 0;

    CPUTime_T timer = CPUTime_New();
    char *time_file_name = NULL;
    FILE *time_file = NULL;
    FILE *fp = NULL;

    char* trans_type = NULL;

    /* default to UArray2 methods */
    A2Methods_T methods = uarray2_methods_plain; 
    assert(methods);

    /* default to best map */
    A2Methods_mapfun *map = methods->map_default; 
    assert(map);

    /*read in commands and arguments*/
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-row-major") == 0) {
            SET_METHODS(uarray2_methods_plain, map_row_major, "row-major");
        } else if (strcmp(argv[i], "-col-major") == 0) {
            SET_METHODS(uarray2_methods_plain, map_col_major, "column-major");
        } else if (strcmp(argv[i], "-block-major") == 0) {
            SET_METHODS(uarray2_methods_blocked, map_block_major, "block-major");
        } else if (strcmp(argv[i], "-rotate") == 0) {
            if (!(i + 1 < argc)) {      /* no rotate value */
                usage(argv[0]);
            }
            trans_type = "Rotate";
            char *endptr;
            rotation = strtol(argv[++i], &endptr, 10);
            if (!(rotation == 0 || rotation == 90 ||
                rotation == 180 || rotation == 270)) {
                fprintf(stderr, 
                    "Rotation must be 0, 90 180 or 270\n");
                usage(argv[0]);
            }
            else {
                /* guaranteed to be 0, 90, 180, or 270 based on if conditions */
                if (rotation == 0) {
                    transformation = &rotate_0;
                }
                if (rotation == 90) {
                    transformation = &rotate_90;
                }
                if (rotation == 180) {
                    transformation = &rotate_180;
                }
                if (rotation == 270) {
                    transformation = &rotate_270;
                }
            }
            if (!(*endptr == '\0')) {    /* Not a number */
                usage(argv[0]);
            }
        } else if (strcmp(argv[i], "-flip") == 0) {
            if (strcmp(argv[i+1], "horizontal") == 0) {
                trans_type = "Horizontal flip";
                transformation = &flip_horiz;
            } 
            else if (strcmp(argv[i+1], "vertical") == 0){
                trans_type = "Vertical flip";
                transformation = &flip_vert;
            } 
            else {
                fprintf(stderr, "Flip must be horizontal or vertical\n");
                usage(argv[0]);
            }
            i++;
        } else if (strcmp(argv[i], "-transpose") == 0) {
            trans_type = "Transpose";
            transformation = &transpose;
        } else if (strcmp(argv[i], "-time") == 0) {
            time_file_name = argv[++i];
        } else if (*argv[i] == '-') {
            fprintf(stderr, "%s: unknown option '%s'\n", argv[0],
                argv[i]);
            usage(argv[0]);
        } else if (argc - i > 1) {
            fprintf(stderr, "Too many arguments\n");
            usage(argv[0]);
        } else {
            fp = fopen(argv[i], "rb");
        }
    }
    /*read in from file or stdin*/
    if (fp == NULL) {
        fp = stdin;
    }

    /*create original image*/
    Pnm_ppm originalImage = Pnm_ppmread(fp, methods);

    /*transform the image and start timer*/
    CPUTime_Start(timer);
    Pnm_ppm finalImage = transform(transformation, 
                                    originalImage, 
                                    &methods, map);
    double time_used = CPUTime_Stop(timer);
    write_time(time_file_name, time_used, time_file, 
                finalImage, trans_type, rotation);

    /*write and free memory */     
    Pnm_ppmwrite(stdout, finalImage);
    fclose(fp);
    CPUTime_Free(&timer);
    Pnm_ppmfree(&originalImage);
    Pnm_ppmfree(&finalImage);

    exit(0);
}

/*
 * write_time
 * Behavior: 
        Writes time used for a transformation to a file.
 * Parameters: 
        char* time_file_name - name of the file to write to
        double time_used -  time used for a transformation
        FILE *time_file - file to write to
        Pnm_ppm ppm_image - the final ppm_image
        char* trans_type - name of transformation type
        int rotation - degree rotation (used only for rotations)
 * Returns: none
 * Expectations/errors: 
        time_file_name should not be null
 */
void write_time(char* time_file_name, double time_used, FILE *time_file, 
                Pnm_ppm ppm_image, char* trans_type, int rotation)
{
    if (time_file_name == NULL) {
        return;
    }

    int total_pixels = ppm_image->height * ppm_image->width;

    time_file = fopen(time_file_name, "a");
    fprintf(time_file, "\n");
    if (strcmp(trans_type, "Rotate") == 0) {
        fprintf(time_file, 
                "Rotation %d was performed in %.0f nanoseconds\n", 
                rotation, time_used);
    } 
    else {
        fprintf(time_file, 
                "%s was performed in %.0f nanoseconds\n", 
                trans_type, time_used);
    }
    fprintf(time_file, "Total number of pixels: %d\n", total_pixels);
    fprintf(time_file, 
            "Time per Pixel: %.0f nanoseconds\n", 
            time_used/total_pixels);
    fclose(time_file);
}

/*
 * transform
 * Behavior: 
        Takes in original ppm file, performs a given transformation,
        and returns a new ppm file which is a transformed version 
        of the original
 * Parameters: 
        A2Methods_applyfun appFunc - function to be applied with mapping
        Pnm_ppm origPPM - the original pnm_ppm file
        A2Methods_T *methods - methods suite
        A2Methods_mapfun *map - mapping function
 * Returns: Pnm_ppm - the final, transformed image
 * Expectations/errors: 
        time_file_name should not be null
 */
Pnm_ppm transform(A2Methods_applyfun appFunc, Pnm_ppm origPPM, 
        A2Methods_T *methods, A2Methods_mapfun *map)
{
    A2 origA2 = origPPM->pixels;

    Pnm_ppm resultPPM;
    NEW(resultPPM);
    resultPPM->methods = origPPM->methods;
    resultPPM->denominator = origPPM->denominator;
    resultPPM->pixels = NULL;

    struct newCl *cl;
    NEW(cl);
    cl->methods = methods;
    cl->finalPPM = &resultPPM;

    map(origA2, appFunc, cl);
    
    FREE(cl);
    return resultPPM;
}