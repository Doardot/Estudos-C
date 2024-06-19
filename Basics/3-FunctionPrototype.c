#include <stdio.h>

void hello(char[], int);
/* A function prototype is a declaration of a function that tells the program
about the function name, return type, and parameters.

It causes the compiler to flag an error if arguments are missing. */

int main()
{
    char name[] = "Edu";
    int age = 19;

    hello(name, age);

    return 0;
}

void hello(char name[], int age)
{
    printf("Hello, %s! You are %d years old.\n", name, age);
}