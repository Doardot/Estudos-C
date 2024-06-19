#include <stdio.h>
#include <string.h>

/*
struct = collection of related members ("variables") that can be of different types
    - members can be accessed using the dot operator (.)
    - members can be accessed using the arrow operator (->) when using pointers

    very similar to classes in other languages (but without methods)
*/

struct Player
{
    char name[12];
    int score;
};

int main() {
    struct Player player1 = {"Edu", 100};
    struct Player player2 = {"Du", 50};

    // strcpy(player1.name, "Edu");
    // player1.score = 100;

    // strcpy(player2.name, "Du");
    // player2.score = 50;    
    
    //printf("%s has a score of %d\n", player1.name, player1.score);
    //printf("%s has a score of %d\n", player2.name, player2.score);

    // Array of structs
    struct Player players[2] = {player1, player2};
    for(int i = 0; i < 2; i++) {
        printf("%s has a score of %d\n", players[i].name, players[i].score);
    }

    return 0;
}