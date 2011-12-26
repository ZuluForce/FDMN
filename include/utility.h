#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#define SEC_PER_YEAR 31536000
#define SEC_PER_DAY 86400
#define SEC_PER_HOUR 3600
#define SEC_PER_MIN 60

using namespace std;

string sec_to_time(int seconds, int style = 0);


#endif // UTILITY_H_INCLUDED
