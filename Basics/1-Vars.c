#include <stdio.h>

void vars()
{
    /*
    float = 4 bytes (32 bits of precision) 6 - 7 digits %f
    double = 8 bytes (64 bits of precision) 15 - 16 digits %lf

        double > float
        double is more precise than float

    char = 1 byte (true or false) %d
    unsigned char = 1 byte (0 to 255) %d or %c
    char[] = 1 byte (string) %s

        char c = 120;
        char c prints the character of ASCII value 120 using %c (character)
        char c prints the integer value of 120 using %d (integer)

    short = 2 bytes (-32,768 to 32,767) %d
    unsigned short = 2 bytes (0 to 65,535) %d

    int = 4 bytes (-2,147,483,648 to 2,147,483,647) %d
    unsigned int = 4 bytes (0 to 4,294,967,295) %u

    long = 4 bytes (-2,147,483,648 to 2,147,483,647) %ld
    unsigned long = 4 bytes (0 to 4,294,967,295) %lu

    long long = 8 bytes (-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807) %lld
    unsigned long long = 8 bytes (0 to 18,446,744,073,709,551,615) %llu
    */

    /*
    Format Specifiers
        %.1f = 1 decimal place
        %1 = 1 digit
        %- = left align
    */

    /*
    Constants
        fixed values that do not change during the execution of a program
        const float PI = 3.14;
    */

    int a = 5;
    printf("The value of a is %d\n", a);

    float b = 5.5;
    printf("The value of b is %.2f\n", b);
}

int main()
{
    vars();
    return 0;
}