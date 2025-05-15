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
    printf    ("    tension:  %3.1f%%\n", soviet_tension);
    if(soviet_knownsecrets[SOVIET_SECRET_BASEDIUM])
        printf("    basedium: %3.1f tons\n", soviet_lastsecrets[SOVIET_SECRET_BASEDIUM]);
    else
        printf("    basedium: ??? tons\n");
    if(soviet_knownsecrets[SOVIET_SECRET_PEPSIUM])
        printf("    pepsium:  %3.1f tons\n", soviet_lastsecrets[SOVIET_SECRET_PEPSIUM]);
    else
        printf("    pepsium:  ??? tons\n");
    if(soviet_knownsecrets[SOVIET_SECRET_OBRION])
        printf("    obrion:   %3.1f tons\n", soviet_lastsecrets[SOVIET_SECRET_OBRION]);
    else
        printf("    obrion:   ??? tons\n");
}

void T_InitSoviet(void)
{
    soviet_secrets[SOVIET_SECRET_BASEDIUM] = T_RandomFloat(0, 5);
    soviet_secrets[SOVIET_SECRET_PEPSIUM] = T_RandomFloat(10, 18);
    soviet_secrets[SOVIET_SECRET_OBRION] = T_RandomFloat(7, 12);
}