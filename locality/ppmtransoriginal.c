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

// typedef void applyFunction(int c, int r, A2 array2, A2Methods_Object *ptr, void *cl); //check if it's A2Methods_Object
A2Methods_applyfun *transformation;


void readCommands(int argc, char *argv[], int rotation, char *time_file_name);
void printImage();
void run_timer(char *time_file_name);
void stop_timer(char *time_file_name);
void set_final_dimensions(Pnm_ppm origPPM, Pnm_ppm *finalPPM, int rotation, A2Methods_applyfun *trans);
Pnm_ppm transform(A2Methods_applyfun *appFunc, /*int rotation,*/ Pnm_ppm origPPM, Pnm_ppm *finalPPM, A2Methods_T *methods, A2Methods_mapfun *map);
// Pnm_ppm rotate(int rotation, Pnm_ppm origPPM, A2Methods_T methods, A2Methods_mapfun *map);
A2Methods_applyfun *rotate0;
A2Methods_applyfun *rotate90;
A2Methods_applyfun *rotate180;
A2Methods_applyfun *rotate270;
A2Methods_applyfun *horizontal;
A2Methods_applyfun *vertical;
A2Methods_applyfun *transpose;
//TODO i think the following should be in a diff header?
// void rotate_0(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl);
// void rotate_90(int i, int j, A2 array2, A2Methods_Object *ptr, void *voidCl);
// void rotate_180(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl);
// void rotate_270(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl);
// void horizontal_flip(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl);
// void vertical_flip(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl);
// void transpose_pix(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl);

int main(int argc, char *argv[]) 
{
    char *time_file_name    = NULL;
    int   rotation          = 0;
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
        } else if (strcmp(argv[i], "-flip") == 0) {
            if (strcmp(argv[i+1], "horizontal") == 0) {
                transformation = horizontal;
            } 
            else if (strcmp(argv[i+1], "vertical") == 0){
                transformation = vertical;
            } 
            else {
                fprintf(stderr, "Flip must be horizontal or vertical\n");
                usage(argv[0]);
            }
            i++;
        } else if (strcmp(argv[i], "-transpose") == 0) {
            transformation = transpose;
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
    printf("1 read in the original image\n");
    Pnm_ppmwrite(stdout, originalImage); //todo remove
    printf("2 printed out original image\n");

    /*create final image*/
    Pnm_ppm finalImage;
    NEW(finalImage);
    finalImage->denominator = originalImage->denominator;
    finalImage->methods = methods;
    Pnm_ppm *finalImagePtr = &finalImage;
    printf("3 create final image\n");

    set_final_dimensions(originalImage, finalImagePtr, rotation, transformation);
    finalImage->pixels = methods->new_with_blocksize(finalImage->width, 
                                    finalImage->height, 
                                    methods->size(originalImage->pixels),
                                    methods->blocksize(originalImage));
    printf("3.5 set final dimensions\n");

    /*transform the images and start timer*/
    run_timer(time_file_name);
    finalImage = transform(transformation, /*rotation,*/ originalImage, finalImagePtr, &methods, map);//int rotation, Pnm_ppm origPPM, A2Methods_T methods, A2Methods_mapfun *map
    stop_timer(time_file_name);

    /*write and free memory*/
    printf("4 finished transform\n");
    Pnm_ppmwrite(fopen("test1outR180.ppm", "r+"), finalImage);
    Pnm_ppmwrite(stdout, finalImage);
    printf("5 printed out final image 2\n");
    fclose(fp);
    printf("6 closed fp\n");
    // CPUTime_Free(&timer);
    Pnm_ppmfree(&originalImage);
    printf("7 free original image\n");
    Pnm_ppmfree(&finalImage);
    printf("8 free final image\n");

    exit(0);          // the rest of this function is not yet implemented
}

struct newCl {
    A2 *newA2;
    // A2Methods_T methods;
    A2Methods_T *methods;
};


void run_timer(char *time_file_name)
{
    printf("testing run timer. Time file name: %s\n", time_file_name);
}

