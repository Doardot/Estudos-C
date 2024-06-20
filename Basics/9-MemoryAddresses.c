#include <stdio.h>

int main()
{
    /*
    memory = an array of bytes within RAM (street)
    memory block= a single unit (byte) within memory, used to hold some value (person)
    memory address = a unique identifier for a memory block,
                    the address of where a memory block is located (house adress)
    */

    char a;  // memory block 'a' is created
    a = 'X'; // 'X' is stored in memory block 'a'

    char b = 'Y';
    char c = 'Z';

    printf("%d bytes\n", sizeof(a));
    printf("%d bytes\n", sizeof(b));
    printf("%d bytes\n", sizeof(c));

    // %p is the format specifier for memory addresses
    printf("Memory address of a: %p\n", &a);
    printf("Memory address of b: %p\n", &b);
    printf("Memory address of c: %p\n", &c);
}