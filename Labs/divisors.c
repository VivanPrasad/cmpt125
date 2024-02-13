#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
    unsigned short int min, max, divisor;
    unsigned int factor_sum = 0; // Sums of shorts may range int.
    unsigned int coprime_sum = 0;
    printf("Enter the smallest integer to consider as part of the sum: ");
    scanf("%hu",&min);
    printf("Enter the largest integer to consider as part of the sum: ");
    scanf("%hu",&max);
    printf("Enter the divisor of interest: ");
    scanf("%hu",&divisor);

    if (max < min) // Integer range error
    {
        printf("\nNo integers larger than %hu and smaller than %hu", min, max);
        return 1;
    }

    if (divisor == 0) // Divide by zero error
    {
        printf("\nDivisor is 0, Cannot divide by 0: ERROR");
        return 1;
    }
    
    if (divisor > max) // Divisior range warning
    {
        printf("\nDivisor is larger than largest integer,\n");
    } else printf("\nThe numbers between 5 and 100 that are divisible by 7 are: \n");

    short factor_count = 0;
    for (int n=min;n<=max;n++) // Procedural O(n) checking
    {
        if ((n%divisor) == 0) // If divisible by the divisor
        {
            printf("%hu, ",n);
            factor_sum += n;
            factor_count += 1;
            if ((factor_count%5)==0) printf("\n");
        } else coprime_sum += n; // Add non-divisible numbers to running sum
    }
    
    // Checking to print sums
    if (factor_count==0) printf("no integers are exactly divisible by %hu\n\n",divisor);
    else 
    {
        printf("The sum of all integers between %hu and %hu\n",min,max);
        printf("that are divisible by %hu is %u\n\n",divisor,factor_sum);
    }
    
    printf("The sum of all integers between %hu and %hu\n",min,max);
    printf("that are not divisible by %hu is %u",divisor,coprime_sum);
    return 0;
}