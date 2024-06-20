#include <stdio.h>

int main()
{
    FILE *pF = NULL;
    pF = fopen("test.txt", "r");
    // use a absolute path to the file if it is not in the same directory as the executable

    char buffer[100]; // buffer to store the content of the file

    if (pF == NULL)
    {
        printf("File not found\n");
    }
    else
    {
        while (fgets(buffer, 100, pF) != NULL) // read the first 100 characters of the file and store them in the buffer
        {
            printf("%s", buffer);
        }
        fclose(pF);
    }

    return 0;
}