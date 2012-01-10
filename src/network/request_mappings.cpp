#include "network/request_mappings.h"

extern cLog *_log;

void STAT_request(packet *_packet) {
	STAT_packet *s_pack = (STAT_packet*) _packet->data;

	stringstream log_msg;
	log_msg << "Stat Reqest (Mount:File) ";
	log_msg << s_pack->mount;
	log_msg << ":";
	log_msg << s_pack->filereq;

	_log->log_simple( log_msg.str() );

	return;
}
