#ifndef _T_USA_H
#define _T_USA_H

#include "t_game.h"

extern float usa_stockmarket;
extern float usa_nucleardevelopment;
extern float usa_military;
extern float usa_tariff;
extern float usa_outlets[NOUTLETS];
extern float usa_budgets[NBUDGETS];
extern float usa_production;

void T_InitUSA(void);
void T_PrintUSAInfo(void);
void T_PrintUSAOutletInfo(void);
void T_PrintUSABudgetInfo(void);
void T_SetUSAOutlet(int ioutlet, float amount);
void T_SetUSABudget(int ibudget, float amount);
void T_SetUSATariff(float amount);
void T_Spy(int secret);

#endif