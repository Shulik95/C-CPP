//
// Implements the algorithm for minimal price railway, using dynamic programing
//
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define LINE_OFFSET 4
#define BASE_SIZE 10
#define  NO_MIN -1
#define MAX_LINE_LEN 1024

long int gLength, gNumOfParts;
int gLineCounter = 1;
char* railTypes = NULL;

FILE* gOutFile; //declare output file.
FILE* inFile; //declare input file.

/**
 * This struct holds all information relevant to one railway part.
 */
typedef struct RailWayParts
{
    char start, end;
    long int length, price, startIdx;
}Part;

Part* parts = NULL; //an array which will hold all given parts.


/**
 * deals with the most basic failure, problem opening the input.
 */
void inputFail()
{
    fclose(gOutFile);
    exit(EXIT_FAILURE);
}

/**
 * closes both input and output files.
 */
void closeFiles()
{
    fclose(inFile);
    inputFail();
}

/**
 * closes all open files and frees allocated memory.
 */
void closeProgram()
{

    free(parts);
    free(railTypes);
    closeFiles();
}

/**
 * clears memory and exits program in case of an empty file.
 */
void emptyFail()
{
    fprintf(gOutFile, "File is empty.");
    closeFiles();
}

/**
 * if an illegal input was found in the file, this function is called. prints relevant error and exits program
 * with EXIT_FAILURE code.
 */
void printInvalidInput()
{
    fprintf(gOutFile, "Invalid input in line: %d.", gLineCounter);
    closeFiles();
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
        emptyFail();
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
    for (unsigned int i = 0; i < strlen(line) - 1; i++)
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
            free(railTypes);
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
bool partCheck(const char* start, const char* end)
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
 * checks that both length and price of a part are positive integers.
 * @param line - input to check.
 * @param ptr - pointer to the variable that stores the value.
 */
void checkPriceAndLen(const char* line, long int* ptr)
{
    char* dispose;
    long int temp;
    for (unsigned int i = 0; i < strlen(line) - 1; i++)
    {
        if((line[i] < 48 || line[i] > 57)) //char isn't an integer.
        {
            fprintf(gOutFile, "Invalid input in line: %d.", gLineCounter);
            closeProgram(); // free both memory allocs and close files.
        }
    }
    temp = strtol(line, &dispose, 10);
    if(temp > 0)
    {
        *ptr = temp;
    }
    else
    {
        fprintf(gOutFile, "Invalid input in line: %d.", gLineCounter);
        closeProgram(); //releases both prev allocs and closes files.
    }
}

/**
 * helper method for the main algorithm. finds the column of given part.
 * @param input - char to find
 * @return index representing the column to search.
 */
int getIndex(char input)
{
    int idx = 0;
    for(int i = 0; i < gNumOfParts; i++)
    {
        if(railTypes[i] == input)
        {
            idx = i;
        }
    }
    return idx;
}

/**
 * reads all lines describing parts, checks legality and add them into a part array.
 * @param inFile
 */
void saveParts(char* line)
{
    long int length, price, idx;
    const char* const helper = "\n"; //helps create expected format..
    char tempLength[MAX_LINE_LEN], tempPrice[MAX_LINE_LEN], start[MAX_LINE_LEN], end[MAX_LINE_LEN];
    sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", start, end, tempLength, tempPrice);
    checkPriceAndLen(strcat(tempLength, helper), &length);
    checkPriceAndLen(strcat(tempPrice, helper), &price);
    if(partCheck(start, end))
    {
        idx = getIndex(*start); //get the index which represents the
        Part newPart = {.start = *start, .end = *end, .length = length, .price = price, .startIdx = idx};
        parts[gLineCounter - LINE_OFFSET] = newPart;
    }
    else
    {
        fprintf(gOutFile, "Invalid input in line: %d.", gLineCounter);
        closeProgram(); //releases both prev allocs and closes files.
    }
}


/**
 * parses the given file into an array of structs of type Part. allocates memory for a Part array and does not free it!
 * prints first encountered error into output file
 * @param arr
 */
void parseFile() //1st const locks the values, 2nd one locks the file pointer
{
    int capacity = BASE_SIZE;
    char tempLine[MAX_LINE_LEN];
    checkEmpty(inFile); // check if file4 is empty, prints error and exits.
    fgets(tempLine, MAX_LINE_LEN, inFile); //gets length of rail
    checkIfNum(tempLine, &gLength);
    gLineCounter++;
    fgets(tempLine, MAX_LINE_LEN, inFile); //gets number of parts.
    checkIfNum(tempLine, &gNumOfParts);
    if(gNumOfParts <= 0) //number of parts has to positive according to school sol
    {
        printInvalidInput();
    }
    gLineCounter++;
    fgets(tempLine, MAX_LINE_LEN, inFile); //gets list of joints.
    railTypes = (char*)malloc(gNumOfParts * sizeof(char)); //init array for all types.
    if(railTypes == NULL) //allocation failed for some reason.
    {
        closeFiles(); //closes both open files and exists program
    }
    checkJoints(tempLine);
    gLineCounter++;
    parts = (Part*)malloc(capacity * sizeof(Part)); // init array for keeping parts.
    if(parts == NULL) //allocation failed for some reason.
    {
        free(railTypes); //only memory allocated so far.
        closeFiles(); // close input and output and exit.
    }

    /*iterate over remaining lines and create parts accordingly*/
    while(fgets(tempLine, MAX_LINE_LEN, inFile) != NULL)
    {
        if (gLineCounter - LINE_OFFSET == capacity) //array is full, reallocation needed.
        {
            capacity += BASE_SIZE;
            parts = (Part*) realloc(parts, sizeof(Part) * capacity);
            if(parts == NULL)
            {
                closeProgram();
            }
        }
        saveParts(tempLine);
        gLineCounter++;
    }
    if(feof(inFile) == 0) //fgets failed before EOF, close all and exit
    {
        closeProgram();
    }
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
     closeProgram();
     exit(EXIT_FAILURE);
 }
 for(int i = 0; i < gLength + 1; i++)
 {
     arr[i] = (int*)malloc(gNumOfParts * sizeof(int)); //columns
     if(arr[i] == NULL)
     {
         closeProgram();
         exit(EXIT_FAILURE);
     }
 }
 return arr;
}

