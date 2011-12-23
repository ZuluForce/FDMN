#include "admin/cmd_bindings/cmd_a.h"

extern cLog *_log;

void eval_cmd_a(string cmd) {
	string cmd_name = cmd.substr(0,cmd.find_first_of(' '));

    if ( cmd_name.compare("admin") == 0) {
        cout << "You entered the admin command" << endl;

        if ( _log )
        	_log->log_simple("admin command executed");

        return;
    }

    cerr << "Invalid Command: ";
    cerr << cmd_name;
    cerr << endl;

    return;
}
