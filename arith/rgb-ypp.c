/**************************************************************
 *
 *                     rgb-ypp.c
 *
 * Assignment: Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 27, 2021
 *     
 * Contains implementations to convert rgb values to component
 * video representation and back.
 * Function implementations include:
 *      normalize
 *      convert_RGB_to_YPP
 *      range
 *      convert_YPP_to_RGB
 *      rgb_to_ypp_A2
 *      ypp_to_rgb_A2
 *      rgb_to_ypp_apply
 *      ypp_to_rgb_apply
 *
 **************************************************************/

#include "rgb-ypp.h"
#include <stdio.h>
#include "pnm.h"
#include "a2methods.h"
#include "a2plain.h"
#include <mem.h>
#include <assert.h>

typedef A2Methods_UArray2 A2;

/*
 * Rgb_struct
 * a struct containing rgb float values between 0 and 1
 */
typedef struct Rgb_struct 
{
    float red;
    float green;
    float blue;
} *Rgb_struct;

/* function declarations */
Rgb_struct normalize(Pnm_rgb rgb_scaled, int denom);
Pnm_rgb convert_YPP_to_RGB(Ypp_struct ypp);
Ypp_struct convert_RGB_to_YPP(Pnm_rgb rgb, int denom);
void rgb_to_ypp_apply(int i, int j, A2 rgb_A2, void *elem, void *ypp_A2);
void ypp_to_rgb_apply(int i, int j, A2 ypp_A2, void *elem, void *rgb_A2);
int range(float curr_val);

/*
 * normalize
 * Behavior: converts from a Pnm_rgb of integer values to an Rgb_struct of 
 *      float values between 0 and 1
 * Parameters:
 *      Pnm_rgb rgb_scaled: the original Pnm_rgb struct that's to be scaled
 *      int denom: the denominator of the Pnm_ppm that contains the Pnm_rgb
 * Returns: Rgb_struct: a struct containing floats between 0 and 1 for 
 *      red, gree, and blue values
 */
Rgb_struct normalize(Pnm_rgb rgb_scaled, int denom)
{
    float d = denom;
    Rgb_struct new_rgb;
    NEW(new_rgb);
    new_rgb->red = rgb_scaled->red / d;
    new_rgb->green = rgb_scaled->green / d;
    new_rgb->blue = rgb_scaled->blue / d;
    return new_rgb;
}

/*
 * convert_RGB_to_YPP
 * Behavior: converts a Pnm_rgb to component video color 
        space struct (Ypp_struct)
 * Parameters: 
        Pnm_rgb rgb pixels
        integer denominator
 * Returns: Ypp_struct (component video color space)
 * Expectations/errors: 
        rgb is not null
        denom is greater than 0
 */
Ypp_struct convert_RGB_to_YPP(Pnm_rgb rgb, int denom) 
{
    assert(rgb != NULL);
    assert(denom > 0);

    /*new rgb_struct*/
    Rgb_struct new_rgb = normalize(rgb, denom);

    float r = new_rgb->red;
    float g = new_rgb->green;
    float b = new_rgb->blue;

    Ypp_struct ypp;
    NEW(ypp);

    ypp->y  = 0.299     * r + 0.587    * g + 0.114    * b;
    ypp->pb = -0.168736 * r - 0.331264 * g + 0.5      * b;
    ypp->pr = 0.5       * r - 0.418688 * g - 0.081312 * b;

    FREE(new_rgb);

    return ypp;
}

/*
 * range
 * Behavior: helper function to check if an rgb float is within 
        range and casts it as an integer within range for an RGB value
 * Parameters: float to be checked
 * Returns: int that clamps any values greater than 255 to 255, or less than
 *      0 to 0
 */
int range(float curr_val)
{
    if (curr_val < 0) {
        return 0; 
    }
    else if (curr_val > 255) {
        return 255;
    }
    else {
        return (int) curr_val;
    }
}

/*
 * convert_YPP_to_RGB
 * Behavior: converts Ypp_struct to Pnm_rgb
 * Parameters: Ypp_struct
 * Returns: Pnm_rgb converted from Ypp_struct
 * Expectations/errors: ypp is not null
 */
Pnm_rgb convert_YPP_to_RGB(Ypp_struct ypp) 
{
    assert(ypp != NULL);

    float y = ypp->y;
    float pb = ypp->pb;
    float pr = ypp->pr;
    
    Pnm_rgb rgb;
    NEW(rgb);

    rgb->red =   range((1.0 * y + 0.0      * pb + 1.402    * pr) * 255);
    rgb->green = range((1.0 * y - 0.344136 * pb - 0.714136 * pr) * 255);
    rgb->blue =  range((1.0 * y + 1.772    * pb + 0.0      * pr) * 255);

    return rgb;
}


