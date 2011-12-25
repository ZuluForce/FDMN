#include "admin/cmd_bindings/cmd_l.h"

extern cSettings *_settings;
extern cLog *_log;

void start_log_monitor(string cmd) {
	pid_t pid;

	if ( (pid = fork()) == 0) {
		execlp("gnome-terminal","gnome-terminal", "-e","tail -f log.txt", (char*) NULL);
		_log->log_simple("Failed to start log monitor");
		return;
	}
	stringstream stream;
	stream << "Started log monitor with PID: ";
	stream << pid;

	_log->log_simple(stream.str());
	return;
}

void eval_cmd_l(string cmd) {
	if ( cmd.compare("logmonitor") == 0 ) {
		start_log_monitor(cmd);
		return;
	}

	cerr << "Invalid Command: ";
	cerr << cmd.substr(0,cmd.find_first_of(' '));
	cerr << endl;

	return;
}