void findMinVal(int len, int k, int* currMinVal, int** table)
{
    for(int p = 0; p < gLineCounter -LINE_OFFSET; p++)
    {
        if(parts[p].end == railTypes[k] && len - parts[p].length >= 0)
        {
            const int tempLen = len - (int)parts[p].length; //row to search
            int tempVal = (int)parts[p].price + table[tempLen][parts[p].startIdx];
            if(tempVal < 0) //checks overflow
            {
                tempVal = INT_MAX;
            }
            if(tempVal < *currMinVal)
            {
                *currMinVal = tempVal;
            }
        }
    }
}

/**
 * inits a table of size length+1 X K and extracts the minimal price for a railway of size length. result is printed
 * into output file.
 */
void getMinCost()
{
    int minVal = INT_MAX;
    int** table = buildTable();
    for(int l = 0; l < gLength + 1; l ++) //iterates of different lengths.
    {
        for(int k = 0; k < gNumOfParts; k ++) //iterates over different connections.
        {
            if(l == 0) //base case, l is 0 min cost for all parts is 0
            {
                table[l][k] = 0;
            }
            else //get minimal rail so far.
            {
                findMinVal(l, k, &minVal, table); // changes minVal
                table[l][k] = minVal; //assign min value
                minVal = INT_MAX; //restart val
            }
        }
    }

    /*get minimal value from top row in table*/
    for(int t = 0; t < gNumOfParts; t++)
    {
        if (table[gLength][t] < minVal)
        {
            minVal = table[gLength][t];
        }
    }
    if(minVal == INT_MAX) //the rail we want doesnt exist, prints -1
    {
        minVal = NO_MIN;
    }
    fprintf(gOutFile, "The minimal price is: %d", minVal);

    /*free all memory which was allocated for the data structure*/
    for(int j = 0; j < gLength + 1; j++)
    {
        free(table[j]);
        table[j] = NULL;
    }
    free(table);
    table = NULL;
}

/**
 * main function, runs all program.
 * @param argc - amount of arguments given by user.
 * @param argv - program variables
 * @return  - 0 if program was successfull, 1 otherwise.
 */
int main(int argc, char* argv[])
{
    gOutFile = fopen("railway_planner_output.txt", "w");
    if(argc != 2)
    {
        fprintf(gOutFile, "Usage: RailwayPlanner <InputFile>");
    inputFail();
}
    char const *const fName = argv[1];
    inFile = fopen(fName, "r");
    if(inFile == NULL) //failed to open file for some reason
    {
        fprintf(gOutFile, "File doesn't exists.");
        inputFail();
    }
    parseFile();
    getMinCost();
    free(parts); //program ran successfully, close both files and free memory.
    free(railTypes);
    fclose(gOutFile);
    fclose(inFile);
    exit(EXIT_SUCCESS);
}
