#include <stdio.h>

int main()
{
    /*
    w = write mode (it can be used to create a new file or overwrite an existing file)
    a = append mode (it can be used to create a new file or add to an existing file)
    r = read mode (it can be used to read an existing file)
    */
    FILE *pF = NULL;
    pF = fopen("test.txt", "w");

    fprintf(pF, "Hello, World!\n");

    fclose(pF);

    // Deleting the file
    // if (remove("test.txt") == 0)
    // {
    //     printf("File deleted successfully\n");
    // }
    // else
    // {
    //     printf("Error deleting file\n");
    // }

    return 0;
}