#include <stdio.h>
#include <string.h>

/*
typedef = reserved keyword that gives an existing datatype a "nickname"
*/

typedef struct
{
    char name[12];
    int score;
} Player;

int main()
{
    Player player1 = {"Edu", 100};
    Player player2 = {"Du", 50};

    printf("%s\n", player1.name);
    printf("%d\n", player1.score);

    printf("%s\n", player2.name);
    printf("%d\n", player2.score);
}