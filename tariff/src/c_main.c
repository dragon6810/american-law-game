#include "c_main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t_soviet.h"
#include "t_usa.h"

#define MAX_ARG_LENGTH 64
#define MAX_ARGS       16

void C_ProcessQuit(int nargs, char args[MAX_ARGS][MAX_ARG_LENGTH])
{
    exit(0);
}

void C_ProcessSpy(int nargs, char args[MAX_ARGS][MAX_ARG_LENGTH])
{
    int isecret;

    if(nargs != 1)
    {
        printf("parse error: expected exactly 1 argument for spy command\n");
        return;
    }

    if(!strcmp(args[0], "basedium"))
        isecret = SOVIET_SECRET_BASEDIUM;
    else if(!strcmp(args[0], "pepsium"))
        isecret = SOVIET_SECRET_PEPSIUM;
    else if(!strcmp(args[0], "obrion"))
        isecret = SOVIET_SECRET_OBRION;
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

    if(!strcmp(args[0], "soviet"))
        T_PrintSovietInformation();
    if(!strcmp(args[0], "usa"))
        T_PrintUSAInfo();
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
        printf("parse error: expected command\n");
        return;
    }

    cstop = cstart;
    while(*cstop > 32)
        cstop++;

    if(cstop - cstart >= MAX_ARG_LENGTH)
    {
        printf("parse error: unknown command\n");
        return;
    }

    memcpy(cmdname, cstart, cstop - cstart);
    cmdname[cstop - cstart] = 0;

    argstart = cstop;
    while(*argstart <= 32 && *argstart)
        argstart++;

    C_ProcessArgs(argstart, &nargs, args);

    if     (!strcmp(cmdname, "info"))
        C_ProcessInfo(nargs, args);
    else if(!strcmp(cmdname, "spy"))
        C_ProcessSpy(nargs, args);
    else if(!strcmp(cmdname, "quit") || !strcmp(cmdname, "q"))
        C_ProcessQuit(nargs, args);
    else
        printf("parse error: unknown command\n");

    printf("> ");
}