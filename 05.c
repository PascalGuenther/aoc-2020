#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct{
int row;
int column;
long int seat_id;
}ticket_t;

int compare2(ticket_t * a, ticket_t * b)
{
    return( a->seat_id - b->seat_id );
}

long int convert( char one, char zero, char *row)
{
    int i = 0;
    char * pEnd;
    while(row[i]!='\0')
    {
        if(row[i] == one)
            row[i]='1';
        else if(row[i] == zero)
            row[i]='0';
        i++;
    }
    return strtol(row, &pEnd, 2);
}

void day5(void)
{
    ticket_t all_tickets[1000];
    FILE* fo;
    char row[8];
    char seat[7];
    char* return1;
    char* return2;
    unsigned int i = 0;
    long int max_seat_id=0;
    char * pEnd;
    fo=fopen("inputs/input_day5.txt", "r");
    while(fgets(row,(int)8,fo))
    {
        return2=fgets(seat,(int)5,fo);
        //printf("Line:%s, Seat:%s\n", row, seat);
        all_tickets[i].row = convert('B', 'F', row);
        //printf("outp_row=%d\n",outp_row);
        all_tickets[i].column = convert('R','L',seat);
        //printf("outp_seat=%d\n",outp_seat);
        all_tickets[i].seat_id = all_tickets[i].row * 8 + all_tickets[i].column;
        if(all_tickets[i].seat_id>max_seat_id)
            max_seat_id = all_tickets[i].seat_id;
        //printf("seat_id=%d\n",seat_id);
        i++;
    }
    printf("Die h;chste seat-id war jetzt %ld\n", max_seat_id);
    qsort(all_tickets, i, sizeof(ticket_t), compare2);

    int last_seat=all_tickets[0].seat_id;
    for(int j = 0; j<i;j++)
    {
        int p = (all_tickets[j].seat_id - last_seat);
        if(abs(p) > 1)
        {
            float potential_seat_id = (last_seat + all_tickets[j].seat_id)/2;
            printf("seat-id missing! Your seat might potentially be %f\n", potential_seat_id);
        }
        last_seat = all_tickets[j].seat_id;
    }
        //printf("Row: %d, Column: %d, Seat-ID: %d\n", all_tickets[j].row, all_tickets[j].column, all_tickets[j].seat_id);
    getch();
}
