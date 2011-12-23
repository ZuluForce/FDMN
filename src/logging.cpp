#include "logging.h"

extern cSettings *_settings;

cLog::cLog()
:ready(false), timestamp(false) {

	if ( _settings )
		timestamp = _settings->extractValue<bool>("Admin", "log_timestamp");
	return;
}

cLog::cLog(string filename)
: ready(false), timestamp(false), log_file(filename) {

	if ( _settings ) {
		if ( INI_EXISTS(Admin, log_timestamp) )
			timestamp = INI_EXTRACT(Admin, log_timestamp, bool);

		if ( timestamp )
			cout << "Log timestamping enabled" << endl;
		else
			cout << "Log timestamping disabled" << endl;
	}

	log_stream.open(filename.c_str(), ios::out | ios::trunc);
	if ( !log_stream.is_open() ) {
		cerr << "Error opening log file " << filename << endl;
		ready = false;
		return;
	}

	cout << "Initialized log file: " << filename << endl;
	ready = true;

	return;
}

cLog::~cLog() {
	log_stream.close();

	return;
}

void cLog::insert_time() {
	if ( timestamp ) {
		time_t rawtime;
		struct tm *timeinfo;

		time( &rawtime );
		timeinfo = localtime( &rawtime );

		char *time_str = asctime( timeinfo );
		time_str[strlen( time_str ) - 1] = '\0'; //Get rid of extra newline

		log_stream << "[" << time_str << "]";
	}

	return;
}

void cLog::log_simple(string message) {
	if ( !ready )
		return;

	/*
	if ( pthread_mutex_lock( &write_lock ) == -1 ) {
		cerr << "cLog::log_simple() Failed to acquire write lock" << endl;
		return;
	}
	*/

	insert_time();
	log_stream << "[" << message << "]" << endl;

	/*
	if ( pthread_mutex_lock( &write_lock ) == -1 ) {
		cerr << "cLog::log_simple() Failed to release write lock" << endl;
		cerr << "\tDisabling logging to possibly prevent deadlock" << endl;

		ready = false;
		pthread_mutex_destroy( &write_lock );
	}
	*/

	return;
}

void cLog::toggle_time(bool setting) {
	if ( setting )
		cerr << "Enabling log timestamp" << endl;
	else
		cerr << "Disabling log timestamp" << endl;

	timestamp = setting;

	return;
}
