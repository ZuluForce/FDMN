#ifndef REQUEST_MAPPINGS_H_INCLUDED
#define REQUEST_MAPPINGS_H_INCLUDED

#include <sstream>

#include "settings.h"
#include "net_interface.h"
#include "utility.h"

#define ADD_MAPPING(x) req_map[STR(x)] = x##_request

void STAT_request(packet*);

#endif // REQUEST_MAPPINGS_H_INCLUDED
