#include <stdio.h>
#include <stdlib.h>
#define VOWEL_COUNT 6

int compare(int index, char value)
{
    return (value == index);
}
int main(void)
{
        char response = 121;
        FILE* inputFile = NULL;
        char fileName[30];

        const char chars[8] = {97, 101, 105, 111, 121, 117, 32, 121};
        unsigned int other_count = 0; //Other character counts

        char current_char; 
        printf("Enter the name of the file: ");
        scanf("%s",&fileName);
        inputFile = fopen(fileName,"r");
        
        unsigned int *char_counts = 0;
        char_counts = (unsigned int*)calloc(8,sizeof(unsigned int)); //Array of counts

        int is_other = 1;
        while (!(feof(inputFile)))
        {
            fscanf(inputFile,"%c",&current_char);
            is_other = 1;
            for (int n=0;n<8;n++)
            {
                char_counts[n] += compare(chars[n], current_char);
                is_other -= compare(chars[n], current_char);

            }
            other_count += is_other;

        }
        for (int i=0;i<6;i++)
        {
            printf("The number of instances of character %c in the string is %u\n",chars[i],char_counts[i]);
        }
        printf("The number of instances of character space in the string is %u\n", char_counts[6]);
        printf("The number of instances of character tab in the string is %u\n",char_counts[7]);
        printf("The number of instances of other characters in the string is %u\n",other_count);
        free(char_counts); char_counts = NULL;
        fclose(inputFile);
        printf("Do you wish to count the characters in another file (y/n)? ");
        scanf("\n%c",&response);
        if (response == 121) main();
    return 0;
}
