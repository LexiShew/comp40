/**************************************************************
 *
 *                     charextraction.c
 *
 *     Assignment: Homework 1
 *     Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 *     Date: Sept 21 2021
 *
 *     summary
 *     Interface of character extraction program, which helps
 *     parse integers and numbers.
 *     
 * 
 *
 **************************************************************/


#include "charextraction.h"

bool isNum(char current)
{
    if (current >= '0' && current <= '9') {
        return true;
    }
    return false;
}

char *extractNumbers(char *allChars, int *numsLength)
{
    //printf("----------ENTERING EXTRACT NUMBERS------------\n");
    

    int i = 0;
    char currChar = allChars[i];
    
    char *numArray = malloc(1000);
    bool numCreated = false;
    
    int arrIndex = 0;
    int number = 0;

    
    while (currChar != '\n') {

        numCreated = false;
        while (isNum(currChar)) {
            number = number * 10 + currChar - '0';
            i++;
            currChar = allChars[i];
            numCreated = true;
        }
        if (numCreated == true) {
            //printf("Here is the new number: %d\n", number);
            numArray[arrIndex] = (char) number;
            //printf("But this is whats saved: %c\n", numArray[arrIndex]);
            number = 0; 
            arrIndex ++;
        }
        

        if (currChar == '\n') {
            break;
        }
        i++; 
        currChar = allChars[i];
    }
    
    // numArray[arrIndex] = '\0';
    /*
    for (int j = 0; j < 10; j++) {
        if ( numArray[j] == '\0') {
             printf("Found the null character at index %d\n",j);
        } 
        if ( numArray[j] == ' ')  {
            printf("Found the space!\n");
        }
    } */

    //printf("\n Array of extracted numbers: %s\n", numArray);
    //printf("----------EXITING EXTRACT NUMBERS-------------\n");
    *numsLength = arrIndex;
    return numArray;
}

char *extractLetters (char *allChars, int *lettersLength)
{
    char *onlyLetters = malloc(1000);
    int lettIndex = 0;
    int i = 0;
    char currChar;
    currChar = allChars[i];
    
    while (currChar != '\n') {
        
        if (currChar < '0' || currChar > '9') {
            onlyLetters[lettIndex] = currChar;
            lettIndex++;
        }
        i++;
        currChar = allChars[i];
    }
    *lettersLength = lettIndex + 1;
    return onlyLetters;
}

size_t stringSize(const char *str)
{
    int size = 0;
    char currChar = str[0];
    while (currChar != '\0') {
        size++;
        currChar = str[size];
    }
    return size;
}