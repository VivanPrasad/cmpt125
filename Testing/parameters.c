#include <stdio.h>

void birthday(char name[],int age)
{
    printf("\nHappy birthday dear %s!",name);
    printf("\nYou are %d years old! Congrats!", age);
}

int main(void)
{
    char name[] = "Bro";
    short int age = 21;
    
    birthday(name,age);
    return 0;
}
