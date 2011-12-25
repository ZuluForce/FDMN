#include "fdmn.h"

extern cLog *_log;

cServerCore *_core;

void exit_handler(int signum) {
	if ( signum != SIGINT ) {
		_log->log_simple("Invalid signal received in exit_handler");
		return;
	}

	cerr << "Exiting the server" << endl;
	_log->log_simple("Exiting the server");

	_core->cleanup();
	exit(0);
}

int main(int argc, char** argv) {
    if ( argc < 2 ) {
        cerr << "Usage: " << argv[0] << " <ini file>" << endl;
        return 1;
    }

    struct sigaction sa;
    sigset_t sa_set;

    sigfillset( &sa_set );
    sa.sa_handler = exit_handler;
    sa.sa_mask = sa_set;
    sa.sa_flags = 0;

	/* Block all signals while server starts */
    sigprocmask(SIG_BLOCK, &sa_set, NULL);

    /* Create Core Server Object */
    cServerCore core( argv[1] /* Settings File */);
    core.start_server();
    _core = &core;

    sigdelset(&sa_set, SIGINT);
    sigprocmask(SIG_SETMASK, &sa_set, NULL);

    sigaction(SIGINT, &sa, NULL);

    while ( true )
		pause();

	return 0;
}
