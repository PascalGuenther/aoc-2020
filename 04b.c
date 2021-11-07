#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <inttypes.h>

#ifdef DAY4B
#pragma message("C Preprocessor got here")
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

typedef struct{
char key[4];
char value[50];
}KeyValPair;

typedef struct{
KeyValPair fields[8];
int NoOfFields;
}Passport;

Passport Passport_init(Passport passport)
{
    for(int i = 0; i<8;i++)
    {
        passport.fields[i].key[0] = "\0";
        passport.fields[i].value[0] = NULL;
    }
    passport.NoOfFields = 0;
return passport;
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

    while(data[i]!='\n')
    {
        char key[4], value[50];
        int n;
        char *line = data;
        int l = 0;
        Passport CurrentPP;
        while(sscanf(line, " %[^: \n]:%s%n", key, value, &n)==2)
        {
            strcpy(CurrentPP.fields[l].key, key);
            strcpy(CurrentPP.fields[l].value, value);
            CurrentPP.NoOfFields = l++;
            line += n;
        }
        printf("Key: %s Value: %s", key, value);
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

int check_passport(const char* key, const char* val)
{
    if(!strcmp(key, "byr"))
    {
        if(strlen(val)!=4)
            return 0;
        unsigned long byr = strtoul(val, NULL, 10);
        if(byr < (int)1920 || byr > (int)2002)
            {
                printf("byr:%lu\n", byr);
                return 0;
            }
        else
            return 1;
    }
    else if(!strcmp(key, "iyr"))
    {
        if(strlen(val)!=4)
            return 0;
        unsigned long iyr = strtoul(val, NULL, 10);
        if(iyr < (int)2010 || iyr > (int)2020)
        {

                printf("iyr:%lu\n", iyr);
                return 0;
        }
        else
            return 1;
    }
    else if (!strcmp(key, "eyr"))
    {
        if(strlen(val)!=4)
            return 0;
        unsigned long eyr = strtoul(val, NULL, 10);
        if(eyr < 2020 || eyr > 2030)
            {
                printf("eyr:%lu\n", eyr);
                return 0;
            }
        else
            return 1;
    }
    else if(!strcmp(key, "hgt"))
    {
        unsigned int hgt = 0;
        char unit[3];
        sscanf(val, "%u%s", &hgt, unit);
        if(!strcmp(unit, "cm"))
        {
            if(hgt < 150 || hgt > 193)
            {
                printf("hgt:%d%s\n", hgt, unit);
                return 0;
            }
            else
                return 1;
        }
        else if(!strcmp(unit, "in"))
        {
            if(hgt < 59 || hgt > 76)
            {
                printf("hgt:%d%s\n", hgt, unit);
                return 0;
            }
            else
                return 1;
        }
        else
        {
            printf("hgt:%d%s\n", hgt, unit);
            return 0;
        }
    }
    else if(!strcmp(key, "hcl"))
    {
        char hashkey, colorstring[10];
        unsigned int color=0;
        sscanf(val, "%c%x",&hashkey, &color);
        if(hashkey!='#')
        {
            printf("hcl:%c%d\n", hashkey, color);
            return 0;
        }
        else if(color <= 0xffffff)
        {
            sscanf(val, "#%s", colorstring);
            if(strlen(colorstring)==6)
                return 1;
            else
                {
                printf("hcl:%c%d\n", hashkey, color);
                return 0;
                }
        }
        else
        {
            printf("hcl:%c%d\n", hashkey, color);
            return 0;
        }
    }
    else if(!strcmp(key,"ecl"))
    {
        if(!strcmp(val,"amb")
           || !strcmp(val, "blu")
           || !strcmp(val, "brn")
           || !strcmp(val, "gry")
           || !strcmp(val, "grn")
           || !strcmp(val, "hzl")
           || !strcmp(val, "oth"))
            return 1;
        else
        {
            printf("ecl=%s\n", val);
            return 0;
        }
    }
    else if(!strcmp(key,"pid"))
    {
        char pidcheck[10];
        int length = 0;
        sscanf(val,"%[0123456789]",pidcheck);
        length = strlen(pidcheck);
        if(length == 9)
            return 1;
        else
        {
            printf("pid:%s\n",val);
            return 0;
        }

    }
    else if(!strcmp(key, "cid"))
        return 0;
    else
        return 0;
}

void day4()
{
    FILE *fo;
    //struct db_entry persons[300]={};
    //int len_db_entry = sizeof(struct db_entry);
    char buf[256];
    fo = fopen("inputs/input_day4.txt", "r");
    int count=0, num_count_valid_pps=0;
    char *m;
    Passport CurrentPP = Passport_init(CurrentPP);
    do
    {
        m = fgets(buf, sizeof buf, fo);
        //printf("%s", buf);
        if(!strcmp(buf,"\n") || m==NULL)
        {
            if(count >= 7)
                num_count_valid_pps++;
            CurrentPP = Passport_init(CurrentPP);
            count = 0;
        }
        else
        {
            char key[4], value[50];
            int n;
            char *line = buf;
            int l = 0;
            while(sscanf(line, " %[^: \n]:%s%n", key, value, &n)==2)
            {
                if(!check_passport(key, value))
                {
                    line += n;
                    continue;
                }
                else
                {
                    strcpy(CurrentPP.fields[l].key, key);
                    strcpy(CurrentPP.fields[l].value, value);
                    count++;
                    CurrentPP.NoOfFields = l++;
                    line += n;
                }
            }
        }
    }while(m!=NULL);
    printf("Number of valid passports: '%d'\n",num_count_valid_pps);
    getch();
}
#endif // DAY4B


