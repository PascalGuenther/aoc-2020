#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
//for stringtoumax():
#include <inttypes.h>

#ifdef DAY4A
#include "inputs/04a.h"
#pragma message("Got Here")
struct db_entry{
unsigned int byr;
unsigned int iyr;
unsigned int eyr;
char hgt[20];
char hcl[20];
char ecl[20];
char pid[20];
char cid[20];
};

void day4()
{
    FILE *fo;
    char data[10][255];
    char buf[255];
    char profile[1024];
    fo = fopen("inputs/input_day4.txt", "r");
    static int j=1;
    for(int i=0; i<10; i++)
    {
        char* p = fgets(buf, sizeof buf, fo);
        int m = strcmp(buf,"\n");
        if(!strcmp(buf,"\n"))
        {
            printf("\nPassport Dataset %d:\n", j);
            j++;
        }
        strcpy(data[i],&buf);
        printf("i=%d, %s Result strcmp: '%d'", i, data[i], m);
    }
    getch();
}

struct db_entry fill_database(char *data, struct db_entry *person)
{
    int i=0, j=0, k=0;
    char entry[128];
    char left[32], right[64];
    *person = (struct db_entry){
        .byr=0,
        .iyr=0,
        .eyr=0,
        .hgt={[0 ... 19]='\0'},
        .hcl={[0 ... 19]='\0'},
        .ecl={[0 ... 19]='\0'},
        .pid={[0 ... 19]='\0'},
        .cid={[0 ... 19]='\0'}
    };

    while(data[i]!='\0')
    {
        j=0;
        while(data[i]!='\0' && data[i]!='\n' && data[i]!=' ')
        {
            entry[j]=data[i];
            i++;
            j++;
        }
        i++;
        entry[j]='\0';
        j=0;
        while(entry[j]!=':')
        {
            left[j]=entry[j];
            j++;
        }
        left[j]='\0';
        k=0;
        while(entry[j]!='\0' && entry[j]!='\n' && entry[j]!=' ')
        {
            j++;
            right[k]=entry[j];
            k++;
        }
        right[k]='\0';
        if(!strcmp("byr", left))
            person->byr=strtoumax(right,NULL, 10);
        else if(!strcmp("iyr", left))
            person->iyr=strtoumax(right,NULL,10);
        else if(!strcmp("eyr",left))
            person->eyr=strtoumax(right,NULL,10);
        else if(!strcmp("hgt",left))
            strcpy(person->hgt, right);
        else if(!strcmp("hcl",left))
            strcpy(person->hcl, right);
        else if(!strcmp("ecl",left))
            strcpy(person->ecl, right);
        else if(!strcmp("pid",left))
            strcpy(person->pid, right);
        else if(!strcmp("cid",left))
            strcpy(person->cid, right);
    }
    return *person;

}
int check_valid_passports(struct db_entry *persons)
{
    int i=0,j=0, count=0;
    while(i<300)
    {
        if(persons[i].byr!=0
           && persons[i].iyr!=0
           && persons[i].eyr!=0
           && persons[i].hgt[0]!='\0'
           && persons[i].ecl[0]!='\0'
           && persons[i].hcl[0]!='\0'
           && persons[i].pid[0]!='\0')
            count++;
        else
            j++;
        i++;
    }
    printf("falsche Dokumente:'%d'\n",j);
    return count;
}
void init_day4()
{
    FILE *fo;
    struct db_entry persons[300]={};
    int len_db_entry = sizeof(struct db_entry);
    char data[1000][256];
    char buf[256];
    char passport[2048];
    fo = fopen("inputs/input_day4.txt", "r");
    static int j=1;
    int i = 0;
    strcpy(data[i],"");
    while(fgets(buf, sizeof buf, fo)!=NULL)
    {
        strcat(data[i],&buf);
        int m = strcmp(buf,"\n");
        if(!strcmp(buf,"\n"))
        {
            persons[i] = fill_database(data[i],&persons[i]);
            i++;
            strcpy(data[i],"");
        }
    }
    persons[i] = fill_database(data[i], &persons[i]);
    printf("\nPassport Dataset %d:\n %s", i, data[i]);
    int count = check_valid_passports(persons);
    printf("Number of valid passports: '%d'\n",count);
    getch();
}
#endif // DAY4A
