#include "admin/cmd_bindings/cmd_m.h"

extern cLog *_log;
extern cMountSys *_mountsys;

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

	string location;

	if ( OPTION_SET(mapOptions,'m','-') ) //Mount #
		cout << "m flag set for mount_cmd" << endl;

	if ( OPTION_SET(mapOptions,'n','-') ) //Mount name
		cout << "n flag set for mount_cmd" << endl;

	if ( OPTION_SET(mapOptions,'r','-') ) //Remote mount
		cout << "r flag set for mount_cmd" << endl;

	if ( OPTION_SET(mapOptions,'l','-') ) {
		location = EXTRACT_STRING(mapOptions,'l',flags);
		cout << "Location string: " << location << endl;
	}
	if ( OPTION_SET(mapOptions,'p','-') ) {
		_mountsys->printMounts();
		clearFlags(mapOptions);
		return;
	}

	if ( location.length() > 0 && location[0] == '~') {
		boost::filesystem::path fullPath = boost::filesystem::current_path();
		fullPath /= location.substr(1);

		_mountsys->newMount(fullPath);
	} else {
		_mountsys->newMount(location);
	}

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

void print_help_m() {
	cout << "**--------| M |--------**" << endl;
	cout << "mount - Mount a directory" << endl;
	cout << "\t-l \"location\": Location of directory to mount" << endl;
	cout << "\t-m #: Specify your own mount # to be referenced later" << endl;
	cout << "\t-n \"name\": Give a human readable name for the new mount" << endl;
	cout << "\t-r: Specify this as a mount on a remote machine" << endl;
	cout << endl;

	return;
}



/*---------Option Class Definitions-----------*/

mountOptions::mountOptions() {
	/* Non-Functional */
	ADD_OPTION(options,'m');
	ADD_INT_ARG(options,'m');

	/* Location for mount */
	ADD_OPTION(options,'l');
	ADD_STR_ARG(options, 'l');

	/* Optional Display Name */
	ADD_OPTION(options,'n');
	ADD_STR_ARG(options,'n');

	/* It is a remote mount. Include network address. */
	ADD_OPTION(options,'r');
	ADD_STR_ARG(options, 'r');

	/* Prints out the current mounts */
	ADD_OPTION(options,'p');

	return;
}
