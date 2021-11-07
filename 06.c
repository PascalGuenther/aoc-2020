#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define ALPHANUM_OFFS_ASCII 97

void day6(void)
{
    FILE* fo;
    char line[100];
    char letters[26];
    unsigned int count=0, temp_count=0;
    memset(letters,'\0',26);
    fo = fopen("inputs/input_day6.txt", "r");
    while(fgets(line,100,fo)!=NULL)
    {
        if(line[0]=='\n')
            {
                count+=temp_count;
                temp_count = 0;
                memset (letters,'\0',26);
            }
        else
        {
            int i = 0;
            while(line[i]!='\n'&&line[i]!='\0')
            {
                int num_dec_letter = (int)line[i] - (int)ALPHANUM_OFFS_ASCII;
                if(line[i]!=letters[num_dec_letter])
                {
                    letters[num_dec_letter]=line[i];
                    temp_count++;
                }
                i++;
            }
        }
    }
    count+=temp_count;
    printf("Number: %d", count);
    getch();
}
