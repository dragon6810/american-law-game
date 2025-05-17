#ifndef _T_USA_H
#define _T_USA_H

#include "t_game.h"

#define USA_PRODUCTION 6 /* how many tons of basedium does the us make per month? */

#define USA_OUTLET_SELL      0
#define USA_OUTLET_RESEARCH  1
#define USA_OUTLET_CIRCULATE 2
#define USA_NOUTLETS         3

extern float usa_stockmarket;
extern float usa_nucleardevelopment;
extern float usa_military;
extern float usa_tariff;
extern float usa_resources[NRESOURCES];
extern float usa_outlets[USA_NOUTLETS];

void T_InitUSA(void);
void T_PrintUSAInfo(void);
void T_PrintUSAOutletInfo(void);
void T_SetUSAOutlet(int ioutlet, float amount);
void T_Spy(int secret);

#endif