#include "t_game.h"

#include <stdlib.h>

#include "c_main.h"

float T_RandomFloat(float min, float max)
{
    return ((float) rand() / RAND_MAX) * (max - min) + min;
}

void T_ProcessInput(const char* message)
{
    C_ProcessCommand(message);
}