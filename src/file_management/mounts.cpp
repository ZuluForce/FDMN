#include "mounts.h"

cMounts::cMounts() {

	return;
}

cMountSys::~~cMounts() {

	return;
}

void cMountSys::setRoot(string &rootDir) {
	if ( chdir(rootDir.c_str()) == -1 ) {
		string error("Failed to change root directory: ");
		error += strerror(errno);
		fprintf(stderr, error.c_str());
		_log->log_simple(error.c_str());

		return;
	}

	string msg("Root directory changed to: ");
	msg += rootDir;
	_log->log_simple(msg.c_str());

	return;
}
