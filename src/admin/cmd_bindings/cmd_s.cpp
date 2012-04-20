#include "admin/cmd_bindings/cmd_s.h"

extern cServerCore *_core;
extern cSettings *_settings;
extern cLog *_log;

void server_status(string cmd) {
	uint32_t sflags = 0;
	bool log = false;

	size_t str_size = cmd.size();
	size_t opt_index = 0;

	opt_index = cmd.find_first_of('-');

	#ifdef DEBUG
	cout << "str_size = " << str_size << endl;
	cout << "opt_index = " << opt_index << endl;
	cout << "cmd string = " << cmd << endl;
	#endif

	while ( opt_index != string::npos ) {
		if ( (opt_index + 1) >= str_size )
			break;

		switch ( cmd[opt_index + 1] ) {
			case 'a':
				sflags = SF_ALL;
				log = true;
				_core->status(sflags,log);
				return;

			case 'l':
				log = true;
				break;

			case 'n':
				sflags |= SF_NETWORK;
				break;

			case 's':
				sflags |= SF_SETTINGS;
				break;

			case 'u':
				sflags |= SF_UPTIME;
				break;

			case 'v':
				sflags |= SF_VERSION;
				break;

			case 'm':
				sflags |= SF_MOUNTS;

			default:
				cerr << "Invalid argument(" << cmd[opt_index + 1];
				cerr << ") to status command" << endl;
				return;
				break;

		}

		//Find next argument. If the next character isn't a space, assume it is a combined arg
		if ( ((++opt_index + 1) < str_size) && (cmd[opt_index + 1] != ' ') )
			continue;
		else
			opt_index = cmd.find_first_of('-', opt_index + 1);
	}

	if ( sflags == 0x0 ) {
		cerr << "No arguments given to status command" << endl;
		return;
	}

	_core->status(sflags,log);

	return;
}

void eval_cmd_s(string cmd) {
	string cmd_name(cmd.substr(0,cmd.find_first_of(' ')));

	if ( cmd_name.compare("status") == 0) {
		server_status(cmd);
		return;
	}

	cerr << "Invalid Command: ";
	cerr << cmd.substr(0,cmd.find_first_of(' '));
	cerr << endl;
	return;
}

void print_help_s() {
	cout << "**------ S ------**" << endl;
	cout << "status - Display status information about the server" << endl;
	cout << "\t-a: Print all status info and log" << endl;
	cout << "\t-l: Export status command results to the log file as well" << endl;
	cout << "\t-n: Network status" << endl;
	cout << "\t-s: Settings information" << endl;
	cout << "\t-u: Server uptime" << endl;
	cout << "\t-v: Version information" << endl;
	cout << "\t-m: Show mounts" << endl;

	return;
}
