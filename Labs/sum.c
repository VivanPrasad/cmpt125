#include <stdio.h>
#include <stdlib.h>

double mySum(double X, unsigned int N);
double printSum(double X, unsigned int N);

int main(void)
{
    double value = 0.3333;
    double num_values = 10;
    printSum(value,num_values);
    return 0;
}

double mySum(double X, unsigned int N)
{
    if (N>0) return X + mySum(X+1.0,N-1);
    else return X;
}
double printSum(double X, unsigned int N)
{
    printf("%5s%19s%19s%19s\n",
"X","sum X to X+3","1/(sum X to X+5)","sum X to X+7");
    double x, sum_x3, sum_x5_inv, sum_x7;
    for (unsigned int n=0; n<N;n++)
    {
        x = X + n;
        sum_x3 = mySum(x,3);
        sum_x5_inv = 1 / mySum(x,5);
        sum_x7 = mySum(x,7);
        printf("%5.3lf%19.3lf%19.4e%19.3lf\n",x,sum_x3,sum_x5_inv,sum_x7);
    }
}