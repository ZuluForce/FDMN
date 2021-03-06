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
		timestamp = INI_EXTRACT(Admin, log_timestamp, bool);

		if ( timestamp )
			cout << "Log timestamping enabled" << endl;
		else
			cout << "Log timestamping disabled" << endl;

		color_prompt = INI_EXTRACT(Admin, color_prompt, bool);

		if ( color_prompt ) {
			termOpts green_uline[] = {cGreen, eULine, EOO};
			print_color("Color prompt is enabled", green_uline, true);
			//cout << "Color prompt is enabled" << endl;
		}
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

	/* Add Mutex Locks */

	insert_time();
	log_stream << "[" << message << "]" << endl;

	/* Add Mutex Locks */

	return;
}

void cLog::log_color(string message, const termOpts options[]) {
	if ( color_prompt )
		print_color(message.c_str(), options, true);

	log_simple(message);

	return;
}

void cLog::log_block_msg(string message) {

	write_lock.lock();

	log_stream << message << endl;

	write_lock.unlock();

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
