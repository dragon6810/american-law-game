#ifndef _C_MAIN_H
#define _C_MAIN_H

#define MAX_CMD_HISTORY 8192
#define MAX_ARG_LENGTH 64
#define MAX_ARGS       16

typedef struct
{
    char cmd[MAX_ARG_LENGTH];
    char args[MAX_ARGS][MAX_ARG_LENGTH];
    int nargs;
} prevcommand_t;

extern int nhistory;
extern prevcommand_t history[MAX_CMD_HISTORY];

void C_ProcessCommand(const char* command);

#endif