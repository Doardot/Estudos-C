#include <stdio.h>

void printAge(int *pAge)
{
    printf("You are %d years old\n", *pAge);
}

int main()
{
    // Pointers = "variable-like" reference that holds the memory address of another variable

    int age = 19;
    int *pAge = NULL; // good practice to assign NULL if declaring a pointer
    pAge = &age;      // Pointer to the memory address of 'age'

    printf("Address of age: %p\n", &age);
    printf("Value of pAge: %p\n", pAge);

    printf("Size of age: %d bytes\n", sizeof(age));
    printf("Size of pAge: %d bytes\n", sizeof(pAge));

    printf("Value of age: %d\n", age);
    printf("Value at stored address: %d\n", *pAge); // Dereferencing the pointer
    // Dereferencing = accessing the value at the memory address stored in the pointer

    printAge(pAge);

    return 0;
}