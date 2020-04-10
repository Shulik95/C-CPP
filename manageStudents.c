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
    double ID;
    long int grade, age;
    char name[MAX_FIELD_LEN], country[MAX_FIELD_LEN], city[MAX_FIELD_LEN];
    long int counter;
}Student;

int gStudentCounter = 0;
int glineCounter = 0;
Student gStudentList[MAX_STUDENT_NUM];


/**
 * returns the number of digits in a given integer.
 */
int digitNum(long num)
{
    int counter = 0;
    do
    {
        counter++;
        num /= 10;
    }while(num != 0);
    return counter;
}

/**
 * checks if given input contains onlu numbers.
 * @param input
 * @return 1 if input is a number, 0 otherwise.
 */
int checkIfNum(const char input[MAX_FIELD_LEN]){
    for(int i = 0; i < strlen(input); i++)
    {
        if((input[i] < 48) || (input[i] > 57))
        {
            return 0; //char is not a digit.
        }
    }
    return 1;
}


/**
 * checks if id is a 10 digit number that doesnt start with a 0.
 * @param id - input to check.
 * @return - 1 if input is legal, 0 otherwise.
 */
int idCheck(char id[MAX_FIELD_LEN])
{
    long int converted = 0;
    sscanf(id, "%li", &converted);
    if((id[0] == 48) || (checkIfNum(id) == 0) || (digitNum(converted) != 10))
    {
        printf("ERROR: ID can only contain exactly 10 digits and the first digit must not be 0,"
               " in line %d\n", glineCounter);
        return 0; //first number is 0;
    }
    return 1;
}

int nameCheck(char name[MAX_FIELD_LEN])
{
    for(int i = 0; i < strlen(name); i++)
    {
        if ((isalpha(name[i]) != 0) || (name[i] == 32) || (name[i] == 45))
        {
            continue;
        } else
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
int checkGrade(char grade[MAX_FIELD_LEN])
{
    long int converted = 0;
    sscanf(grade, "%li", &converted);
    if(converted < minGrade || converted > maxGrade || checkIfNum(grade) == 0)
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
int checkAge(char age[MAX_FIELD_LEN])
{
    long int converted = 0;
    sscanf(age, "%li", &converted);
    if(converted < minAge || converted > maxAge || checkIfNum(age) == 0)
    {
        printf("ERROR: age may only be an integer from 18 to 120, including. "
               "in line %d\n", glineCounter);
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
int checkCountry(char country[MAX_FIELD_LEN])
{
    if(checkString(country))
    {
        return 1;
    }
    else
    {
        printf("ERROR: country may only contain lower and upper case letters and '-'."
               " in line %d\n", glineCounter);
        return 0;
    }
}

/**
 * checks if the given city is legal.
 * @param country - value to check.
 * @return 1 if the value is lega, 0 otherwise.
 */
int checkCity(char city[MAX_FIELD_LEN])
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
 * calls all helper function which check legality of given input fields.
 * @return returns 6(1 for each input field) if all input fields are legal. another integer
 * otherwise.
 */
int legalCheck(char id[MAX_FIELD_LEN], char grade[MAX_FIELD_LEN], char age[MAX_FIELD_LEN],
        char name[MAX_FIELD_LEN], char country[MAX_FIELD_LEN], char city[MAX_FIELD_LEN])
{
    return idCheck(id) + nameCheck(name) + checkGrade(grade) + checkAge(age) +
    checkCountry(country) + checkCity(city);
}


/**
 * read the input given by user, call relevant function to check input legality and return best
 * student.
 */
void getBestStudent(){
    char grade[MAX_FIELD_LEN], age[MAX_FIELD_LEN], id[MAX_FIELD_LEN], name[MAX_FIELD_LEN],
    country[MAX_FIELD_LEN], city[MAX_FIELD_LEN], input[MAX_LINE_LEN],
    temp;
    while(1) {
        printf("Enter student info.  To exit press q, then enter\n");
        fgets(input, MAX_LINE_LEN, stdin);
        glineCounter++;
        sscanf(input, "%c", &temp);
        if (temp == quit) { // user is done giving input.
            break;
        }
        else
        {
            sscanf(input, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", id, name, grade, age,
                    country, city);
            if(legalCheck(id, grade, age, name, country, city) == LEGAL_INPUT)
            {
                
                Student tempStu = {.ID};
            }
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
