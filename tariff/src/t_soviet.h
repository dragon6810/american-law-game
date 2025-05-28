#ifndef _SOVIET_H
#define _SOVIET_H

#include "t_game.h"

#define SOVIET_SECRET_RESEARCH 0
#define SOVIET_SECRET_MILITARY 1
#define SOVIET_SECRET_ECONOMY  2
#define SOVIET_NSECRETS        3

extern int soviet_knownsecrets[SOVIET_NSECRETS];
extern float soviet_lastsecrets[SOVIET_NSECRETS];
extern float soviet_secrets[SOVIET_NSECRETS];
extern float soviet_outlets[NOUTLETS];
extern float soviet_tariff;
extern float soviet_tension;

void T_PrintSovietInformation(void);
void T_InitSoviet(void);

#endif