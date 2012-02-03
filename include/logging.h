#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <boost/thread/mutex.hpp>

#include "settings.h"
#include "color_out.h"

#define STR(x) #x
#define INI_EXISTS(section,key) _settings->exists(STR(section), STR(key))
#define INI_EXTRACT(section,key,type) _settings->extractValue<type>(STR(section),STR(key))

using namespace std;

class cLog {
	private:
		/* Is everything set to log */
		bool ready;

		/* Settings */
		bool timestamp;
		bool color_prompt;

		/* Log Filename */
		string log_file;

		/* Output stream for log */
		ofstream log_stream;

		/* Locking for multiple threads */
		boost::timed_mutex write_lock;

		void insert_time();

	public:
		cLog();
		cLog(string filename);

		~cLog();

		void log_simple(string message); //Simple log entry with optional timestamp and given message

		/* Will output message to terminal with the given options
		 * and then will use log_simple to send the message to
		 * the log.
		 */
		void log_color(string message, const termOpts options[]);
		void log_block_msg(string block_msg);

		void toggle_time(bool setting);

};

#endif // LOGGING_H_INCLUDED
