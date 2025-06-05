#include "c_main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t_game.h"
#include "t_soviet.h"
#include "t_usa.h"

int nhistory = 0;
prevcommand_t history[MAX_CMD_HISTORY] = {};

void C_ProcessQuit(int nargs, char args[MAX_ARGS][MAX_ARG_LENGTH])
{
    exit(0);
}

void C_ProcessHistory(int nargs, char args[MAX_ARGS][MAX_ARG_LENGTH])
{
    int i, j;

    if(nargs)
    {
        printf("parse error: expected exactly 0 arguments for history\n");
        return;
    }

    for(i=0; i<nhistory; i++)
    {
        printf("%s ", history[i].cmd);
        for(j=0; j<history[i].nargs; j++)
            printf("%s ", history[i].args[j]);
        printf("\n");
    }
}

void C_ProcessStep(int nargs, char args[MAX_ARGS][MAX_ARG_LENGTH])
{
    int i;

    int nmonths;

    if(nargs > 1)
    {
        printf("parse error: expected exactly 1 or 0 arguments for step command\n");
        return;
    }

    nmonths = 1;
    if(nargs)
    {
        for(i=0; i<strlen(args[0]); i++)
        {
            if(args[0][i] >= '0' && args[0][i] <= '9')
                continue;

            printf("parse error: expected positive integer for argument 1 of step command\n");
            return;
        }

        nmonths = atoi(args[0]);
    }

    T_StepVariable(nmonths);

    printf("stepped forward %d months\n", nmonths);
}

void C_ProcessTariff(int nargs, char args[MAX_ARGS][MAX_ARG_LENGTH])
{
    char *end;
    float amount;

    if(nargs != 1)
    {
        printf("parse error: expected exactly 1 argument for tariff command\n");
        return;
    }

    amount = strtod(args[0], &end);
    if(end != args[0] + strlen(args[0]))
    {
        printf("parse error: expected valid float for argument 1 of tariff command\n");
        return;
    }

    T_SetUSATariff(amount);
}

void C_ProcessBudget(int nargs, char args[MAX_ARGS][MAX_ARG_LENGTH])
{
    char *end;
    float amount;
    int budget;

    if(!nargs || !strcmp(args[1], "info"))
    {
        T_PrintUSABudgetInfo();
        return;
    }

    if(nargs != 2)
    {
        printf("parse error: expected exactly 2 arguments for budget command\n");
        return;
    }

    amount = strtod(args[1], &end);
    if(end != args[1] + strlen(args[1]))
    {
        printf("parse error: expected valid float for argument 2 of basedium command\n");
        return;
    }

    if(!strcmp(args[0], "military"))
        budget = BUDGET_MILITARY;
    else if(!strcmp(args[0], "production") || !strcmp(args[0], "produce") || !strcmp(args[0], "basedium"))
        budget = BUDGET_PRODUCTION;
    else if(!strcmp(args[0], "research"))
        budget = BUDGET_RESEARCH;
    else if(!strcmp(args[0], "pepsium") || !strcmp(args[0], "import") || !strcmp(args[0], "buy"))
        budget = BUDGET_IMPORT;
    else
    {
        printf("parse error: unknown budget\n");
        return;
    }

    T_SetUSABudget(budget, amount);
}

void C_ProcessBasedium(int nargs, char args[MAX_ARGS][MAX_ARG_LENGTH])
{
    float amount;
    char *end;
    int outlet;

    if(!nargs || !strcmp(args[1], "info"))
    {
        T_PrintUSAOutletInfo();
        return;
    }

    if(nargs != 2)
    {
        printf("parse error: expected exactly 2 arguments for basedium command\n");
        return;
    }

    amount = strtod(args[1], &end);
    if(end != args[1] + strlen(args[1]))
    {
        printf("parse error: expected valid float for argument 2 of basedium command\n");
        return;
    }

    if(!strcmp(args[0], "sell"))
        outlet = OUTLET_SELL;
    else if(!strcmp(args[0], "research") || !strcmp(args[0], "use"))
        outlet = OUTLET_RESEARCH;
    else if(!strcmp(args[0], "circulate"))
        outlet = OUTLET_CIRCULATE;
    else
    {
        printf("parse error: unknown outlet for basedium\n");
        return;
    }

    T_SetUSAOutlet(outlet, amount);
}

void C_ProcessSpy(int nargs, char args[MAX_ARGS][MAX_ARG_LENGTH])
{
    int isecret;

    if(nargs != 1)
    {
        printf("parse error: expected exactly 1 argument for spy command\n");
        return;
    }

    if(!strcmp(args[0], "research"))
        isecret = SOVIET_SECRET_RESEARCH;
    else if(!strcmp(args[0], "military"))
        isecret = SOVIET_SECRET_MILITARY;
    else if(!strcmp(args[0], "economy"))
        isecret = SOVIET_SECRET_ECONOMY;
    else
    {
        printf("parse error: unkown secret for spy command\n");
        return;
    }

    T_Spy(isecret);
}

