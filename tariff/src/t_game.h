#ifndef _GAME_H
#define _GAME_H

#define RESOURCE_BASEDIUM 0
#define RESOURCE_PEPSIUM  1
#define RESOURCE_OBRION   2
#define NRESOURCES        3

typedef struct
{
    float military;
    float development;
} budget_t;

extern float resourceprices[3];

float T_RandomFloat(float min, float max);
void T_ProcessInput(const char* message);
void T_InitGame(void);
void T_Step(void);
void T_StepVariable(int i);

#endif