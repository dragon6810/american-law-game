#include "t_usa.h"

#include <stdio.h>

#include "t_game.h"
#include "t_soviet.h"

float usa_stockmarket;
float usa_nucleardevelopment;
float usa_military;
float usa_tariff;
float usa_outlets[NOUTLETS];
float usa_budgets[NBUDGETS];
float usa_production;

void T_InitUSA(void)
{
    int i;

    usa_stockmarket = T_RandomFloat(70, 80);
    usa_nucleardevelopment = 0;
    usa_military = T_RandomFloat(75, 85);
    for(i=0; i<NOUTLETS; i++)
        usa_outlets[i] = 100.0 / ((float) NOUTLETS);
    for(i=0; i<NBUDGETS; i++)
        usa_budgets[i] = 100.0 / ((float) NBUDGETS);
    usa_production = 6.0;
    usa_tariff = 0;
}

void T_PrintUSAInfo(void)
{
    printf("USA Information:\n");
    printf("    economy health:    %3.1f%%\n", usa_stockmarket);
    printf("    research:          %3.1f%%\n", usa_nucleardevelopment);
    printf("    military strength: %3.1f%%\n", usa_military);
    printf("    tariff on pepsium: %3.1f%%\n", usa_tariff);
}

void T_PrintUSAOutletInfo(void)
{
    int i;

    float surplus;

    printf("usa basedium distribution (%.1f tons produced per month):\n", (float) usa_production);

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

    printf("    military: %3.1f%%\n", usa_budgets[BUDGET_MILITARY]);
    printf("    basedium: %3.1f%%\n", usa_budgets[BUDGET_PRODUCTION]);
    printf("    research: %3.1f%%\n", usa_budgets[BUDGET_RESEARCH]);
    printf("    pepsium:  %3.1f%%\n", usa_budgets[BUDGET_IMPORT]);

    for(i=0, surplus=0; i<NBUDGETS; i++)
        surplus += usa_budgets[i];
    surplus = 100 - surplus;

    printf("    surplus:  %3.1f%%\n", surplus);
}

void T_PrintUSATariffInfo(void)
{
    printf("tariff on pepsium is at %.1f%%\n", usa_tariff);
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

void T_SetUSATariff(float amount)
{
    if(amount < 0.0)
    {
        printf("error: expected amount >= 0.0\n");
        return;
    }

    if(amount > usa_tariff)
        soviet_tension += (amount - usa_tariff) / 3.0;
    else
        soviet_tension += (amount - usa_tariff) / 5.0;
    soviet_tension += T_RandomFloat(0.0, 5.0);

    usa_tariff = amount;
}

void T_Spy(int secret)
{
    float risk;
    float addtense;

    risk = usa_military - soviet_secrets[SOVIET_SECRET_MILITARY] / 2;
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