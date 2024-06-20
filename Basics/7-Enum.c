#include <stdio.h>

enum Day
{
    Mon = 1,
    Tue = 2,
    Wed = 3,
    Thu = 4,
    Fri = 5,
    Sat = 6,
    Sun = 7
};

int main()
{
    enum Day today = Sun;

    if (today == Sun || today == Sat)
    {
        printf("It's the weekend!\n");
    }
    else
    {
        printf("It's a weekday!\n");
    }

    return 0;
}