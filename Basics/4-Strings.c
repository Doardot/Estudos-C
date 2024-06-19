#include <stdio.h>
#include <string.h>

int main() {
    char string1[] = "Hello";
    char string2[] = "World";

    strlwr(string1); // Converts string1 to lowercase
    strupr(string2); // Converts string2 to uppercase
    strcat(string1, string2); // Appends string2 to end of string1
    strcpy(string1, string2); // Copies string2 to string1
    strncpy(string1, string2, 3); // Copies first 3 characters of string2 to string1

    strset(string1, 'a'); // Sets all characters in string1 to 'a'
    strnset(string1, 'b', 3); // Sets first 3 characters in string1 to 'b'
    strrev(string1); // Reverses string1

    int length = strlen(string1); // Returns the length of string1

    int compare = strcmp(string1, string2); // Compares string1 and string2
    int compareN = strncmp(string1, string2, 3); // Compares first 3 characters of string1 and string2

    int compareCase = strcmpi(string1, string2); // Compares string1 and string2 ignoring case
    int compareCaseN = strnicmp(string1, string2, 3); // Compares first 3 characters of string1 and string2 ignoring case

    if (compare == 0) {
        printf("The strings are equal\n");
    } else {
        printf("The strings are not equal\n");
    }

    printf("%d", compare);
}