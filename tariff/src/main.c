#include <stdio.h>

#include "t_game.h"
#include "t_usa.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_LENGTH 512

int main(int argc, char** argv)
{
    char input[MAX_INPUT_LENGTH];

    srand(time(NULL));

    T_InitUSA();

    printf("> ");

    while(1)
    {
        fgets(input, MAX_INPUT_LENGTH, stdin);
        input[strcspn(input, "\n")] = 0;
        T_ProcessInput(input);
    }
}