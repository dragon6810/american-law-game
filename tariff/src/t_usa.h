#ifndef _T_USA_H
#define _T_USA_H

extern float usa_stockmarket;
extern float usa_nucleardevelopment;
extern float usa_military;
extern float usa_resources[3];

void T_InitUSA(void);
void T_PrintUSAInfo(void);
void T_Spy(int secret);

#endif