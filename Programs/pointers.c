
// Pointers
#include <stdio.h>

int main(void) {
    double *num1p = NULL; //pointing to address -1 if NULL/undeclared (no address)

    printf("%lf\n",num1p);

    double number2 = 1.0;
    double number1 = 0.0, *number1p; //initialize pointer after variable declaration
    
    num1p = &number1; // gets address of number1
    //since it is pointing to number1, it is 0.0
    num1p = &number2;
    number2 = *num1p; 
    number2 += 2.0; // number2 becomes 3.0

    printf("%lf\n",number2); // since it is pointing to number2, it is 1.0+2.0=3.0

    return 0;
}