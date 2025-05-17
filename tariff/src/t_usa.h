#ifndef _T_USA_H
#define _T_USA_H

#define MAX_USA_EXPORT 6

extern float usa_stockmarket;
extern float usa_nucleardevelopment;
extern float usa_military;
extern float usa_tariff;
extern float usa_resources[3];
extern float usa_export;

void T_InitUSA(void);
void T_PrintUSAInfo(void);
void T_PrintUSAExportInfo(void);
void T_SetUSAExport(float amount);
void T_Spy(int secret);

#endif