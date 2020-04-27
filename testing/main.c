
#include <stdio.h>

void reset (int* arr[], int n)
{
for (int i = 0; i < n; i++)
{
*arr[i] = 0;
}
}

int main(argc, argv[1])
{
    int a = 1, b = 2;
    int* arr[] = {&a, &b};
    reset(arr, 2);
    printf("%d %d", a, b);
    return 0;
}
