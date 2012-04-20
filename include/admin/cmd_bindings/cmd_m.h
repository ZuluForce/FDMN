#ifndef CMD_M_H_INCLUDED
#define CMD_M_H_INCLUDED

#include <iostream>
#include <string>

#include "logging.h"
#include "utility.h"
#include "file_management/mounts.h"

#include "boost/filesystem.hpp"

using namespace std;

void eval_cmd_m(string cmd);
void print_help_m();

class mountOptions: public OptionsBase {
	public:
		mountOptions();
};

#endif // CMD_M_H_INCLUDED
