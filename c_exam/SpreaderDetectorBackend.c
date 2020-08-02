// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "SpreaderDetectorParams.h"
#include <string.h>

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

int gCounter = 0;

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
typedef struct Edge
{
    Person src, dest;
    float time, distance;
} Edge;

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
 * this function parses the people.in file.
 * @param fileName - name of file to parse.
 * @return - an array containing Person structs for all the people.
 */
Person* parsePeopleFile(const char* const fileName)
{
    int capacity = BASE_SIZE;
    int lineCounter = 0;

    /*open file and check success*/
    inputFile = fopen(fileName, "r");
    if (inputFile == NULL) //opening input file failed.
    {
        printError(INPUT_ERR);
    }

    Person* personArr = (Person*)malloc(capacity * sizeof(Person));
    if(personArr == NULL) // malloc failed, close files and exit program.
    {
        printError(STL_ERR);
    }

    char buffer[MAX_LINE_LEN];
    while(fgets(buffer, MAX_LINE_LEN, inputFile) != NULL)
    {
        if (lineCounter == capacity) //increase array if needed.
        {
            capacity += BASE_SIZE;
            personArr = (Person*) realloc(personArr, sizeof(Person) * capacity);
            if(personArr == NULL)
            {
                free(personArr); //free what was already allocated.
                printError(STL_ERR); //close files and exit.
            }
        }
        addPerson(buffer, &personArr ,lineCounter);
        lineCounter++;
        gCounter++;
    }
    return personArr;
}


int main(int argc, char* argv[])
{
    if (argc != LEGAL_INPUT_NUM)
    {
        fprintf(stderr, "%s", USAGE_ERR);
        exit(EXIT_FAILURE);
    }
    outputFile = fopen(gOutputName, "w");
    if(outputFile == NULL)
    {

    }
    const char* const peopleFile = argv[1];
    Person* temp = parsePeopleFile(peopleFile);
    for(int i = 0; i < gCounter; i++ )
    {
        fprintf(outputFile, "Name: %s, ID: %s, age: %f \n", temp[i].name, temp[i].ID, temp[i].age);
    }
    return 0;
}
