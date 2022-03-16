/*
    Lexi Shewchuk (ashewc01) and Deanna Oei (doei01)
    Homework 3
    This is the ppmtrans implementation.
    TODO: Summary
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

typedef A2Methods_UArray2 A2;

/* Function Declarations */

typedef void applyFunction(int c, int r, A2 array2, A2Methods_Object *ptr, void *cl); //check if it's A2Methods_Object
applyFunction *transformation;


void readCommands(int argc, char *argv[], int rotation, char *time_file_name);
void printImage();
void run_timer(char *time_file_name);
void stop_timer(char *time_file_name);
Pnm_ppm transform(int rotation, int flip, int transpose, Pnm_ppm origPPM, A2Methods_T methods, A2Methods_mapfun *map);
Pnm_ppm rotate(int rotation, Pnm_ppm origPPM, A2Methods_T methods, A2Methods_mapfun *map);
applyFunction *rotate0;
applyFunction *rotate90;
applyFunction *rotate180;
applyFunction *rotate270;
void rotate_0(int c, int r, A2 array2, A2Methods_Object *ptr, void *cl);
void rotate_90(int i, int j, A2 array2, A2Methods_Object *ptr, void *cl);
void rotate_180(int i, int j, A2 array2, A2Methods_Object *ptr, void *cl);
void rotate_270(int i, int j, A2 array2, A2Methods_Object *ptr, void *cl);
void horizontal();
void vertical();
void transpose();

int main(int argc, char *argv[]) 
{
    char *time_file_name = NULL;
    int   rotation = 0;
    int       flip = 0;

    // CPUTime_T timer;
    FILE *fp = NULL;

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
                    transformation = rotate0;
                }
                if (rotation == 90) {
                    transformation = rotate90;
                }
                if (rotation == 180) {
                    transformation = rotate180;
                }
                if (rotation == 270) {
                    transformation = rotate270;
                }
            }
            if (!(*endptr == '\0')) {    /* Not a number */
                usage(argv[0]);
            }
        else if (strcmp(argv[i], "-flip") == 0) {
            if (!(i + 1 < argc)) {      /* no rotate value */
                flip = 0;
            }
            char *endptr;
            flip = strtol(argv[++i], &endptr, 10);
            if (!(strcmp(argv[i], "horizontal") == 0 || strcmp(argv[i], "vertical") == 0)) {
                fprintf(stderr, 
                    "Flip must be horizontal or vertical\n");
                flip = 0;
            }
            else {
                /* guaranteed to be 0, 90, 180, or 270 based on if conditions */
                if (flip == 0) {
                    transformation = rotate0;
                }
                if (flip == 90) {
                    transformation = rotate90;
                }
                if (rotation == 180) {
                    transformation = rotate180;
                }
                if (rotation == 270) {
                    transformation = rotate270;
                }
            }
            if (!(*endptr == '\0')) {    /* Not a number */
                usage(argv[0]);
            }
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
    printf("1 debug");
    Pnm_ppmwrite(stdout, originalImage); //todo remove

    /*create final image*/
    Pnm_ppm finalImage;
    NEW(finalImage);

    /*transform the images and start timer*/
    run_timer(time_file_name);
    finalImage = transform(rotation, originalImage, methods, map);//int rotation, Pnm_ppm origPPM, A2Methods_T methods, A2Methods_mapfun *map
    stop_timer(time_file_name);

    /*write and free memory*/
    printf("okay 1\n");
    
    Pnm_ppmwrite(stdout, finalImage);
    printf("okay 2\n");
    fclose(fp);
    printf("okay 3\n");
    // CPUTime_Free(&timer);
    Pnm_ppmfree(&originalImage);
    Pnm_ppmfree(&finalImage);

    exit(0);          // the rest of this function is not yet implemented
}

struct newCl {
    A2 newA2;
    A2Methods_T methods;
};

void run_timer(char *time_file_name)
{
    printf("testing run timer. Time file name: %s\n", time_file_name);
}

