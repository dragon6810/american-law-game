#include "t_game.h"

#include <stdlib.h>

#include "c_main.h"
#include "t_soviet.h"
#include "t_usa.h"

float usa_production = USA_PRODUCTION;

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

void T_ApplyBudget(void)
{
    int i;

    float totalbudget;
    float budgeteffect[NBUDGETS];

    totalbudget = usa_stockmarket / 100.0 * 25.0;
    for(i=0; i<NBUDGETS; i++)
        budgeteffect[i] = 0;
    
    budgeteffect[BUDGET_MILITARY] = (usa_budgets[BUDGET_MILITARY] / 100.0) * totalbudget - 14.0;
    budgeteffect[BUDGET_MILITARY] += T_RandomFloat(-8, 8);
    budgeteffect[BUDGET_MILITARY] /= 4.0;

    usa_military += budgeteffect[BUDGET_MILITARY];
    if(usa_military < 0)
        usa_military = 0;
    if(usa_military > 100)
        usa_military = 100;
}

void T_Step(void)
{
    T_ApplyBudget();
    T_UpdateResources();
    T_UpdateEconomy();
}

void T_StepVariable(int i)
{
    while(i--)
        T_Step();
}