void stop_timer(char *time_file_name)
{
    printf("testing stop timer. Time file name2: %s\n", time_file_name);
}

void set_final_dimensions(Pnm_ppm origPPM, Pnm_ppm *finalPPM, int rotation, A2Methods_applyfun *trans)
{
    int originalWidth = origPPM->width;
    int originalHeight = origPPM->height;

    (void) trans;

    if (rotation == 90 || rotation == 270) {
        printf("rotating 90 or 270 or transpose\n"); //TODO add transpose
        (*finalPPM)->width = originalHeight;
        (*finalPPM)->height = originalWidth;
    }
    else {
        printf("dimensions stay the same!\n");
        (*finalPPM)->width = originalWidth;
        (*finalPPM)->height = originalHeight;
    }
    printf("final image width: %d\n", (*finalPPM)->width);
    printf("final image height: %d\n", (*finalPPM)->height);
}

Pnm_ppm transform(A2Methods_applyfun *appFunc, /*int rotation,*/ Pnm_ppm origPPM, Pnm_ppm *finalPPM, A2Methods_T *methods, A2Methods_mapfun *map)
{
    A2 *origA2 = origPPM->pixels;
    A2 resultA2 = (*finalPPM)->pixels;

    struct newCl cl = { &resultA2, methods };
    printf("okay 1\n");
    // seg fault here
    map(origA2, appFunc, &cl);

    
    /*go through rotations*/
    // if (rotation == 0) {
    //     printf("calling map using rotate0\n");
    //     struct newCl cl = {resultA2, methods};
    //     map(origA2, rotate_0, &cl);
    // }
    // if (rotation == 90) {
    //     //set dimensions
    //     printf("calling map using rotate90\n");
    //     struct newCl cl = {resultA2, methods};
    //     map(origA2, rotate_90, &cl);
    // }
    // if (rotation == 180) {

    //     printf("calling map using rotate180\n");
    //     struct newCl cl = {resultA2, methods};
    //     map(origA2, rotate_180, &cl);
    // }
    // if (rotation == 270) {
    //     //set dimensions
    //     printf("calling map using rotate270\n");
    //     struct newCl cl = {resultA2, methods};
    //     map(origA2, rotate_270, &cl);
    // }

    /*go through flips*/
    
    // if (flip horizontal) { //TODO get conditional
        // printf("Doing horizontal now\n");
        // struct newCl cl = {resultA2, methods};
        // map(origA2, horizontal_flip, &cl);
    // }
    // if (flip vertical) { //TODO get conditional
        // printf("Doing vertical now\n");
        // struct newCl cl = {resultA2, methods};
        // map(origA2, vertical_flip, &cl);
    // }

    /*check transpose*/
    /*
    if (transpose) {
        map(origA2, transpose_pix, &cl);
    }
    */
    return *finalPPM;
}


// void rotate_0(int c, int r, A2 array2, A2Methods_Object *ptr, void *voidCl)
// {
//     printf("in rotate0\n");
//     printf("    c: %d, r: %d\n", c, r);
//     (void) ptr;
//     assert(voidCl != NULL);
//     assert(array2 != NULL);

//     struct newCl *cl = voidCl;
//     A2Methods_T meth = *(cl->methods);

//     // Pnm_ppm resultPPM = 
//     A2 resultA2 = *(cl->newA2);
//     (void) resultA2;
    
//     void* plsWork = meth->at(array2, c, r);
//     if (plsWork != NULL) {
//         printf("Works!\n");
//     }
    
//     // printf("orig pixel: %d\n", *(int*) cl.methods->at(array2, c, r));
//     // printf("final pixel: %d\n", *(int*) cl.methods->at(finalA2, c, r));
//     // *(int*) cl.methods->at(finalA2, c, r) = *(int*) cl.methods->at(array2, c, r);
//     // printf("debug debug\n");

//     // printf("Testing: %d\n", *(int*) cl.methods->at(cl.newA2, c, r));
// }