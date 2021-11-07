/**< sample of puzzles */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void print_space(int i)
{
        for(int j=0; j<i;j++)
        {
            printf(" ");
        }
}

int init_day3()
{
    long long int result = 1;
    result *= (long long int)run_day3(1,1);
    result *= (long long int)run_day3(3,1);
    result *= (long long int)run_day3(5,1);
    result *= (long long int)run_day3(7,1);
    result *= (long long int)run_day3(1,2);
    printf("result=%lli", result);
    getch();
    return 0;
}

int run_day3(int right, int down)
{
    //int fgets_ret_val = 1;
    char line[255];
    //int line_num=0;
    int i = 1, j=right, tree_count = 0;
    FILE *fo;
    fo = fopen("inputs/input_day3.txt", "r");
    fgets(line, 255, (FILE*)fo);
    //printf("%s", line);
    while(1)
    {
        for(int k=0; k < down;k++)
        {
            if(fgets(line, 255, (FILE*)fo) == NULL)
                {
                    printf("tree_count with %d right, %d down: %d\n", right, down, tree_count);
                    return tree_count;
                }
        }
        //printf("%s", line);
        //print_space(j);
        //printf("%c", line[j]);
        if(line[j]=='#')
        {
            tree_count++;
            //printf("%i", tree_count);
        }
        //printf("\n");
        for(int k = 0; k < right ; k++)
        {
            j++;
            if(line[j] == '\n')
            {
                j=0;
            }
        }
        i++;
    }

    printf("tree_count with %d right, %d down: %d\n", right, down, tree_count);
    getchar();
    return tree_count;
}
