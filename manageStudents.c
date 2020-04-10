#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * defines the max length for each field of the user input.
 */
#define MAX_FIELD_LEN 42
/**
 * max length for given input
 */
#define MAX_LINE_LEN 60
#define MAX_STUDENT_NUM 5500
#define LEGAL_INPUT 6
#define BEST "best"
#define MERGE "merge"
#define QUICK "quick"
const char quit = 'q';
const int minGrade = 0;
const int maxGrade = 100;
const int minAge = 18;
const int maxAge = 120;


/**
 * a Student struct, enveloping all relevant student information.
 */
typedef struct Student{
    char ID[MAX_FIELD_LEN];
    long int grade, age;
    char name[MAX_FIELD_LEN], country[MAX_FIELD_LEN], city[MAX_FIELD_LEN];
    long int counter;
}Student;


int gStudentCounter = 0;
int glineCounter = 0;
Student gStudentList[MAX_STUDENT_NUM];

/**
 * checks if a given input string contains only number.
 * @param input - a given string.
 * @return - 0 if string contains anything but numbers, else 1.
 */
int checkIfNum(char input[])
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
 * checks if a given ID upholds all demands.
 * @param id ID to check.
 * @return 1 if the ID is legal 0 otherwise, also prints relevent informative error message.
 */
int checkID(char id[])
{
    int checkVal = checkIfNum(id);
    if((checkVal == 0) || (strlen(id) != 10) || ((int)id[0] == 48))
    {
        printf("ERROR: ID can only contain exactly 10 digits and the first digit must not be 0,"
               " in line %d\n", glineCounter);
        return 0;
    }
    return 1;
}

/**
 * checks if a given name contains only the allowed characters.
 * @param name - name to check.
 * @return - 0 if an illegal character was found, 1 if name is legal.
 */
int checkName(char name[])
{
    for(int j = 0; j < strlen(name); j++)
    {
        if((name[j] == 32) || (name[j] == 45) || (isalpha(name[j]) != 0))
        {
            continue; // the values are legal.
        }
        else // found illegal value in the name.
        {
            printf("ERROR: a name may only contain letter - both lower and upper case, "
                   "spaces and '-'. in line %d\n", glineCounter);
            return 0;
        }
    }
    return 1;
}

/**
 * checks if the given grade is legal.
 * @param grade
 * @return 1 if the grade is legal, 0 otherwise.
 */
int checkGrade(char grade[])
{
    char *remain;
    long int convertedGrade = strtol(grade, &remain, 10); // convert str into a long.
    if(convertedGrade > maxGrade || convertedGrade < minGrade)
    {
        printf("ERROR: grade may only be an integer from 0 to 100, including. "
               "in line %d\n", glineCounter);
        return 0;
    }
    return 1;
}

/**
 * checks if the given age is legal.
 * @param age
 * @return 1 if the given value is legal, 0 otherwise.
 */
int checkAge(char age[])
{
    char *remain;
    long int convertedAge = strtol(age, &remain, 10);
    if(convertedAge < minAge || convertedAge > maxAge)
    {
        printf("ERROR: age may only be an integer between 18 to 120."
               " in line %d\n", glineCounter);
        return 0;
    }
    return 1;
}

/**
 * checks if a given string contain only letters or '-'.
 * @param string - string to check.
 * @return return 1 if the string is legal, 0 otherwise.
 */
int checkString(char input[])
{
    for(int i = 0; i < strlen(input); i++)
    {
        if((isalpha(input[i]) != 0) || (input[i] == 45))
        {
            continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

/**
 * checks if the given country value is legal.
 * @param country - value to check.
 * @return 1 if the given value is legal, 0 otherwise.
 */
int checkCountry(char country[])
{
    if(checkString(country))
    {
        return 1;
    }
    printf("ERROR: country may only contain lower and upper case letters and '-'."
           " in line %d\n", glineCounter);
    return 0;
}

/**
 * checks if the given city is legal.
 * @param country - value to check.
 * @return 1 if the value is lega, 0 otherwise.
 */
int checkCity(char city[])
{
    if(checkString(city))
    {
        return 1;
    }
    printf("ERROR: city may only contain lower and upper case letters and '-'."
           " in line %d\n", glineCounter);
    return 0;
}

/**
 * This function checks that all given fields are legal.
 * @return 1 if an illegal input was found, 0 otherwise.
 */
int checkInput(char name[], char id[], char city[], char country[], char age[], char grade[])
{
    return checkID(id) + checkName(name) + checkGrade(grade) + checkAge(age) +
           checkCountry(country) + checkCity(city);
}

/**
 * read the input given by the user and returns best student info if such exists.
 */
void getBestStudent()
{
    int stopFlag = 0;
    while(stopFlag == 0) //user still gives input.
    {
        char input[MAX_LINE_LEN], city[MAX_FIELD_LEN], country[MAX_FIELD_LEN], name[MAX_FIELD_LEN],
        id[MAX_FIELD_LEN], grade[MAX_FIELD_LEN], age[MAX_FIELD_LEN], temp;

        printf("Enter student info.  To exit press q, then enter\n");

        fgets(input, MAX_LINE_LEN, stdin); // get info from user.
        glineCounter++;
        if(strlen(input) == 1)
        {
            sscanf(input, "%c", &temp);
            if(temp == quit)
            {
                stopFlag = 1; // stop the loop.
                continue;
            }
        }
        sscanf(input, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,]",
                id, name, grade, age, country, city);
        if(checkInput(id, name, grade, age, country, city) == LEGAL_INPUT)
        {
            char *remain;
            long int tempGrade = strtol(grade, &remain, 10);
            long int tempAge = strtol(grade, &remain, 10);
            Student tempStudent = {.name = (char)name, .ID = (char)id, .grade = tempGrade,
                                   .age = tempAge, .country = (char)country, .city = (char)city,
                                   .counter = gStudentCounter};
            gStudentList[gStudentCounter] = tempStudent;
            gStudentCounter++;
        }
    }
}

int main(int argc, char* argv[])
{
    if(strcmp(BEST,argv[1]) == 0){
        getBestStudent();
    }
    return 0;
}