void stop_timer(char *time_file_name)
{
    printf("testing stop timer. Time file name2: %s\n", time_file_name);
}

Pnm_ppm transform(int rotation, int flip, int transpose, Pnm_ppm origPPM, A2Methods_T methods, A2Methods_mapfun *map)
{
    A2 origA2 = origPPM->pixels;
    A2 resultA2 = methods->new_with_blocksize(methods->width(origA2),
                                            methods->height(origA2),
                                            methods->size(origA2),
                                            methods->blocksize(origA2));
    
    /*go through rotations*/
    if (rotation == 0) {
        printf("calling map using rotate0\n");
        struct newCl cl = {resultA2, methods};
        map(origA2, rotate_0, &cl);
    }
    if (rotation == 90) {
        //set dimensions
        printf("calling map using rotate90\n");
        map(origA2, rotate_90, resultA2);
    }
    if (rotation == 180) {

        printf("calling map using rotate180\n");
        map(origA2, rotate_180, resultA2);
    }
    if (rotation == 270) {
        //set dimensions
        printf("calling map using rotate270\n");
        map(origA2, rotate_270, resultA2);
    }

    /*go through flips*/
    /*
    if (flip horizontal) {
        map(origA2, horizontal_flip, &cl);
    }
    if (flip vertical) {
        map(origA2, vertical_flip, &cl);
    }
    */

    /*go through transpose*/

    Pnm_ppm resultPPM;
    NEW(resultPPM);
    resultPPM->width = origPPM->methods->width(resultA2);
    resultPPM->height = origPPM->methods->height(resultA2);
    resultPPM->denominator = origPPM->denominator;
    resultPPM->pixels = origPPM->pixels;
    resultPPM->methods = origPPM->methods;
    return resultPPM;
}

// @Deanna A2Methods_Object represents the current element, not methods

void rotate_0(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl)
{
    (void) ptr;
    assert(voidCl != NULL);
    assert(array2 != NULL);

    // struct newCl clStruct = *(struct newCl*) cl;
    struct newCl cl = *(struct newCl*) voidCl;

    A2 finalA2 = cl.newA2;
    printf("in rotate0\n");
    assert(array2 != NULL);

    // A2Methods_T meth = cl.methods;
    // if (meth != NULL) {
    //     printf("meth:%u\n", meth);
    // }

    printf("c: %d, r: %d\n", c, r);

    void* plsWork = cl.methods->at(array2, c, r);
    if (plsWork == NULL) {
        printf("Works!\n");
    }

    printf("orig pixel: %d\n", *(int*) cl.methods->at(array2, c, r));
    printf("final pixel: %d\n", *(int*) cl.methods->at(finalA2, c, r));
    *(int*) cl.methods->at(finalA2, c, r) = *(int*) cl.methods->at(array2, c, r);
    printf("debug debug\n");

    printf("Testing: %d\n", *(int*) cl.methods->at(cl.newA2, c, r));
}

void rotate_90(int i, int j, A2 array2, A2Methods_Object *ptr, void *cl)
{
    (void) i;
    (void) j;
    (void) array2;
    (void) ptr;
    (void) cl;
//     printf("in rotate90\n");
//     assert(array2 != NULL);
//     *(A2*) methods->at(cl, i, j) = methods->at(array2, i, j);

//     // for (int c = 0; c < A2_width(array2); c++) {
//     //     for (int r = 0; r < A2_height(array2); r++) {
            
//     //     }
//     // }
}

void rotate_180(int c, int r, A2 array2, A2Methods_Object *ptr, void *cl)
{
    (void) c;
    (void) r;
    (void) array2;
    (void) ptr;
    (void) cl;
}

void rotate_270(int c, int r, A2 array2, A2Methods_Object *ptr, void *cl)
{
    (void) c;
    (void) r;
    (void) array2;
    (void) ptr;
    (void) cl;
}