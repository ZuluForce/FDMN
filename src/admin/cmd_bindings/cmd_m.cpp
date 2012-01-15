#include "admin/cmd_bindings/cmd_m.h"

extern cLog *_log;

void mount_cmd(string cmd) {
	static mountOptions options = mountOptions();
	static argMap& mapOptions = options();

	_log->log_simple("Mount command received");

	int opt_index = cmd.find_first_of('-');
	if ( opt_index == string::npos ) {
		cerr << "No arguments given to mount command" << endl;
		return;
	}
	string flags = cmd.substr(opt_index);

	try {
		parseFlags(options(), flags);
	} catch (string error) {
		cerr << "Error Parsing Arguments: " << endl;
		cerr << error << endl;
		return;
	}

	if ( OPTION_SET(mapOptions,'m','-') )
		cout << "m flag set for mount_cmd" << endl;

	if ( OPTION_SET(mapOptions,'n','-') )
		cout << "n flag set for mount_cmd" << endl;

	if ( OPTION_SET(mapOptions,'r','-') )
		cout << "r flag set for mount_cmd" << endl;

	clearFlags(mapOptions);
	return;
}

void eval_cmd_m(string cmd) {
	string cmd_name = cmd.substr(0,cmd.find_first_of(' '));

	if ( cmd_name.compare("mount") == 0 ) {
		mount_cmd(cmd);
		return;
	}

	cerr << "Invalid command: " << cmd_name;

	return;
}



/*---------Option Class Definitions-----------*/

mountOptions::mountOptions() {
	ADD_OPTION(options,'m');
	ADD_INT_ARG(options,'m');

	ADD_OPTION(options,'n');
	ADD_STR_ARG(options,'n');

	ADD_OPTION(options,'r');

	return;
}

mountOptions::~mountOptions() {
	return;
}

argMap& mountOptions::operator ()() {
	return options;
}
