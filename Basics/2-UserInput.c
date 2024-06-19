#include <stdio.h>
#include <string.h>

int main()
{
    int age;
    char name[20];

    printf("Enter your name: ");
    // scanf("%s", name);
    fgets(name, 20, stdin);        // fgets is used to read strings with spaces
    name[strlen(name) - 1] = '\0'; // remove the newline character

    printf("Enter your age: ");
    scanf("%d", &age); // & is the address of operator

    printf("Your name is %s\n", name);
    printf("You are %d years old\n", age);
}