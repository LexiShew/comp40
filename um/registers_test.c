#include <stdio.h>
#include "registers.h"

int main()
{
    fprintf(stderr, "\n\n---- REGISTERS ARCHITECTURE TESTS ----\n");


    fprintf(stderr, "\nNEW\n");
    Registers_T r0 = Registers_new();
    Registers_T r1 = Registers_new();

    fprintf(stderr, "\nPRINT\n");
    Registers_print(r0);
    Registers_print(r1);

    fprintf(stderr, "\nSET\n");
    Registers_set_reg(r0, 2, 4);
    Registers_set_reg(r0, 1, 6);
    // Registers_set_reg(r0, 8, 1);    // error: out of bounds
    // Registers_set_reg(r0, -1, 1);   // error: out of bounds
    Registers_print(r0);
    Registers_print(r1);


    fprintf(stderr, "\nGET\n");
    fprintf(stderr, "%u\n", Registers_get_reg(r0, 2));
    fprintf(stderr, "%u\n", Registers_get_reg(r0, 1));
    Registers_set_reg(r0, 2, 17);
    Registers_set_reg(r0, 1, 420);
    fprintf(stderr, "%u\n", Registers_get_reg(r0, 2));
    fprintf(stderr, "%u\n", Registers_get_reg(r0, 1));
    // Registers_get_reg(r0, 8);    // error: out of bounds
    // Registers_get_reg(r0, -1);   // error: out of bounds


    fprintf(stderr, "\nFREE\n");
    Registers_free(&r0);
    Registers_free(&r1);


    fprintf(stderr, "\n\n--------------------------------------\n");
    return 0;
}