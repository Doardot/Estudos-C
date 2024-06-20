#include <stdio.h>

/*
Bitwise operators = operators that perform operations on bits
    & = bitwise AND
    | = bitwise OR
    ^ = bitwise XOR
    ~ = bitwise NOT
    << = bitwise left shift
    >> = bitwise right shift
*/

int main()
{
    int x = 6; // 6 = 0110 in binary
    int y = 12; // 12 = 1100 in binary
    int z = 0; // 0 = 0000 in binary

    z = x & y; // 0110 & 1100 = 0100
    // Both bits must be 1 for the result to be 1
    printf("AND = %d\n", z);

    z = x | y; // 0110 | 1100 = 1110
    // At least one bit must be 1 for the result to be 1
    printf("OR = %d\n", z);

    z = x ^ y; // 0110 ^ 1100 = 1010
    // If both bits are the same, the result is 0. If they are different, the result is 1
    printf("XOR = %d\n", z);

    z = ~x; // ~0110 = 1001
    // Flips the bits
    printf("NOT = %d\n", z);

    z = x << 1; // 0110 << 1 = 1100
    // Shifts the bits to the left
    printf("Left shift = %d\n", z);

    z = x >> 1; // 0110 >> 1 = 0011
    // Shifts the bits to the right
    printf("Right shift = %d\n", z);

    return 0;
}