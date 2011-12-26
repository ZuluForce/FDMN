#include "utility.h"

string sec_to_time(int seconds, int style) {
	stringstream stream;
	int num_years = seconds / SEC_PER_YEAR;
	seconds = seconds % SEC_PER_YEAR;

	int num_days = seconds / SEC_PER_DAY;
	seconds = seconds % SEC_PER_DAY;

	int num_hours = seconds / SEC_PER_HOUR;
	seconds = seconds % SEC_PER_HOUR;

	int num_minutes = seconds / SEC_PER_MIN;
	seconds = seconds % SEC_PER_MIN;

	switch ( style ) {
		case 0:
			stream << num_years << " Years ";
			stream << num_days << " Days ";
			stream << num_hours << " Hours ";
			stream << num_minutes << " Minutes ";
			stream << seconds << " Seconds";
			break;

		case 1:
			stream << num_years << ":";
			stream << num_days << ":";
			stream << num_hours << ":";
			stream << num_minutes << ":";
			stream << seconds;
			break;

		default:
		/*
			cerr << "Invalid style argument(" << style;
			cerr << ") give to sec_to_time";
			*/
			break;
	}

	return stream.str();
}
