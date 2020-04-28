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

long int gLength, gNumOfParts;
int gLineCounter = 1;
char* railTypes;

FILE* gOutFile; //declare output file.

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
 * if an illegal input was found in the file, this function is called. prints relevant error and exits program
 * with EXIT_FAILURE code.
 */
void printInvalidInput()
{
    fprintf(gOutFile, "Invalid input in line: %d", gLineCounter);
    exit(EXIT_FAILURE);
}


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
 * checks if values given for length and number of parts are non-negative values.
 * @param line - line containing the gLength.
 * @param ptr - pointer to integer value to change.
 */
void checkIfNum(const char* line, long int* ptr)
{
    char* dispose;
    long int temp;
    for (int i = 0; i < strlen(line) - 1; i++)
    {
        if((line[i] < 48 || line[i] > 57)) //char isn't an integer.
        {
            printInvalidInput();
        }
    }
    temp = strtol(line, &dispose, 10);
    if(temp >= 0)
    {
        *ptr = temp;
    }
}

/**
 * checks if given rail joints are legal and appends them into an array for keeping.
 * @param line - line containing joins separated by commas.
 */
void checkJoints(char* line)
{
    const char* delimiter = ",";
    char* token = strtok(line, delimiter); //get first token.
    int i = 0;
    while (token != NULL)
    {
        if (strlen(token) != 1 && (token[1] != '\n')) //contains more than a single char, illegal.
        {
            printInvalidInput();
        }
        railTypes[i] = *token;
        i++;
        token = strtok(NULL, delimiter);
    }
}

/**
 *
 * @param arr
 */
void openFile(char const *const arr) //1st const locks the values, 2nd one locks the file pointer
{
    char tempLine[gMaxLineLen];
    FILE* inFile = fopen(arr, "r");
    gOutFile = fopen("railway_planner_output.txt", "w");
    if(inFile == NULL) //failed to open file for some reason
    {
        fprintf(gOutFile, "File doesn't exist\n"); /// change to print into output file~!
        exit(EXIT_FAILURE);
    }
    checkEmpty(inFile); // check if file is empty, prints error and exits.
    fgets(tempLine, gMaxLineLen, inFile); //gets length of rail
    checkIfNum(tempLine, &gLength);
    gLineCounter++;
    fgets(tempLine, gMaxLineLen,inFile); //gets number of parts.
    checkIfNum(tempLine, &gNumOfParts);
    gLineCounter++;
    fgets(tempLine, gMaxLineLen,inFile); //gets list of joints.
    railTypes = (char*)malloc(gNumOfParts * sizeof(char)); //init array for all types.
    if(railTypes == NULL) //allocation failed for some reason.
    {
        exit(EXIT_FAILURE);
    }
    checkJoints(tempLine);
    gLineCounter++;
    printf("Length is: %ld\n", gLength);
    printf("number of parts is: %ld\n", gNumOfParts);
    fclose(inFile);
}


int main(int argc, char* argv[]) {
    if(argc != 2)
    {
        fprintf(gOutFile,"Usage: RailWayPlanner <InputFile>\n"); /// change to print into output file~!
        exit(EXIT_FAILURE);
    }
    char const *const fName = argv[1];
    openFile(fName);
    return 0;
}