/*
 * specialCl struct:
 * both the resulting A2 of Ypp_structs and the denominator of the PPM are
 * needed in the mapping of rgb_A2, so this struct contains both :)
 */
struct specialCl {
    A2 ypp_A2;
    int denom;
};

/*
 * rgb_to_ypp_A2
 * Behavior: converts an rgb_A2 to a ypp_A2 by using
 *     apply function rgb_to_ypp_apply with row major mapping
 * Parameters: 
        A2 rgb_A2: A2 containing Pnm_rgb structs
        int denom: the denominator of the PPM
 * Returns: A2 containing Ypp_structs
 * Expectations/errors: rgb_A2 should not be null
 */
A2 rgb_to_ypp_A2(A2 rgb_A2, int denom) 
{
    assert(rgb_A2 != NULL);
    int width = uarray2_methods_plain->width(rgb_A2);
    int height = uarray2_methods_plain->height(rgb_A2);

    A2 ypp_A2 = uarray2_methods_plain->new(width, height, 
                                            sizeof(struct Ypp_struct));
    struct specialCl closure = { &ypp_A2, denom };

    uarray2_methods_plain->map_default(rgb_A2, rgb_to_ypp_apply, &closure);

    return ypp_A2;
}

/*
 * ypp_to_rgb_A2
 * Behavior: convert A2 of ypp values to an A2 of rgb values by using
 *     apply function ypp_to_rgb_apply with row major mapping
 * Parameters: 
        A2 ypp_A2: A2 of Ypp_structs to be converted to Pnm_rgb structs
 * Returns: A2 of Pnm_rgb structs
 * Expectations/errors: ypp_A2 should not be null
 */
A2 ypp_to_rgb_A2(A2 ypp_A2) 
{
    assert(ypp_A2 != NULL);
    int width = uarray2_methods_plain->width(ypp_A2);
    int height = uarray2_methods_plain->height(ypp_A2);

    A2 rgb_A2 = uarray2_methods_plain->new(width, height, 
                                            sizeof(struct Pnm_rgb));
    uarray2_methods_plain->map_default(ypp_A2, ypp_to_rgb_apply, rgb_A2);
    return rgb_A2;
}

/*
 * rgb_to_ypp_apply
 * Behavior: apply function that converts rgb value to ypp
        applied to each element in an rgb_A2
 * Parameters: 
        int i: column of rgb_A2
        int j: row of rgb_A2
        A2 rgb_A2: the A2 containing Pnm_rgb structs
        void *elem: the current Pnm_rgb to be converted
        void *closure: the special closure that has the ypp_A2 and denominator
 * Returns: none
 * Expectations/errors: elem and closure should not be null
 */
void rgb_to_ypp_apply(int i, int j, A2 rgb_A2, void *elem, void *closure) 
{
    assert(elem != NULL);
    assert(closure != NULL);
    /* elem is a pnm_rgb struct. get the rbg values, convert to ypp, 
    and insert that struct into the new ypp_A2 at (i,j)*/
    (void) rgb_A2;
    struct specialCl cl = *(struct specialCl*) closure;
   
    Ypp_struct ypp = convert_RGB_to_YPP(elem, cl.denom);

    *(Ypp_struct) uarray2_methods_plain->at(*(A2*) (cl.ypp_A2), i, j) = *ypp;

    FREE(ypp);
}

/*
 * ypp_to_rgb_apply
 * Behavior: apply function that converts ypp value to rgb
        applied to each element in a ypp_A2
 * Parameters: 
        int i: column of ypp_A2
        int j: row of ypp_A2
        A2 ypp_A2: A2 containing Ypp_structs
        void *elem: the current Ypp_struct
        void *rgb_A2: the ypp_A2 that will contain the newly made Ypp_structs
 * Returns: none
 * Expectations/errors: elem and rgb_A2 should not be null
 */
void ypp_to_rgb_apply(int i, int j, A2 ypp_A2, void *elem, void *rgb_A2)
{
    (void) ypp_A2;
   
    Pnm_rgb rgb = convert_YPP_to_RGB(elem);

    *(Pnm_rgb) uarray2_methods_plain->at(rgb_A2, i, j) = *rgb;
    FREE(rgb);
}