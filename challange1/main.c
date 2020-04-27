
#include <math.h>
#include <stdio.h>



int normalize(double* data[], int len)
{
    double sum = 0;
    for(int i = 0; i < len; i++)
    {
        double temp = fabs(*data[i]);
        sum += temp;
    }
    if(sum == 0) // cant normalize
    {
        return 0;
    }
    for(int j = 0; j < len; j++)
    {
        *data[j] = fabs(*data[j]) / sum;
    }
    return 1;
}

int main()
{
    double x0 = -0.3, x1 = -13, x2 = -0.3, x3 = 551, x4 = 11;

    double* data[5] = {&x0, &x1, &x2, &x3, &x4};
    int len = 5;
    normalize(data, len);
    for(int i = 0; i < len; i++)
    {
        printf("%f ",*data[i]);
    }
}