#include <stdio.h>
double calculateVolume(double radius, double length)
{
    //constant value for PI
    const double PI = 3.141592653;
    return (PI * radius * radius * length);
}
int main(void) 
{
    double radius = 0;
    double length = 0;
    double volume = 0;
    printf("Please enter a value for the radius of the cylinder: ");
    scanf("%lf", &radius);
    printf("Please enter a value for the length of the cylinder: ");
    scanf("%lf", &length);

    volume = calculateVolume(radius, length);
    printf("\nThe volume of the cylinder with radius %.3lf and length %.3lf is %.3lf",radius,length,volume);
    return 0;

}