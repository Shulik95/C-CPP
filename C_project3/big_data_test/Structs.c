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
#include <stdlib.h>
#include "RBTree.h"
// -------------------------- const definitions -------------------------
#define GREATER 1
#define LESSER -1
#define EQUAL 0
const char* NEW_LINE = "\n";
const int CONT_SUCC = 1;
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
        return CONT_SUCC;
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
 * returns the minimal of 2 given values.
 */
int findMin(double a, double b)
{
    return (int)((a > b) ? b : a);
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
    int minLen = findMin((double)vec1->len, (double)vec2->len);
    for(int i = 0; i < minLen; i++)
    {
        if(vec1->vector[i] - vec2->vector[i] < 0) //a[i] < b[i] -> a < b
        {
            return LESSER;
        }
        else if (vec1->vector[i] - vec2->vector[i] > 0) //a[i] > b[i] -> a > b
        {
            return GREATER;
        }
    }
    if(vec1->len != vec2->len)
    {
        return (vec1->len > vec2->len) ? GREATER:LESSER ;
    }
    return EQUAL;

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
    free(pVector);
}

/**
 * calculates the norm of a given vector.
 * @param vec - pointer to a vector struct.
 * @return - the norm of the given vector.
 */
double calcNorm(const Vector* vec)
{
    double norm = 0;
    for(int i = 0; i < vec->len; i++)
    {
        norm +=(vec->vector[i] * vec->vector[i]);
    }
    return norm;
}

/**
 * copy pVector to pMaxVector if : 1. The norm of pVector is greater then the norm of pMaxVector.
 * 								   2. pMaxVector->vector == NULL.
 * @param pVector pointer to Vector
 * @param pMaxVector pointer to Vector that will hold a copy of the data of pVector.
 * @return 1 on success, 0 on failure (if pVector == NULL || pMaxVector==NULL: failure).
 */
int copyIfNormIsLarger(const void *pVector, void *pMaxVector)
{
    if(pVector == NULL || pMaxVector == NULL) // no vector to copy.
    {
        return FAIL;
    }
    else if(((Vector*)pMaxVector)->vector && calcNorm(pVector) <= calcNorm(pMaxVector))
    {
        return CONT_SUCC;
    }
    else
    {
        /*make sure vectors are the same length before copying*/
        ((Vector*)pMaxVector)->vector = (double*)realloc(((Vector*)pMaxVector)->vector,
                                                         sizeof(double)*((Vector*)pVector)->len);
        if(((Vector*)pMaxVector)->vector == NULL)
        {
            return FAIL;
        }
        ((Vector*)pMaxVector)->vector = \
        (double*)memcpy(((Vector*)pMaxVector)->vector,((Vector*)pVector)->vector,
                sizeof(double)*((Vector*)pVector)->len);
        return CONT_SUCC;
    }
}

/**
 * This function allocates memory it does not free.
 * @param tree a pointer to a tree of Vectors
 * @return pointer to a *copy* of the vector that has the largest norm (L2 Norm), NULL on failure.
 */
Vector *findMaxNormVectorInTree(RBTree *tree)
{
    if(!tree || !(tree->root))
    {
        return NULL;
    }
    else
    {
        Vector* maxVec = (Vector*)malloc(sizeof(Vector));
        if(maxVec == NULL)
        {
            return NULL;
        }
        maxVec->len = ((Vector*)tree->root->data)->len;
        maxVec->vector = (double*)calloc(maxVec->len, sizeof(double));
        if(forEachRBTree(tree, copyIfNormIsLarger, NULL) == FAIL)
        {
            /*couldn't activate function on all nodes for some reason*/
            free(maxVec->vector);
            free(maxVec);
            return NULL;
        }
        return maxVec;
    }
}

