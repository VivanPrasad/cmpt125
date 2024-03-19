#include <stdio.h>
#include <string.h>

int main(void){

    char string1[] = "Vivan";
    char string2[] = "Prasad";

    

    short length = strlen(string1);

    strlwr(string1); // lowercases the string to 'vivan'
    printf("%s",string1);

    return 0;
}