#include <stdio.h>
#include <conio.h>
#include "inputs/03.h"
#include "inputs/04a.h"
#include "inputs/04b.h"
//#include "examples/day4_examples.h"

int main()
{
#ifdef DAY3
    init_day3();
#endif // DAY3
#ifdef DAY4A
    init_day4();
    day4();
#endif // DAY4A
#ifdef DAY4B
    day4();
#endif // DAY4B
#ifdef DAY5
    day5();
#endif // DAY5
#ifdef DAY6
    day6();
#endif // DAY6
    return 0;
}


