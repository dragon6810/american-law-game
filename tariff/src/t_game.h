#ifndef _GAME_H
#define _GAME_H

#define RESOURCE_BASEDIUM 0
#define RESOURCE_PEPSIUM  1
#define RESOURCE_OBRION   2
#define NRESOURCES        3

float T_RandomFloat(float min, float max);
void T_ProcessInput(const char* message);

#endif