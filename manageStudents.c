#include <stdio.h>
#include <regex.h>
#include <string.h>

/**
 * defines the max length for each field of the user input.
 */
#define MAX_FIELD_LEN 42
#define MAX_STUDENT_NUM 5500
#define BEST "best"
#define MERGE "merge"
#define QUICK "quick"

typedef struct Student{
    int ID;
    int grade;
    int age;
    int counter;
    char city[MAX_FIELD_LEN], name[MAX_FIELD_LEN], country[MAX_FIELD_LEN];
}Student;

int gStudentCounter = 0;
Student gStudentList[MAX_STUDENT_NUM];
char gBest[4] = {'b','e','s','t','\0'};
char gMerge[5] = {'m','e','r','g','e','\0'};





int main(int argc, char* argv[]) {
    if(argv[1] == BEST){

    }
    return 0;
}
