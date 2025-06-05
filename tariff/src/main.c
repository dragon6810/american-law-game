#include <stdio.h>

#include "t_game.h"
#include "t_usa.h"
#include "t_soviet.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_LENGTH 512

int main(int argc, char** argv)
{
    char input[MAX_INPUT_LENGTH];

    setvbuf(stdout, NULL, _IONBF, 0);

    printf("\033[2J\033[H");

    srand(time(NULL));

    T_InitGame();
    printf("> ");
    while(1)
    {
        fgets(input, MAX_INPUT_LENGTH, stdin);
        input[strcspn(input, "\n")] = 0;
        T_ProcessInput(input);
    }
}