#pragma once

#include "Drawer.h"
#include <map>

double Emin = 1.0;

void Img();

void Console();

/* COMMANDS */
str CMD_Print(deq arg);

str CMD_Draw(deq arg);

str CMD_LejaAdd(deq arg);

str CMD_setS(deq arg);

str CMD_C(deq arg);