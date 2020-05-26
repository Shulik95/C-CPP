/**
 * @file RBTree.c
 * @author  Shalom Kachko
 * @version 1.0
 * @date 25 may 2020
 *
 * @brief helper function and implementation of Structs.h
 *
 * @section DESCRIPTION
 * The system keeps track of the cooking times.
 * Input  : Times to be measured.
 * Process: Summing times if needed, waiting for the correct time and
 *          notifying the user.
 * Output : Notification.
 */
// ------------------------------ includes ------------------------------
#include "Structs.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
// -------------------------- const definitions -------------------------
const char* NEW_LINE = "\n";
const int SUCCESS = 1;
const int FAIL = 0;


// ----------------------------- functions ------------------------------

/**
 * CompFunc for strings (assumes strings end with "\0")
 * @param a - char* pointer
 * @param b - char* pointer
 * @return equal to 0 iff a == b. lower than 0 if a < b. Greater than 0 iff b < a. (lexicographic
 * order)
 */
int stringCompare(const void *a, const void *b)
{
    const char* str1 = (const char*) a;
    const char* str2 = (const char*) b;
    return strcmp(str1, str2);
}

/**
 * ForEach function that concatenates the given word and \n to pConcatenated. pConcatenated is
 * already allocated with enough space.
 * @param word - char* to add to pConcatenated
 * @param pConcatenated - char*
 * @return 0 on failure, other on success
 */
int concatenate(const void *word, void *pConcatenated)
{
    char* tempStr = (char*)word;
    tempStr = strcat(tempStr, NEW_LINE); //concat "\n" to word
    pConcatenated = (void*)strcat((char*)pConcatenated, tempStr); //concat

    if(pConcatenated == NULL) // check if strcat didnt fail
    {
        return  FAIL;
    }

    else
    {
        return SUCCESS;
    }
}

/**
 * FreeFunc for strings
 */
void freeString(void *s)
{
    free((char*)s);
}

/**
 * CompFunc for Vectors, compares element by element, the vector that has the first larger
 * element is considered larger. If vectors are of different lengths and identify for the length
 * of the shorter vector, the shorter vector is considered smaller.
 * @param a - first vector
 * @param b - second vector
 * @return equal to 0 iff a == b. lower than 0 if a < b. Greater than 0 iff b < a.
 */
int vectorCompare1By1(const void *a, const void *b)
{
    const Vector* vec1 = (const Vector*)a;
    const Vector* vec2 = (const Vector*)b;
    /*get minimal length for number of iteration needed*/
    int minLen = (int) fmin((double)vec1->len, (double)vec2->len);
    for(int i = 0; i < minLen; i++)
    {
        if(vec1->vector[i] < vec2->vector[i])
        {
            
        }
    }

}

/**
 * FreeFunc for vectors
 */
void freeVector(void *pVector)
{
    if(pVector == NULL)
    {
        /*do nothing*/
        return;
    }
    free(((Vector*)pVector)->vector); //free dynamically allocated array.
    ((Vector*)pVector)->vector = NULL;
}


