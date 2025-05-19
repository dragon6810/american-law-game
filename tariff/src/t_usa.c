#include "t_usa.h"

#include <stdio.h>

#include "t_game.h"
#include "t_soviet.h"

float usa_stockmarket;
float usa_nucleardevelopment;
float usa_military;
float usa_tariff;
float usa_resources[NRESOURCES];
float usa_outlets[NOUTLETS];
float usa_budgets[NBUDGETS];

void T_InitUSA(void)
{
    int i;

    usa_stockmarket = T_RandomFloat(70, 80);
    usa_nucleardevelopment = 0;
    usa_military = T_RandomFloat(75, 85);
    usa_resources[RESOURCE_BASEDIUM] = T_RandomFloat(10, 18);
    usa_resources[RESOURCE_PEPSIUM] = T_RandomFloat(0, 5);
    for(i=0; i<NOUTLETS; i++)
        usa_outlets[i] = 100.0 / ((float) NOUTLETS);
    for(i=0; i<NBUDGETS; i++)
        usa_budgets[i] = 100.0 / ((float) NBUDGETS);
}

void T_PrintUSAInfo(void)
{
    printf("USA Information:\n");
    printf("    economy health:      %3.1f%%\n", usa_stockmarket);
    printf("    nuclear development: %3.1f%%\n", usa_nucleardevelopment);
    printf("    military strength:   %3.1f%%\n", usa_military);
    printf("    basedium:            %3.1f tons\n", usa_resources[RESOURCE_BASEDIUM]);
    printf("    pepsium:             %3.1f tons\n", usa_resources[RESOURCE_PEPSIUM]);
}

void T_PrintUSAOutletInfo(void)
{
    int i;

    float surplus;

    printf("usa basedium distribution (%.1f tons produced per month):\n", (float) USA_PRODUCTION);

    printf("    sell to soviet union: %3.1f%%\n", usa_outlets[OUTLET_SELL]);
    printf("    research:             %3.1f%%\n", usa_outlets[OUTLET_RESEARCH]);
    printf("    circulate in economy: %3.1f%%\n", usa_outlets[OUTLET_CIRCULATE]);

    for(i=0, surplus=0; i<NOUTLETS; i++)
        surplus += usa_outlets[i];
    surplus = 100 - surplus;

    printf("    surplus:              %3.1f%%\n", surplus);
}

void T_PrintUSABudgetInfo(void)
{
    int i;

    float surplus;

    printf("usa budget distribution:\n");

    printf("    military:            %3.1f%%\n", usa_budgets[BUDGET_MILITARY]);
    printf("    basedium refinement: %3.1f%%\n", usa_budgets[BUDGET_PRODUCTION]);
    printf("    research:            %3.1f%%\n", usa_budgets[BUDGET_RESEARCH]);

    for(i=0, surplus=0; i<NBUDGETS; i++)
        surplus += usa_budgets[i];
    surplus = 100 - surplus;

    printf("    surplus:             %3.1f%%\n", surplus);
}

void T_SetUSAOutlet(int ioutlet, float amount)
{
    int i;

    float total;

    if(amount < 0 || amount > 100)
    {
        printf("error: expected float from 0-100\n");
        return;
    }

    for(i=0, total=0; i<NOUTLETS; i++)
        total += usa_outlets[i];
    total -= usa_outlets[ioutlet];
    total += amount;

    if(total > 100)
    {
        printf("error: new total surpasses 100%%\n");
        return;
    }

    usa_outlets[ioutlet] = amount;
}

void T_SetUSABudget(int ibudget, float amount)
{
    int i;

    float total;

    if(amount < 0 || amount > 100)
    {
        printf("error: expected float from 0-100\n");
        return;
    }

    for(i=0, total=0; i<NBUDGETS; i++)
        total += usa_budgets[i];
    total -= usa_budgets[ibudget];
    total += amount;

    if(total > 100)
    {
        printf("error: new total surpasses 100%%\n");
        return;
    }

    usa_budgets[ibudget] = amount;
}

void T_Spy(int secret)
{
    float risk;
    float addtense;

    risk = usa_military - soviet_secrets[SOVIET_SECRET_MILITARY] / 4;
    if(T_RandomFloat(0, 100) > risk)
    {
        printf("your spy was caught\n");
        addtense = T_RandomFloat(0, 15) + usa_military * T_RandomFloat(0, 0.05);
        printf("+%3.1f tension\n", addtense);
        soviet_tension += addtense;
        return;
    }

    printf("your operation was successful\n");

    soviet_knownsecrets[secret] = 1;
    soviet_lastsecrets[secret] = soviet_secrets[secret];
}