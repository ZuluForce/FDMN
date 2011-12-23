#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include "settings.h"

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

		/* Log Filename */
		string log_file;

		/* Output stream for log */
		ofstream log_stream;

		/* Locking for multiple threads */
		//pthread_mutex_lock write_lock = PTHREAD_MUTEX_INITIALIZER;

		void insert_time();

	public:
		cLog();
		cLog(string filename);

		~cLog();

		void log_simple(string message);

		void toggle_time(bool setting);

};

#endif // LOGGING_H_INCLUDED
