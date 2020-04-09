#include <stdio.h>
#include <string.h>

/**
 * defines the max length for each field of the user input.
 */
#define MAX_FIELD_LEN 42
#define MAX_LINE_LEN 60
#define MAX_STUDENT_NUM 5500
#define BEST "best"
#define MERGE "merge"
#define QUICK "quick"
__const char quit = 'q';

/**
 * a Student struct, enveloping all relevant student information.
 */
typedef struct Student{
    int ID;
    int grade;
    int age;
    int counter;
    char city[MAX_FIELD_LEN], name[MAX_FIELD_LEN], country[MAX_FIELD_LEN];
}Student;

int gStopFlag = 0;
int gStudentCounter = 0;
Student gStudentList[MAX_STUDENT_NUM];

int checkIfNum();

/**
 * This function checks that all given fields are legal.
 * @return 1 if an illegal input was found, 0 otherwise.
 */
int checkInput(char* id, char* name, char* grade, char* age, char* country, char* city)
{
    int checkVal = checkIfNum();
    if((checkVal == 0) || (strlen(id) != 10) || (id[0] == 0)) //means we found letters in the id.
    {
        printf("ERROR: ID can only contain exactly 10 digits and the first digit must not be 0,"
               " in line %d\n", gStudentCounter);
    }
    return 0;
}

/**
 * checks if a given input string contains only number.
 * @param input - a given string.
 * @return - 0 if string contains anything but numbers, else 1.
 */
int checkIfNum(char* input)
{
    for(int i = 0; i < strlen(input); i++)
    {
        if(input[i] < 48 || input[i] > 57) //ascii code for integers.
        {
            return 0;
        }
    }
    return 1;
}

/**
 * the main running function for getting the best student, receives input, calls needed methods to
 * check legality and returns the student if such exits.
 */
void getBestStudent()
{
    while(gStopFlag == 0)
    {
        char input[MAX_LINE_LEN], city[MAX_FIELD_LEN], name[MAX_FIELD_LEN], country[MAX_FIELD_LEN]
        , id[MAX_FIELD_LEN], grade[MAX_FIELD_LEN], age[MAX_FIELD_LEN];

        printf("Enter student info.  To exit press q, then enter\n");

        fgets(input, MAX_LINE_LEN , stdin);
        sscanf(input, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", id, name, grade,
                age, country, city);
        gStudentCounter++;

        if(quit == id[0])
        {
            gStopFlag = 1; //change the flag to stop gathering data.
        }
        checkInput(id, name, grade, age, country, city);
    }
}

int main(int argc, char* argv[])
{
    if(strcmp(BEST,argv[1]) == 0){
        getBestStudent();
    }
    return 0;
}
