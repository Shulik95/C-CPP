// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "SpreaderDetectorParams.h"
#include <string.h>
#include <stdbool.h>

// ----------------------------- definitions ----------------------------
const char* USAGE_ERR = "Usage: ./SpreaderDetectorBackend <Path to People.in> <Path to Meetings.in>\n";
const char* INPUT_ERR = "Error in input files.\n";
const char* OUTPUT_ERR = "Error in output file.\n";
const char* STL_ERR = "Standard library error.\n";
const char* gOutputName = "SpreaderDetectorAnalysis.out";
const int LEGAL_INPUT_NUM = 3;

#define MAX_LINE_LEN 1024
#define BASE_SIZE 10
#define DEFAULT_PROB 0.0
#define FAILURE -1

int gCounter = 0;
bool meetingFlag = false;

/**
 * struct representing each person.
 * prob - the probability of being sick as calculated by crna algorithm.
 */
typedef struct Person
{
    char name[MAX_LINE_LEN], ID[MAX_LINE_LEN];
    float age, prob;
} Person;

/**
 * struct to serve as weighted edges in graph, the weight is determined by time an distance the infected has spent with
 * the infector.
 */
//typedef struct Edge
//{
//    Person src, dest;
//    float time, distance;
//} Edge;


/**
 * input file and output file, will be initialized in main.
 */
FILE* inputFile;
FILE* outputFile;

// ------------------------------ functions -----------------------------

void printError(const char* errMsg)
{
    fprintf(stderr, "%s", errMsg);
    fclose(outputFile);
    fclose(inputFile);
    exit(EXIT_FAILURE);
}

/**
 * creates a person struct and inserts it into the array.
 * @param  - line containing the info of the person, read by parsing method.
 * @param lineCounter - the line on which the person appears, decides its index in the array.
 */
void addPerson(char* line, Person** arr ,int lineCounter)
{
    char tempAge[MAX_LINE_LEN];
    char name[MAX_LINE_LEN];
    char id[MAX_LINE_LEN];
    float age = 0;
    sscanf(line, "%s %s %s", name, id, tempAge);
    age = strtof(tempAge, NULL);

    Person newPerson = {.age = age, .prob = DEFAULT_PROB};
    strcpy(newPerson.name, name);
    strcpy(newPerson.ID, id);
    (*arr)[lineCounter] = newPerson;
}

/**
 * comparator func for qsort.
 * @param p1 - first person to compare.
 * @param p2 - 2nd person to compare.
 * @return - return val is positive if p1 > p2, negative if p2 > p1, 0 if they're equal.
 */
int cmpfunc(const void* p1, const void* p2)
{
    int num1 = (int)(*(Person*)p1).ID;
    int num2 = (int)(*(Person*)p2).ID;
    return (num1 - num2);
}

/**
 * this function parses the people.in file, allocates memory but doesnt free it!
 * @param fileName - name of file to parse.
 * @return - an array containing Person structs for all the people.
 */
void* parsePeopleFile(const char* const fileName)
{
    int capacity = BASE_SIZE;
    int lineCounter = 0;

    /*open file and check success*/
    inputFile = fopen(fileName, "r");
    if (inputFile == NULL) //opening input file failed.
    {
        printError(INPUT_ERR);
    }

    char buffer[MAX_LINE_LEN];
    Person* arr = (Person*)malloc(capacity * sizeof(Person));
    if(arr == NULL) // malloc failed, close files and exit program.
    {
        printError(STL_ERR);
    }
    while(fgets(buffer, MAX_LINE_LEN, inputFile) != NULL)
    {
        if (lineCounter == capacity) //increase array if needed.
        {
            capacity += BASE_SIZE;
            arr = (Person*) realloc(arr, sizeof(Person) * capacity);
            if(arr == NULL)
            {
                free(arr); //free what was already allocated.
                printError(STL_ERR); //close files and exit.
            }
        }
        addPerson(buffer, &arr , lineCounter);
        lineCounter++;
        gCounter++;
    }
    fclose(inputFile);
    return arr;
}

/**
 * returns the index of the person struct with the given ID number.
 * @param arr - sorted array of Person structs.
 */
int binarySearch(Person arr[], int left, int right, int val)
{
    if(right >= left)
    {
        int mid = (left + right) / 2;
        int midVal = (int)arr[mid].ID;
        if(midVal == val)
        {
            return mid; //found value, return it
        }
        else if(val < midVal) //val must be on the left of mid
        {
            return binarySearch(arr, left, mid + 1, val);
        }
        else //val is on the right
        {
            return binarySearch(arr, mid + 1, right, val);
        }
    }
    return FAILURE;
}

/**
 * parses the "meeting.in" file. calculates the infection probability and adds it to the correct Person
 * struct.
 * @param fileName - file to parse.
 * @param arr - array of Person structs.
 * @return - pointer to an array of Person structs.
 */
Person* finalizeData(const char* fileName, Person** arr)
{


}



int main(int argc, char* argv[])
{
    if (argc != LEGAL_INPUT_NUM)
    {
        printError(USAGE_ERR);
    }
    outputFile = fopen(gOutputName, "w");
    if(outputFile == NULL) //opening outputFile failed
    {
        printError(OUTPUT_ERR);
    }
    const char* const peopleFile = argv[1];
    Person* temp = (Person*)parsePeopleFile(peopleFile);
    const char* meetingFile = argv[2];
    for(int i = 0; i < gCounter; i++ )
    {
        fprintf(outputFile, "Name: %s, ID: %s, age: %f \n", temp[i].name, temp[i].ID, temp[i].age);
    }
    return 0;
}
