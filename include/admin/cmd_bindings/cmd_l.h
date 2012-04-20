#ifndef CMD_L_H_INCLUDED
#define CMD_L_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>

#include "logging.h"
#include "settings.h"

void eval_cmd_l(string cmd);
void print_help_l();

#endif // CMD_L_H_INCLUDED
