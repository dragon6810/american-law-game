#include "t_usa.h"

#include <stdio.h>

#include "t_game.h"
#include "t_soviet.h"

float usa_stockmarket;
float usa_nucleardevelopment;
float usa_military;
float usa_resources[3];

void T_InitUSA(void)
{
    usa_stockmarket = T_RandomFloat(70, 80);
    usa_nucleardevelopment = 0;
    usa_military = T_RandomFloat(75, 85);
    usa_resources[RESOURCE_BASEDIUM] = T_RandomFloat(10, 18);
    usa_resources[RESOURCE_PEPSIUM] = T_RandomFloat(0, 5);
    usa_resources[RESOURCE_OBRION] = T_RandomFloat(7, 12);
}

void T_PrintUSAInfo(void)
{
    printf("USA Information:\n");
    printf("    stock market health: %3.1f%%\n", usa_stockmarket);
    printf("    nuclear development: %3.1f%%\n", usa_nucleardevelopment);
    printf("    military strength:   %3.1f%%\n", usa_military);
    printf("    basedium:            %3.1f tons\n", usa_resources[RESOURCE_BASEDIUM]);
    printf("    pepsium:             %3.1f tons\n", usa_resources[RESOURCE_PEPSIUM]);
    printf("    obrion:              %3.1f tons\n", usa_resources[RESOURCE_OBRION]);
}

void T_Spy(int secret)
{
    soviet_knownsecrets[secret] = 1;
}