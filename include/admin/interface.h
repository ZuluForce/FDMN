#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "cmd_bindings/all_cmds.h"

using namespace std;

#define EVAL_CASE(char, _char) case char:\
                        eval_cmd_##_char(input);\
                        break;

int init_admin();
int start_admin();

void eval_input(string input);

#endif // INTERFACE_H_INCLUDED
