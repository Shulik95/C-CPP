//
// Implements the algorithm for minimal price railway, using dynamic programing
//
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LINE_OFFSET 4
#define BASE_SIZE 10
#define MINIMAL_PRICE_MSG = "The minimal price is: %d"
const int gMaxLineLen =  1024;

long int gLength, gNumOfParts;
int gLineCounter = 1;
char* railTypes;

FILE* gOutFile; //declare output file.

/**
 * This struct holds all information relevant to one railway part.
 */
typedef struct RailWayParts
{
    char start, end;
    long int length, price;
}Part;

Part* parts; //an array which will hold all given parts.

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
 * checks if values given for length and number of parts are non-negative values. assumes that line ends with "\n".
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
 * checks if both parts given are legal.
 * @param start - a char representing the left joint.
 * @param end - a char representing the right joint.
 */
bool partCheck(const char* start,const char* end)
{
    /*flags which indicate if start and end parts are legal*/
    bool foundStart = false;
    bool foundEnd = false;
    for( int i = 0; i < gNumOfParts; i++)
    {
        if(railTypes[i] == *start && strlen(start) == 1)//checks if starting part in part list
        {
            foundStart = true;
        }
        if(railTypes[i] == *end && strlen(end) == 1)//checks if ending part is in part list.
        {
            foundEnd = true;
        }
    }
    return (foundEnd && foundStart);
}

/**
 * reads all lines describing parts, checks legality and add them into a part array.
 * @param inFile
 */
void saveParts(char* line)
{
    long int length, price;
    const char* const helper = "\n"; //helps support restrictions.
    char tempLength[gMaxLineLen], tempPrice[gMaxLineLen], start[gMaxLineLen], end[gMaxLineLen];
    sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", start, end, tempLength, tempPrice);
    checkIfNum(strcat(tempLength, helper), &length);
    checkIfNum(strcat(tempPrice, helper), &price);
    if(partCheck(start, end) && price > 0)
    {
        Part newPart = {.start = *start, .end = *end, .length = length, .price = price};
        parts[gLineCounter - LINE_OFFSET] = newPart;
    }
    else
    {
        printInvalidInput();
    }
}


/**
 * parses the given file into an array of structs of type Part. allocates memory for a Part array and does not free it!
 * prints first encountered error into output file
 * @param arr
 */
void parseFile(char const *const arr) //1st const locks the values, 2nd one locks the file pointer
{
    int capacity = BASE_SIZE;
    char tempLine[gMaxLineLen];
    FILE* const inFile = fopen(arr, "r");
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
    parts = (Part*)malloc(capacity * sizeof(Part)); // init array for keeping parts.
    if(parts == NULL) //allocation failed for some reason.
    {
        exit(EXIT_FAILURE);
    }
    while(fgets(tempLine, gMaxLineLen, inFile) != NULL)
    {
        if (gLineCounter - LINE_OFFSET == capacity) { //array is full, reallocation needed.
            capacity += BASE_SIZE;
            parts = (Part *) realloc(parts, sizeof(Part) * capacity);
            if(parts == NULL)
            {
                exit(EXIT_FAILURE);
            }
        }
        saveParts(tempLine);
        gLineCounter++;
    }
    free(railTypes);//de-allocs the memory.
    fclose(inFile);
}

/**
 * initializes a 2 dimensional array of pointers, does not free the memory!
 * @return - returns a pointer to a 2 dim array.
 */
int** buildTable()
{
 int** arr = (int**)malloc((gLength + 1) * sizeof(int*)); //allocates rows.
 if(arr == NULL)
 {
     exit(EXIT_FAILURE);
 }
 for(int i = 0; i < gLength + 1; i++)
 {
     arr[i] = (int*)malloc(gNumOfParts * sizeof(int)); //columns
     if(arr[i] == NULL)
     {
         exit(EXIT_FAILURE);
     }
 }
 return arr;
}


/**
 *
 */
void getMinCost()
{
    int** table = buildTable();

    free(parts); //free array of Parts, no longer needed.
    fclose(gOutFile); //close the output file program is done.
}


int main(int argc, char* argv[]) {
    if(argc != 2)
    {
        fprintf(gOutFile,"Usage: RailWayPlanner <InputFile>\n");
        exit(EXIT_FAILURE);
    }
    char const *const fName = argv[1];
    parseFile(fName);
    getMinCost();
    return 0;
}
