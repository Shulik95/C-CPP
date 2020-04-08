#include <stdio.h>
#include <regex.h>
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

/**
 * the main running function for getting the best student, recieves input, calls needed methods to
 * check legality and returns the student if such exits.
 */
void getBestStudent()
{
    while(gStopFlag == 0)
    {
        char id, grade, age;
        int counter;
        char input[MAX_LINE_LEN], city[MAX_FIELD_LEN], name[MAX_FIELD_LEN], country[MAX_FIELD_LEN];
        printf("Enter student info.  To exit press q, then enter\n");
        fgets(input, MAX_LINE_LEN , stdin);
        sscanf(input, "%c, %[^,], %c, %c, %[^,], %[^\n]", &id, name, &grade, &age, country, city);
        if
    }
    printf("i get here, good job Shulik! :)");
}

/**
 * This function
 * @return
 */
int checkInput(){

}

int main(int argc, char* argv[]) {
    if(strcmp(BEST,argv[1]) == 0){
        getBestStudent();
    }
    return 0;
}
