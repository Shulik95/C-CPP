//
// Implements the algorithm for minimal price railway, using dynamic programing
//
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const int gMaxLineLen =  1024;
int gLineCounter = 1;
FILE* gOutFile; //declare output file.

void printInvalidInput()
{
    fprintf(gOutFile, "Invalid input in line %d", )
}

/**
 * This struct holds all information relevant to one railway part.
 */
typedef struct railWayParts
{
    char start, end;
    int length;
    int price;
}Part;

/**
 * checks if the file is empty using fseek and ftell. if the file is empty prints error into file and exits program with
 * exit code 1. otherwise restarts pointer to beginning of file and returns.
 * @param inputFile - stream leading to the file.
 */
void checkEmpty(FILE* inputFile)
{
    fseek(inputFile, 0, SEEK_END);
    unsigned long fileLen = (unsigned long) ftell(inputFile); // check file size;
    if(fileLen > 0) //if true file isn't empty
    {
        rewind(inputFile); //resets pointer in file.
    }
    else //file is empty, print error into file and exit.
    {
        fprintf(gOutFile, "File is empty.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 *
 * @param arr
 */
void openFile(char const *const arr) //1st const locks the values, 2nd one locks the file pointer
{
    int length, numOfParts;
    FILE* inFile = fopen(arr, "r");
    gOutFile = fopen("railway_planner_output.txt", "w");
    if(inFile == NULL) //failed to open file for some reason
    {

        fprintf(gOutFile, "File doesn't exist\n"); /// change to print into output file~!
        exit(EXIT_FAILURE);
    }
    checkEmpty(inFile); // check if file is empty, prints error and exits.
    char tempLine[gMaxLineLen];
    fgets(tempLine, gMaxLineLen, inFile);

    printf("1st tempLine is: %s", tempLine);
    fclose(inFile);
}

/**
 * checks if given length is legal - a non-negative integer. if the line is illegal, prints error into file and exists
 * program with EXIT_FAILURE code.
 * @param line - line containing the length.
 */
void checkLength(char* line)
{
    for (int i = 0; i < strlen(line); i++)
    {
     if(isdigit(line[i]) == 0)
     {

     }
    }
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
