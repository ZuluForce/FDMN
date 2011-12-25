#ifndef CMD_C_H_INCLUDED
#define CMD_C_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/wait.h>

#include "logging.h"

using namespace std;

void eval_cmd_c(string cmd);

#endif // CMD_C_H_INCLUDED
