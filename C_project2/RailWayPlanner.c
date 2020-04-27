//
// Implements the algorithm for minimal price railway, using dynamic programing
//
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_LINE_LENGTH 1024
char *gline;

void openFile(char *arr)
{
    FILE *file = fopen(arr, (const char *) 'r');
    gline = fgets(gline, MAX_LINE_LENGTH, file);
    printf("1st line is: %s", gline);
}

int main(argc,(char**)argv[1])
{
    openFile(argv[1]);
    return 0;
}

