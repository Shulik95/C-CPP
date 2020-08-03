// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "SpreaderDetectorParams.h"
#include <string.h>

// ----------------------------- definitions ----------------------------
const char* USAGE_ERR = "Usage: ./SpreaderDetectorBackend <Path to People.in> <Path to Meetings.in>\n";
const char* INPUT_ERR = "Error in input files.\n";
const char* OUTPUT_ERR = "Error in output file.\n";
const int LEGAL_INPUT_NUM = 3;

#define MAX_LINE_LEN 1024
#define BASE_SIZE 10
#define DEFAULT_PROB 0.0
#define FAILURE -1
#define SICK 1
#define GT 1
#define EQUAL 0

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
int idCmpfunc(const void* p1, const void* p2)
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
        printError(STANDARD_LIB_ERR_MSG);
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
                printError(STANDARD_LIB_ERR_MSG); //close files and exit.
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
 * calculates the the probability of one person infecting another.
 * @param time - time they spent together.
 * @param distance - distance between the two people.
 */
float Crna(float const time, float const distance)
{
    return (time * MIN_DISTANCE) / (distance * MAX_TIME);
}

/**
 * returns the index of the person struct with the given ID number.
 * @param arr - sorted array of Person structs.
 */
 //TODO: test binaetSeach first thing tommorow!!!
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
    float dist, time;
    int id1, id2, currInfectorIdx;
    char* res;
    Person* personArr = *arr;

    inputFile = fopen(fileName, "w");
    if(inputFile == NULL)
    {
        /*opening file failed, free memory and close files.*/
        free(personArr);
        printError(STANDARD_LIB_ERR_MSG);
    }

    qsort(personArr, gCounter, sizeof(Person), idCmpfunc); //sort array to use binary search.
    char buffer[MAX_LINE_LEN];
    fgets(buffer, MAX_LINE_LEN, inputFile); //get first line
    int tempID = (int)strtol(buffer, &res, 10);
    int idx = binarySearch(personArr, 0, gCounter - 1, tempID);
    personArr[idx].prob = SICK;
    currInfectorIdx = idx;
    while(fgets(buffer, MAX_LINE_LEN, inputFile) != NULL)
    {
        sscanf(buffer, "%d %d %f %f", &id1, &id2, &dist, &time);
        if(currInfectorIdx != binarySearch(personArr, 0, gCounter - 1, id1)) //infector changed, find new one.
        {
            currInfectorIdx = binarySearch(personArr, 0, gCounter - 1, id1); // get correct infector index.
        }
        float currCrna = Crna(time, dist);
        currCrna *= personArr[currInfectorIdx].prob;
        int infectedIdx = binarySearch(personArr, 0, gCounter, id2); // get 2nd person struct.
        personArr[infectedIdx].prob = currCrna; // update that struct to contain the infection probability.
    }
    return personArr;
}

/**
 * comparator method for sorting by infection probability.
 * @param p1 - pointer to Person struct.
 * @param p2 - pointer to Person struct.
 */
int probCompFunc(void* const p1, void* const p2)
{
    float prob1 = (*(Person*)p1).prob;
    float prob2 = (*(Person*)p2).prob;
    float res = prob1 - prob2;
    if(res > 0)
    {
        return GT;
    }
    else if (res < 0)
    {
        return FAILURE;
    }
    else
    {
        return EQUAL;
    }
}

/**
 * iterates over given array, checks for each person the probability of infection and writes recommendation into file
 * according to given care standards. This method is in charge of freeing the allocated array.
 * @param arr - array of Person structs, the probability for each is calculated, array is not sorted according to
 * probability.
*/
void writeDataToOutput(Person* arr)
{

}



int main(int argc, char* argv[])
{
    if (argc != LEGAL_INPUT_NUM)
    {
        printError(USAGE_ERR);
    }
    outputFile = fopen(OUTPUT_FILE, "w");
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
