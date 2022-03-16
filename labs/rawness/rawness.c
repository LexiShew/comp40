#include <stdio.h>
#include "pnmrdr.h"


int main(int argc, char *argv[]) {
    /* file is given in arguments */
    FILE *file;
    if (argc == 1) {  
        file = stdin;
    } 
    else if (argc == 2) { 
        file = fopen(argv[1], "rb");
    } 
    else {
        /* throw argument error */
        printf("insufficient arguments\n");
        return 0;
    }

    if (file == NULL) {
        printf("file not found\n");
        return 0;
    } 
    else {
        // printf("found file\n");
        // fclose(file);
        
    }


    /* read files */
    Pnmrdr_T reader = Pnmrdr_new(file);

    Pnmrdr_mapdata mapdata = Pnmrdr_data(reader);
    printf("P5\n");
    printf("%u ", mapdata.width);
    printf("%u\n", mapdata.height);
    printf("%u\n", mapdata.denominator);

    for (int i = 0; i < (int) mapdata.width; i++) {
        for (int j = 0; j < (int) mapdata.height; j++) {
            unsigned data = Pnmrdr_get(reader);
            printf("%c", (char) data);
        }
    }


    fclose(file);

    return 0;
}