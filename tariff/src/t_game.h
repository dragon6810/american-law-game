#ifndef _GAME_H
#define _GAME_H

#define RESOURCE_BASEDIUM 0
#define RESOURCE_PEPSIUM  1
#define NRESOURCES        2

#define OUTLET_SELL      0
#define OUTLET_RESEARCH  1
#define OUTLET_CIRCULATE 2
#define NOUTLETS         3

#define BUDGET_MILITARY   0
#define BUDGET_PRODUCTION 1
#define BUDGET_RESEARCH   2
#define BUDGET_IMPORT     3
#define NBUDGETS          4

extern int month;

float T_RandomFloat(float min, float max);
void T_ProcessInput(const char* message);
void T_InitGame(void);
void T_Step(void);
void T_StepVariable(int i);
void T_PrintTimeInfo(void);

#endif