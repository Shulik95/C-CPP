//
// Implements the algorithm for minimal price railway, using dynamic programing
//
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

const int gMaxLineLen =  1024;


void openFile(char const *const arr) //1st const locks the values, 2nd one locks the file pointer
{
    FILE* file = fopen(arr, "r");
    if(file == NULL) //failed to open file for some reason
    {
        fprintf(stderr,"File doesn't exist\n"); /// change to print into output file~!
        exit(EXIT_FAILURE);
    }
    char tempLine[gMaxLineLen];
    fgets(tempLine, gMaxLineLen, file);
    printf("1st tempLine is: %s", tempLine);
    fclose(file);
}


int main(int argc, char* argv[]) {

    if(argc != 2)
    {
        fprintf(stderr,"Usage: RailWayPlanner <InputFile>"); /// change to print into output file~!
        exit(EXIT_FAILURE);
    }
    char const *const fName = argv[1];
    openFile(fName);
    return 0;
}
