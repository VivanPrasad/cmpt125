#include <stdio.h>
#include <math.h>

int main(void){

    const double PI = 3.141592653589;
    double A = sqrt(9); //3.000000
    double B = pow(2, 4); //16.000000

    short int C = round(3.14); //3
    short int D = ceil(3.14); //4
    short int E = floor(3.99); //3

    double F = fabs(-100); //100.000000
    double G = log(3); //1.098612
    double H = sin(PI); //0.000000
    double I = cos(PI); //-1.000000
    double J = tan(PI/2); //-1.00000

    printf("\n%lf",J);
    return 0;
}