#include "admin/cmd_bindings/cmd_t.h"

extern cLog *_log;

void eval_cmd_t(string cmd) {
	string cmd_name = cmd.substr(0,cmd.find_first_of(' '));

    if ( cmd_name.compare("timestamp") == 0) {
        cout << "You entered the timestamp command" << endl;

        _log->toggle_time(true);

        return;
    }

    cerr << "Invalid Command: ";
    cerr << cmd_name;
    cerr << endl;

    return;
}
