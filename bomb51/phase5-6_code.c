#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void explode_bomb();
extern int *read_six_numbers(char input[]);



/* 
 * phase_5
 * Purpose: this function represents a 
 * Inputs: the input from the fifth line of the input file
 * Exceptions/errors: bomb explodes if there're less than 2 inputs and if
 *      more or less than 10 indices are looked at
 */      
void phase_5(char input[])
{
    /* start by reading in the start_index and final sum from inputs */
    int start_index;
    int sum;
    if (sscanf(input, "%d %d", &start_index, &sum) <= 1) {
        explode_bomb();
    }

    int arr[16] = { 10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6, 5 };

    int counter = 0;      /* edx is the counter (must get to 10) */
    int index = start_index;
    int total = 0;
    while (arr[index] != 15) {   /* loop breaks when arr[index] = 15 */
        total += arr[index];
        index = arr[index];
        counter++;
    }

    if (counter != 10) {
        explode_bomb();
    }
}



struct node {
    const int key;
    const int val;
    struct node *next;
};

static struct node node6 = {
    6, 723, NULL
};

static struct node node5 = {
    5, 608, &node6
};

static struct node node4 = {
    4, 408, &node5
};

static struct node node3 = {
    3, 825, &node4
};

static struct node node2 = {
    2, 677, &node3
};

static struct node node1 = {
    1, 270, &node2
};


/* phase_6
 * Description: takes in 6 integers, makes sure none are the same, then
 *      creates enums for all six integers, then makes sure that the
 *      integers are inputted in decreasing order in terms of their enums
 * Input: the input from the sixth line of the input file
 * Errors/exceptions: bomb explodes if any of the integers are the same,
 *      if the enums aren't in decreasing order
 */
void phase_6(char input[])
{
    int *six_nums = read_six_numbers(input);
    for (int i = 0; i < 6; i++) {
        for (int j = i; j < 6; j++) {
            if (*(six_nums + i) == *(six_nums + j)) {
                explode_bomb();         /* make sure no inputs are the same */
            }
        }
    }

/*
    confusion:
    * void pointers are stored 8 bytes apart in mem
    * when these pointers are defeferenced, they're our big values
    * so the values aren't stored contiguously, but the pointers are
    * 

*/
    struct node *curr_node = &node1;
    /* get the linked list node we want */
    while (curr_node->key != *six_nums) {
        curr_node = curr_node->next;
    }

    /* make sure that OUR inputs are in an order such that linked list values
            are accessed in decreasing order */
    for (int i = 1; i < 6; i++) {
        struct node *temp = curr_node;
        while (temp->key != *(six_nums + i)) {
            temp = temp->next;
        }
        if (curr_node->val < temp->val) {
            explode_bomb();
        }
    }
}