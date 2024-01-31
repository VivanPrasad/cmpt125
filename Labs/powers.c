#include <stdio.h>
#include <math.h>

void displayTable(float value, float increment, int rows) 
{
    for (int row=1; row <= rows; row++) 
    {
        for (int column=1; column <= 3; column++) 
        {
            float power = pow(value, column);
            int digits = 4;
            
            switch (column)
            {
                case 1: printf("%-+16.4f",power); break;
                case 2: printf("%-+16.3f",power); break;
                case 3: printf("%-.5e",power); break;
                default: break;
            }
        }
        value += increment;
        printf("\n");
    }
}
int main(void) 
{
    float value = 0.0;
    float increment = 0.0;
    int rows = 1; //Number of Rows
    
    printf("Please enter the value of X: ");
    scanf("%f", &value);
    
    printf("Please enter the value of the increment between X on successive rows: ");
    scanf("%f", &increment);
    
    printf("Please enter the number of rows: ");
    scanf("%i", &rows);

    displayTable(value,increment,rows);

    return 0;
}