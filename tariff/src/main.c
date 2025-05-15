#include <stdio.h>

#include "t_game.h"

#include <string.h>

#define MAX_INPUT_LENGTH 512

int main(int argc, char** argv)
{
    char input[MAX_INPUT_LENGTH];

    //I_Init();

    while(1)
    {
        fgets(input, MAX_INPUT_LENGTH, stdin);
        input[strcspn(input, "\n")] = 0;
        T_ProcessInput(input);
    }
}