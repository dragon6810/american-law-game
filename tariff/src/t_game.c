#include "t_game.h"

#include <stdio.h>
#include <stdlib.h>

#include "c_main.h"
#include "t_soviet.h"
#include "t_usa.h"

const char* randomresearchdebuffevents[] =
{
    "an unpaid intern was dissolved in acid. better safety regulations will set your research back.",
    "a scientist tripped and accidentally triggered a convieniently placed self destruct button on one of your labs.",
    "the local daredevil drove his car into one of your labs full force after he lost a bet.",
    "a top researcher got poached by Bell Labs.",
};

const char* randommilitarydebuffevents[] =
{
    "a high-ranking military general quit to pursue a degree in evolutionary biology.",
    "one of your top submersibles imploded after trying to visit the titanic.",
    "a pilot carrying an expensive load of nuclear weapons died attempting a quintuple barrel roll.",
    "a lead military strategist left to make a business to produce microprocessors for this computer fad.",
};

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

void T_UpdateTension()
{
    soviet_tension += T_RandomFloat(0.0, 3.0);
    soviet_tension += (usa_stockmarket - soviet_secrets[SOVIET_SECRET_ECONOMY]) * T_RandomFloat(0.0, 0.1);
    soviet_tension += (usa_military - soviet_secrets[SOVIET_SECRET_MILITARY]) * T_RandomFloat(0.0, 0.2);
    soviet_tension += (usa_nucleardevelopment - soviet_secrets[SOVIET_SECRET_RESEARCH]) * T_RandomFloat(0.0, 0.05);
}

void T_UpdateMilitary(void)
{
    int message;
    float removeamount;

    usa_military += (usa_budgets[BUDGET_MILITARY] / 100.0) * (usa_stockmarket / 6.0);
    usa_military -= T_RandomFloat(2.0, 6.0);

    if(T_RandomFloat(0, 100) < 6.0 + 6.0 * (1.0 - usa_military / 100.0))
    {
        message = rand() % (sizeof(randommilitarydebuffevents) / sizeof(char*));
        puts(randommilitarydebuffevents[message]);

        removeamount = T_RandomFloat(2.0, 2.0 + (1.0 - usa_military / 100.0) * 6.0);
        printf("-%.1f miltary\n", removeamount);
        usa_military -= removeamount;
    }
}

void T_UpdateResearch(void)
{
    float usaresearch, sovietresearch;
    float sovietproduction, importpercent, privateimportpercent, sovietsurplus;
    int imessage;
    float remove;

    sovietproduction = soviet_secrets[SOVIET_SECRET_ECONOMY] / 100.0 * 11.0;
    sovietproduction -= T_RandomFloat(0, 2);
    if(sovietproduction < 0)
        sovietproduction = 0;

    importpercent = usa_budgets[BUDGET_IMPORT] / 3;
    privateimportpercent = (1 / ((usa_tariff / 100.0) + 1)) * (1.0 - importpercent / 100.0) * 100.0 / 4.0;
    sovietsurplus = 100.0 - privateimportpercent - importpercent;

    usaresearch  = sovietproduction * (importpercent / 100.0) * 3.0;
    usaresearch += usa_production * (usa_outlets[OUTLET_RESEARCH] / 100.0) * 2.0;
    usaresearch *= ((usa_budgets[BUDGET_RESEARCH] + 50.0) * (usa_stockmarket / 2.0 + 50.0)) / 10000.0;

    sovietresearch = sovietproduction * (sovietsurplus / 100.0);
    sovietresearch += usa_production * (usa_outlets[OUTLET_SELL] / 100.0);
    soviet_tension -= usa_outlets[OUTLET_SELL] / 12.0;
    sovietresearch *= ((soviet_secrets[SOVIET_SECRET_ECONOMY] / 2.0 + 50.0) / 100.0);
    
    usa_nucleardevelopment += usaresearch;
    usa_stockmarket += privateimportpercent / 13.0;
    soviet_secrets[SOVIET_SECRET_ECONOMY] += privateimportpercent / 11.0;

    soviet_secrets[SOVIET_SECRET_RESEARCH] += sovietresearch * 0.5;
    soviet_secrets[SOVIET_SECRET_ECONOMY] += (importpercent + privateimportpercent) / 4.0;

    remove = T_RandomFloat(0.0, 5.0);
    if(!(rand() % 16) && remove >= usa_nucleardevelopment)
    {
        imessage = rand() % (sizeof(randomresearchdebuffevents) / sizeof(char*));
        puts(randomresearchdebuffevents[imessage]);
        printf("-%.1f research\n", remove);
        usa_nucleardevelopment -= remove;
    }
}

void T_UpdateEconomy(void)
{
    float addecousa, addecosoviet;

    addecousa = T_RandomFloat(-6, 6);
    addecosoviet = T_RandomFloat(-6, 6);

    addecousa += usa_outlets[OUTLET_SELL] / 100.0 * usa_production * 1.0;
    addecousa += usa_outlets[OUTLET_CIRCULATE] / 100.0 * usa_production * 0.3;

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

    budgeteffect[BUDGET_PRODUCTION] = (usa_budgets[BUDGET_PRODUCTION] / 100.0) * totalbudget - 14.0;
    budgeteffect[BUDGET_PRODUCTION] /= 15.0;

    usa_military += budgeteffect[BUDGET_MILITARY];
    if(usa_military < 0)
        usa_military = 0;
    if(usa_military > 100)
        usa_military = 100;

    usa_production += budgeteffect[BUDGET_PRODUCTION];
    if(usa_production < 0)
        usa_production = 0;
    if(usa_production > 11) /* you can only refine as much that is mined */
        usa_production = 11;
}

void T_Step(void)
{
    T_ApplyBudget();
    T_UpdateEconomy();
    T_UpdateResearch();
    T_UpdateMilitary();
    T_UpdateTension();

    if(usa_nucleardevelopment >= 100.0 && soviet_secrets[SOVIET_SECRET_RESEARCH] >= 100.0)
    {
        printf("you and the Soviet Union both made a breakthrough at the same time.\n");
        printf("you tear each other apart, leaving no winners.\n");
        printf("\nYOU LOSE\n");
        exit(0);
    }
    if(usa_nucleardevelopment >= 100.0)
    {
        printf("you made a breakthrough before the Soivet Union.\n");
        if(soviet_secrets[SOVIET_SECRET_MILITARY] - usa_military >= -5.0)
        {
            printf("you and the Union were unable to make peace during negotiations and you bombed their major cities,");
            printf("leaving millions dead and Eurasia in shambles.\n");
            printf("\nYOU WIN(?)\n");
        }
        else
        {
            printf("you and the Union were able to make peace during negotiations and the cold war slowly fizzled out.\n");
            printf("\nYOU WIN\n");
        }
        exit(0);
    }
    if(soviet_secrets[SOVIET_SECRET_RESEARCH] >= 100.0)
    {
        printf("the Soviet Union reached a breakthrough before you.\n");
        printf("they shortly bombed your major cities, reducing your country to cinders.\n");
        printf("\nYOU LOSE\n");
        exit(0);
    }

    if(soviet_tension - 100 > T_RandomFloat(0, 50))
    {
        printf("rising tensions between you and the Soviet Union resulted in them launching an attack.\n");
        printf("you counterstruck, but knew that within hours both countries would be destroyed.\n");
        printf("\nYOU LOSE\n");
        exit(0);
    }
}

void T_StepVariable(int i)
{
    while(i--)
        T_Step();
}