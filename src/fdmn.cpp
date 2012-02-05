#include "fdmn.h"

extern cLog *_log;

cServerCore *_core;

void exit_handler(int signum) {
	if ( signum != SIGINT ) {
		_log->log_simple("Invalid signal received in exit_handler");
		return;
	}

	cerr << endl << "Exiting the server" << endl;
	_log->log_simple("Exiting the server");

	_core->cleanup();
	exit(0);
}

void seg_handler(int signum) {
	static const char errmsg[] = "Application has crashed!!";
	if ( !_log )
		cerr << errmsg << endl;
	else
		_log->log_color(errmsg, redErrorStrong);

	void *stack[20];
	size_t stackSize = backtrace(stack, 20);

	string cwd = filesystem::initial_path().string();
	fprintf(stderr, "\tError Dump: %s/errDump.dmp\n", cwd.c_str());
	FILE* errDump = fopen(cwd.c_str(), "w");


	backtrace_symbols_fd(stack, stackSize, fileno(errDump));
	fclose(errDump);

	exit(-1);
}

int main(int argc, char** argv) {
    if ( argc < 2 ) {
        cerr << "Usage: " << argv[0] << " <ini file>" << endl;
        return 1;
    }

    struct sigaction sa, sa_seg;
    sigset_t sa_set;

    sigfillset( &sa_set );
    sa.sa_handler = exit_handler;
    sa.sa_mask = sa_set;
    sa.sa_flags = 0;

    sa_seg.sa_handler = seg_handler;
    sa_seg.sa_mask = sa_set;
    sa_seg.sa_flags = SA_ONSTACK;

	/* Block all signals while server starts */
    sigprocmask(SIG_BLOCK, &sa_set, NULL);

    /* Create Core Server Object */
    cServerCore core( argv[1] /* Settings File */);
    core.start_server();
    _core = &core;

    sigdelset(&sa_set, SIGINT);
    sigdelset(&sa_set, SIGSEGV);
    sigprocmask(SIG_SETMASK, &sa_set, NULL);

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGSEGV, &sa_seg, NULL);

    while ( true )
		pause();

	return 0;
}
