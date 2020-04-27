#include <stdio.h>
#include <stdlib.h>

/**
 * @param argc - the amount of arguments we received.
 * @param argv - the arguments from the user.
 * @return - returns 0 but output is prints.
 */
int main(int argc, char* argv[])
{
    const int a = 5;
    const int *ptr;
    ptr = &a;
    *ptr = 10;
    printf("%d", a);
    return 0;
}

