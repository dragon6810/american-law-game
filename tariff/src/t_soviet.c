#include "t_soviet.h"

#include <stdio.h>

#include "t_game.h"

int soviet_knownsecrets[SOVIET_NSECRETS] = {};
float soviet_lastsecrets[SOVIET_NSECRETS];
float soviet_secrets[SOVIET_NSECRETS];
float soviet_tension;

void T_PrintSovietInformation(void)
{
    printf("Soviet Union Information:\n");
    if(soviet_knownsecrets[SOVIET_SECRET_RESEARCH])
        printf("    research:       %3.1f%%\n", soviet_lastsecrets[SOVIET_SECRET_RESEARCH]);
    else
        printf("    research:       ???%%\n");
    if(soviet_knownsecrets[SOVIET_SECRET_ECONOMY])
        printf("    economy health: %3.1f%%\n", soviet_lastsecrets[SOVIET_SECRET_ECONOMY]);
    else
        printf("    economy health: ???%%\n");
    if(soviet_knownsecrets[SOVIET_SECRET_MILITARY])
        printf("    military:       %3.1f%%\n", soviet_lastsecrets[SOVIET_SECRET_MILITARY]);
    else
        printf("    military:       ???%%\n");;
    printf    ("    tension:        %3.1f%%\n", soviet_tension);
}

void T_InitSoviet(void)
{
    soviet_tension = T_RandomFloat(40, 55);
    soviet_secrets[SOVIET_SECRET_RESEARCH] = 0.0;
    soviet_secrets[SOVIET_SECRET_MILITARY] = T_RandomFloat(65, 80);
    soviet_secrets[SOVIET_SECRET_ECONOMY] = T_RandomFloat(75, 90);
}