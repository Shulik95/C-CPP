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
#define MAX_LINE_LEN 100
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
typedef struct Student
{
    long ID;
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
int checkIfNum(const char input[MAX_FIELD_LEN])
{
    for(unsigned int i = 0; i < strlen(input); i++)
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
        printf("ERROR: id must be exactly 10 digits and may not start with a 0\n"
               "in line %d\n", glineCounter);
        return 0; //first number is 0;
    }
    return 1;
}

int nameCheck(char name[MAX_FIELD_LEN])
{
    for(unsigned int i = 0; i < strlen(name); i++)
    {
        if ((isalpha(name[i]) != 0) || (name[i] == 32) || (name[i] == 45))
        {
            continue;
        }
        else
        {
            printf("ERROR: a name may only contain letter - both lower and upper case, "
                   "spaces and '-'.\n in line %d\n", glineCounter);
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
        printf("ERROR: grade may only be an integer from 0 to 100, including.\n "
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
        printf("ERROR: age may only be an integer from 18 to 120, including.\n "
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
    for(unsigned int i = 0; i < strlen(string); i++)
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
        printf("ERROR: country may only contain lower and upper case letters and '-'\n."
               "in line %d\n", glineCounter);
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
    printf("ERROR: city may only contain lower and upper case letters and '-'.\n"
           "in line %d\n", glineCounter);
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
    if(!idCheck(id) || !nameCheck(name) || !checkGrade(grade) || !checkCountry(country) || !checkAge(age) ||
    !checkCity(city))
    {
        return 0;
    }
    return LEGAL_INPUT;
}

/**
 * finds the best grade/age ratio for each student on the list.
 * @return
 */
long findBestRatio()
{
    if(gStudentCounter == 0) // no legal values were given, do nothing like shimon said
    {
        return 0;
    }
    long bestIndex = 0;
    double bestRatio = 0;
    for(int i = 0; i < gStudentCounter; i++)
    {
        Student temp = gStudentList[i];
        double tempRatio = (double)temp.grade / (double)temp.age;
        if(tempRatio > bestRatio)
        {
            bestIndex = temp.counter;
            bestRatio = tempRatio;
        }
    }
    return bestIndex;
}

/**
 * signs up student, assumes legality has been checked before.
 */
void signStudent(char id[MAX_FIELD_LEN], char grade[MAX_FIELD_LEN], char age[MAX_FIELD_LEN],
                char name[MAX_FIELD_LEN], char country[MAX_FIELD_LEN], char city[MAX_FIELD_LEN])
{
    char *remain;
    long tempID = strtol(id, &remain, 10);
    long int tempGrade = strtol(grade, &remain, 10);
    long int tempAge = strtol(age, &remain, 10);
    Student tempStu = {.ID = tempID, .counter = gStudentCounter, .grade = tempGrade, .age = tempAge};
    strcpy(tempStu.name, name);
    strcpy(tempStu.country, country);
    strcpy(tempStu.city, city);
    gStudentList[gStudentCounter] = tempStu; // assign student into list.
    gStudentCounter++;
}

/**
 * this function takes input from the user and checks legality, if the input is legal, the student is registered.
 */
void readStudents()
{
    char grade[MAX_FIELD_LEN], age[MAX_FIELD_LEN], id[MAX_FIELD_LEN], name[MAX_FIELD_LEN],
            country[MAX_FIELD_LEN], city[MAX_FIELD_LEN], input[MAX_LINE_LEN],
            temp;
    while(1)
    {
        printf("Enter student info. To exit press q, then enter\n");
        fgets(input, MAX_LINE_LEN, stdin);
        sscanf(input, "%c", &temp);
        if (temp == quit)
        { // user is done giving input.
            break;
        }
        else
        {
            sscanf(input, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", id, name, grade, age,
                   country, city);
            if(legalCheck(id, grade, age, name, country, city) == LEGAL_INPUT)
            {
                signStudent(id, grade, age, name, country, city);
            }
            glineCounter++;
        }
    }
}

/**
 * read the input given by user, call relevant function to check input legality and return best
 * student.
 */
void getBestStudent()
{
    readStudents();
    if(gStudentCounter != 0)
    {
        long bestStudentIndex = findBestRatio();
        Student bestStudent = gStudentList[bestStudentIndex];
        printf("best student info is: %ld,%s,%ld,%ld,%s,%s\n", bestStudent.ID, bestStudent.name,
               bestStudent.grade, bestStudent.age, bestStudent.country, bestStudent.city);
    }
}

/**
 * merges 2 sorted array of size n/2 into a sorted array of size n.
 * @param studentList - array of student structs to sort.
 * @param left - left index to start sorting from.
 * @param mid - right index of left array part.
 * @param right - right index of right array part.
 */
void merge(Student studentList[], int left, int mid, int right)
{
    int i = 0, j = 0, k = left; //i&j run through arrays. k keeps track of merged index.
    int leftArrSize = mid - left + 1;
    int rightArrSize = right - mid;

    Student leftArr[MAX_STUDENT_NUM], rightArr[MAX_STUDENT_NUM]; //init subarrays of constant size.
    for(int l = 0; l < rightArrSize; l++)
    {
        rightArr[l] = studentList[mid + 1 + l]; //copy data into right array, start from m+1 cause m is in leftArray.
    }
    for(int p = 0; p < leftArrSize; p++)
    {
        leftArr[p] = studentList[left + p]; // copy data into left array
    }
    while((i < leftArrSize) && (j< rightArrSize)) // there are still items in both arrays.
    {
        if(leftArr[i].grade < rightArr[j].grade)
        {
            studentList[k] = leftArr[i];
            i++;
        }
        else // rightArr[j].grade <= leftArr[i].grade
        {
            studentList[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while(j < rightArrSize) //all elements from leftArr have been inserted, insert whats left in rightArr
    {
        studentList[k] = rightArr[j];
        j++;
        k++;
    }
    while( i < leftArrSize) //all elements from rightArr have been inserted, insert whats left in leftArr
    {
        studentList[k] = leftArr[i];
        i++;
        k++;
    }
}

/**
 * sorts a given array of student structs.
 * @param studentArray - array to sort.
 * @param left - left index to sort from.
 * @param right - right index to sort to.
 */
void mergeSort(Student studentArray[], int left, int right)
{
    if(left < right) // checks for base case which is array of size 1.
    {
        int mid = (left + right) / 2;
        mergeSort(studentArray, left, mid);
        mergeSort(studentArray, mid + 1, right);
        merge(studentArray, left, mid, right);
    }
}

/**
 * sorts students by grade using mergeSort and prints their info.
 */
void sortByGrade()
{
    int left = 0, right;
    readStudents();
    right = gStudentCounter;
    mergeSort(gStudentList, left, right);
    for(int i = 0; i < gStudentCounter; i++)
    {
        Student currStudent = gStudentList[i];
        printf("%ld,%s,%ld,%ld,%s,%s\n", currStudent.ID, currStudent.name,
               currStudent.grade, currStudent.age, currStudent.country, currStudent.city);
    }
}

int main(int argc, char* argv[])
{
    if(argc == 1 || argc > 2) //no arguments/to many arguments were given.
    {
        return 1;
    }

    if(strcmp(BEST, argv[1]) == 0)
    {
        getBestStudent();
        return 0;
    }
    else if(strcmp(MERGE, argv[1]) == 0) //sort according to grades.
    {
        sortByGrade();
        return 0;
    }
    else if(strcmp(QUICK, argv[1]) == 0) // sort alphabetically by name.
    {
        return 0;
    }
    else // the input doesnt fit any of the options.
    {
        printf("USAGE: illegal input, choose between best, merge or quick\n");
        return 1;
    }
}
