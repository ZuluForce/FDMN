#include "admin/cmd_bindings/cmd_c.h"

extern cLog *_log;

void eval_cmd_c(string cmd) {
	pid_t pid;

	if ( cmd.compare("clear") == 0) {
		if ( (pid = fork()) == 0) {
			#ifdef __MINGW32__
			execlp("cls", "cls", (char*) NULL);
			#else
			execlp("clear", "clear", (char*) NULL); //__GNUC__
			#endif

			/* Exec Failed */
			return;
		}

		waitpid(pid, NULL, 0);
		return;
	}

	cerr << "Invalid Command: ";
	cerr << cmd.substr(0,cmd.find_first_of(' '));
	cerr << endl;


	return;
}


void print_help_c() {
	cout << "**--------| C |--------**" << endl;
	cout << "clear - Clearn the terminal screen" << endl;
	cout << endl;

	return;
}
