#ifndef CMD_M_H_INCLUDED
#define CMD_M_H_INCLUDED

#include <iostream>
#include <string>

#include "logging.h"
#include "utility.h"

using namespace std;

void eval_cmd_m(string cmd);

class mountOptions: public OptionsBase {
	public:
		mountOptions();
};

#endif // CMD_M_H_INCLUDED
