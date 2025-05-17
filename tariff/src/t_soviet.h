#ifndef _SOVIET_H
#define _SOVIET_H

#define SOVIET_SECRET_BASEDIUM 0
#define SOVIET_SECRET_PEPSIUM  1
#define SOVIET_SECRET_OBRION   2
#define SOVIET_SECRET_MILITARY 3
#define SOVIET_SECRET_ECONOMY  4
#define SOVIET_NSECRETS        5

extern int soviet_knownsecrets[SOVIET_NSECRETS];
extern float soviet_lastsecrets[SOVIET_NSECRETS];
extern float soviet_secrets[SOVIET_NSECRETS];
extern float soviet_tariff;
extern float soviet_tension;

void T_PrintSovietInformation(void);
void T_InitSoviet(void);

#endif