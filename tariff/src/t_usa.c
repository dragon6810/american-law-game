#include "t_usa.h"

#include <stdio.h>

#include "t_game.h"
#include "t_soviet.h"

float usa_stockmarket;
float usa_nucleardevelopment;
float usa_military;
float usa_tariff;
float usa_resources[3];
float usa_export;

void T_InitUSA(void)
{
    usa_stockmarket = T_RandomFloat(70, 80);
    usa_nucleardevelopment = 0;
    usa_military = T_RandomFloat(75, 85);
    usa_resources[RESOURCE_BASEDIUM] = T_RandomFloat(10, 18);
    usa_resources[RESOURCE_PEPSIUM] = T_RandomFloat(0, 5);
    usa_resources[RESOURCE_OBRION] = T_RandomFloat(7, 12);
    usa_export = 4;
}

void T_PrintUSAInfo(void)
{
    printf("USA Information:\n");
    printf("    economy health:      %3.1f%%\n", usa_stockmarket);
    printf("    nuclear development: %3.1f%%\n", usa_nucleardevelopment);
    printf("    military strength:   %3.1f%%\n", usa_military);
    printf("    basedium:            %3.1f tons\n", usa_resources[RESOURCE_BASEDIUM]);
    printf("    pepsium:             %3.1f tons\n", usa_resources[RESOURCE_PEPSIUM]);
    printf("    obrion:              %3.1f tons\n", usa_resources[RESOURCE_OBRION]);
}

void T_PrintUSAExportInfo(void)
{
    printf("exporting %.1f tons of basedium per month (max is %.1f)\n", usa_export, (float) MAX_USA_EXPORT);
}

void T_SetUSAExport(float amount)
{
    if(amount < 0 || amount > MAX_USA_EXPORT)
    {
        printf("error: expected float from 0.0-%.1f\n", (float) MAX_USA_EXPORT);
        return;
    }

    usa_export = amount;
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