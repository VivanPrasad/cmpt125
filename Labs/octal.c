#include <stdio.h>
#include <stdlib.h>

void convertToOctal(unsigned int decimalInteger); 

int main(void)
{
    int integer;
    printf("enter the decimal integer to convert to octal: ");
    scanf("%d",&integer);
    printf("the decimal integer read is: %d\n",integer);
    printf("Starting conversion to octal\n");
    printf("The equivalent octal number is ");
    convertToOctal(integer);
    return 0;
}
void convertToOctal(unsigned int decimalInteger)
{
    if (decimalInteger > 0)
    {
        convertToOctal(decimalInteger / 8);
        printf("%d",decimalInteger % 8);
    }
    else return; // Base Case
}
