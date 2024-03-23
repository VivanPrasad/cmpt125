#include <stdio.h>
#include <stdlib.h>

struct Assignment
{   
    double grade;  
    int numQuestions;
    int questionNum;    
    char date[10];  
};
int  main( )
{    
    struct Assignment A= { 98.4, 12, 4, 10102014 };
    A.questionNum = 5;
    printf("%s   %lf  %d",  A.date,  A.grade,  A.questionNum);
    return 0;
}

 