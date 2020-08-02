#include <stdio.h>
#include <stdlib.h>

typedef struct Date Date;

struct Date {
    unsigned int day; // a number between 1 to 31
    unsigned int month; // a number between 1 to 12
    char * event;
    Date * next_date;
};

Date * create_date(unsigned int day,
                   unsigned int month, char * event)
{
    if (!(day >= 1 && day <= 31) ||
        !(month >= 1 && month <= 12) ||
        event == NULL) {
        return NULL;
    }
    Date * d = (Date *) malloc (sizeof(Date));
    if (d == NULL) {
        return NULL;
    }
    d->day = day;
    d->month = month;
    d->event = event;
    d->next_date = NULL;
    return d;
}

int are_equals(Date * date1, Date * date2)
{
    if(date1 == NULL || date2 == NULL) //invalid input.
    {
        return 0;
    }
    else
    {
        if(date1->day == date2->day && date1->month == date2->month)
        {
            /*dates are equal*/
            return 1;
        }
        return 0;
    }

}

void free_date(Date *date)
{
    if(date != NULL)
    {
        free(date);
        date = NULL;
    }
}

// part 2:
typedef struct Calendar {
    Date * first_date;
} Calendar;

void init_calendar(Calendar * c)
{
    c->first_date = NULL;
    return;
}

int add_to_calendar(Calendar * c, unsigned int day,
                    unsigned int month, char * event)
{
    Date* newDate = create_date(day, month, event);
    if(newDate == NULL)
    {
        return 0;
    }
    if(c->first_date ==NULL) //empty calendar
    {
        c->first_date = newDate;
        return 1;
    }
    Date* temp = c->first_date;
    if(are_equals(temp, newDate) == 1)
    {
        free_date(newDate);
        return 0;
    }
    while(temp->next_date != NULL)
    {
        if(are_equals(temp, newDate) == 1)//date exists
        {
            free_date(newDate);
            return 0;
        }
        temp = temp->next_date;
    }
    temp->next_date = newDate; //add date
    return 1;
}

/**
 * free all allocation made by calendar
 */
void free_calendar(Calendar * c)
{
    Date* temp;
    if(c->first_date == NULL) //empty calander, do nothing.
    {
        return;
    }
    while(c->first_date != NULL)
    {
        temp = c->first_date->next_date; //save rest of list
        free_date(c->first_date);
        c->first_date = temp;
    }
    c->first_date = NULL;
}

void print_calendar(Calendar * c)
{
    if (c == NULL) {
        return;
    }
    Date * current = c->first_date;
    while (current != NULL) {
        printf("%s\n", current->event);
        current = current->next_date;
    }
}
int main()
{
    Calendar c;
    init_calendar(&c);
    add_to_calendar(&c, 16, 8, "Exam_C");
    //print_calendar(&c);
    add_to_calendar(&c, 10, 6, "Exam_CPP");
    //print_calendar(&c);
    add_to_calendar(&c, 24, 6, "Exam_OOP");
    print_calendar(&c);
    free_calendar(&c);
}