void C_ProcessInfo(int nargs, char args[MAX_ARGS][MAX_ARG_LENGTH])
{
    if(nargs != 1)
    {
        printf("parse error: expected exactly 1 argument for info command\n");
        return;
    }

    if     (!strcmp(args[0], "soviet") || !strcmp(args[0], "ussr") || !strcmp(args[0], "commies"))
        T_PrintSovietInformation();
    else if(!strcmp(args[0], "usa"))
        T_PrintUSAInfo();
    else if(!strcmp(args[0], "basedium") || !strcmp(args[0], "outlets") || !strcmp(args[0], "outlet"))
        T_PrintUSAOutletInfo();
    else if(!strcmp(args[0], "budgets") || !strcmp(args[0], "budget"))
        T_PrintUSABudgetInfo();
    else if(!strcmp(args[0], "tariff"))
        T_PrintUSATariffInfo();
    else if(!strcmp(args[0], "time") || !strcmp(args[0], "month") || !strcmp(args[0], "months"))
        T_PrintTimeInfo();
    else
        printf("parse error: unkown thing for info command\n");
}

void C_ProcessArgs(const char* args, int* nargs, char outargs[MAX_ARGS][MAX_ARG_LENGTH])
{
    char *c;

    int iarg;
    char *start, *stop;

    c = (char*) args;
    iarg = *nargs = 0;
    while(1)
    {
        if(!*c)
            break;

        if(iarg >= MAX_ARGS)
        {
            printf("parse error: too many args\n");
            return;
        }

        start = stop = c;
        while(*stop > 32)
            stop++;

        if(stop - start >= MAX_ARG_LENGTH)
        {
            printf("parse error: arg too long\n");
            return;
        }

        memcpy(outargs[iarg], start, stop - start);
        outargs[iarg][stop - start] = 0;
        iarg++;

        c = stop;
        while(*c <= 32 && *c)
            c++;
    }

    *nargs = iarg;
}

int historyoverflow = 0;

void C_ProcessCommand(const char* command)
{
    char *cstart, *cstop, *argstart;
    char cmdname[MAX_ARG_LENGTH];
    int nargs;
    char args[MAX_ARGS][MAX_ARG_LENGTH];

    cstart = (char*) command;
    while(*cstart <= 32 && *cstart)
        cstart++;

    if(!*cstart)
    {
        printf("parse error: expected command\n> ");
        return;
    }

    cstop = cstart;
    while(*cstop > 32)
        cstop++;

    if(cstop - cstart >= MAX_ARG_LENGTH)
    {
        printf("parse error: unknown command\n> ");
        return;
    }

    memcpy(cmdname, cstart, cstop - cstart);
    cmdname[cstop - cstart] = 0;

    argstart = cstop;
    while(*argstart <= 32 && *argstart)
        argstart++;

    C_ProcessArgs(argstart, &nargs, args);

    if     (!strcmp(cmdname, "info") || !strcmp(cmdname, "i"))
        C_ProcessInfo(nargs, args);
    else if(!strcmp(cmdname, "spy") || !strcmp(cmdname, "sp"))
        C_ProcessSpy(nargs, args);
    else if(!strcmp(cmdname, "step") || !strcmp(cmdname, "st"))
        C_ProcessStep(nargs, args);
    else if(!strcmp(cmdname, "quit") || !strcmp(cmdname, "q"))
        C_ProcessQuit(nargs, args);
    else if(!strcmp(cmdname, "basedium") || !strcmp(cmdname, "outlets") || !strcmp(cmdname, "outlet") || !strcmp(cmdname, "o"))
        C_ProcessBasedium(nargs, args);
    else if(!strcmp(cmdname, "budgets") || !strcmp(cmdname, "budget") || !strcmp(cmdname, "b"))
        C_ProcessBudget(nargs, args);
    else if(!strcmp(cmdname, "tariff") || !strcmp(cmdname, "t"))
        C_ProcessTariff(nargs, args);
    else if(!strcmp(cmdname, "history"))
        C_ProcessHistory(nargs, args);
    else
        printf("parse error: unknown command\n");

    if(!historyoverflow)
    {
        memcpy(history[nhistory].cmd, cmdname, MAX_ARG_LENGTH);
        memcpy(history[nhistory].args, args, sizeof(args));
        history[nhistory].nargs = nargs;
        nhistory++;
    }

    if(nhistory+1 >= MAX_CMD_HISTORY && !historyoverflow)
    {
        printf("error: max commands reached. max is %d\n", MAX_CMD_HISTORY);
        printf("future commands will not be saved\n");
        historyoverflow = 1;
    }

    printf("> ");
}