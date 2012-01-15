#ifndef CMD_M_H_INCLUDED
#define CMD_M_H_INCLUDED

#include <iostream>
#include <string>

#include "logging.h"
#include "utility.h"

using namespace std;

void eval_cmd_m(string cmd);

class mountOptions {
	private:
		argMap options;

	public:
		mountOptions();
		~mountOptions();

		argMap& operator ()();
};

#endif // CMD_M_H_INCLUDED
