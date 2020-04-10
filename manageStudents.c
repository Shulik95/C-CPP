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
    long int ID, grade, age;
    int counter;
    char *country, *city, *name;
}Student;

int gStopFlag = 0;
int gStudentCounter = 0;
int glineCounter = 0;
Student gStudentList[MAX_STUDENT_NUM];


/**
 * checks if a given name contains only the allowed characters.
 * @param name - name to check.
 * @return - 0 if an illegal character was found, 1 if name is legal.
 */
int checkName(char *name)
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
 * checks if a given ID upholds all demands.
 * @param id ID to check.
 * @return 1 if the ID is legal 0 otherwise, also prints relevent informative error message.
 */
int checkID(char* id)
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
 * checks if the given grade is legal.
 * @param grade
 * @return 1 if the grade is legal, 0 otherwise.
 */
int checkGrade(char* grade)
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
int checkAge(char *age)
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
int checkString(char *string)
{
    for(int i = 0; i < strlen(string); i++)
    {
        if((isalpha(string[i]) != 0) || (string[i] == 45))
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
int checkCountry(char *country)
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
int checkCity(char *city)
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
int checkInput(char *id, char *name, char *grade, char *age, char *country, char *city)
{
    return checkID(id) + checkName(name) + checkGrade(grade) + checkAge(age) +
    checkCountry(country) + checkCity(city);
}


/**
 * find the student with the best grade/age ratio and prints his/hers details.
 */
int findBest()
{
    if (gStudentCounter == 0) //no legal values were given, do nothing.
    {
        return 0;
    }
    int bestStudentIndex = 0;
    double bestRatio = 0;
    for(int i =0; i < gStudentCounter; i++)
    {
        double tGrade = (double)gStudentList[i].grade;
        double tAge = (double)gStudentList[i].age;
        double tempRatio = tGrade / tAge;
        printf("the ratio for %s is: %f", gStudentList[i].name, tempRatio);
        if( tempRatio > bestRatio)
        {
            bestStudentIndex = gStudentList[i].counter;
            bestRatio = tempRatio;
        }
    }
    Student bestStudent = gStudentList[bestStudentIndex];
    printf("best student info is: %s,%s,%ld,%ld,%s,%s\n", bestStudent.ID, bestStudent.name,
            bestStudent.grade, bestStudent.age, bestStudent.country, bestStudent.city);
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
        glineCounter++;
        if(quit == id[0])
        {
            gStopFlag = 1; //change the flag to stop gathering data.
            continue;
        }
        else if(checkInput(id, name, grade, age, country, city) == LEGAL_INPUT) // create student
        {
            char *remain;
            long int tempGrade = strtol(grade, &remain, 10);
            long int tempAge = strtol(age, &remain, 10);
            Student tempStudent = {id, tempGrade, tempAge, gStudentCounter, country, city, name};
            gStudentList[gStudentCounter] = tempStudent;
            gStudentCounter++;
        }
    }
    printf("counter is: %d\n", gStudentCounter);
    for(int i = 0; i < gStudentCounter; i++)
    {
        printf("my name is: %s\n", gStudentList[i].name);
    }
    findBest();
}

int main(int argc, char* argv[])
{
    if(strcmp(BEST,argv[1]) == 0){
        getBestStudent();
    }
    return 0;
}
