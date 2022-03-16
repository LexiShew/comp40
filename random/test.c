#include <stdio.h>

#define MAX_NAME_LEN     20
#define NUM_DESTINATIONS  8

struct Country {
        char         name[MAX_NAME_LEN];
        unsigned int population;
};

struct Country france;
struct Country *country_p;
struct Country countries_to_visit[NUM_DESTINATIONS];

country_p = &france;

int main() {
    char *str = "size: %d";
    printf(str, sizeof(country_p));
}