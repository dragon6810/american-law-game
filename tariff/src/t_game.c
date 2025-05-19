#include "t_game.h"

#include <stdlib.h>

#include "c_main.h"
#include "t_soviet.h"
#include "t_usa.h"

float T_RandomFloat(float min, float max)
{
    return ((float) rand() / RAND_MAX) * (max - min) + min;
}

void T_ProcessInput(const char* message)
{
    C_ProcessCommand(message);
}

void T_InitGame(void)
{
    T_InitUSA();
    T_InitSoviet();
}

void T_UpdateEconomy(void)
{
    float addecousa, addecosoviet;

    addecousa = T_RandomFloat(-6, 6);
    addecosoviet = T_RandomFloat(-6, 6);

    addecousa += usa_outlets[OUTLET_SELL] / 100.0 * USA_PRODUCTION * 1.0;
    addecousa += usa_outlets[OUTLET_CIRCULATE] / 100.0 * USA_PRODUCTION * 0.3;

    usa_stockmarket += addecousa;
    soviet_secrets[SOVIET_SECRET_ECONOMY] += addecosoviet;

    if(usa_stockmarket > 100)
        usa_stockmarket = 100;
    if(usa_stockmarket < 0)
        usa_stockmarket = 0;
    if(soviet_secrets[SOVIET_SECRET_ECONOMY] > 100)
        soviet_secrets[SOVIET_SECRET_ECONOMY] = 100;
    if(soviet_secrets[SOVIET_SECRET_ECONOMY] < 0)
        soviet_secrets[SOVIET_SECRET_ECONOMY] = 0;
}

void T_UpdateResources(void)
{
    //float addresource[NRESOURCES];
    //usa_resources[RESOURCE_OBRION];
}

void T_Step(void)
{
    T_UpdateResources();
    T_UpdateEconomy();
}

void T_StepVariable(int i)
{
    while(i--)
        T_Step();
}