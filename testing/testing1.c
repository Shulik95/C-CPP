//
// Created by user on 21-Apr-20.
//


#include <stdio.h>

void reset (int* arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        *arr[i] = 0;
    }
}

int main()
{
    int a = 1, b = 2;
    int* arr[] = {&a, &b};
    reset(arr, 2);
    printf("%d %d", a, b);
    return 0;
}

