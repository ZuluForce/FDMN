#ifndef PACKETS_H_INCLUDED
#define PACKETS_H_INCLUDED

#include <arpa/inet.h>

#define MAX_PATHSIZE 2048

static uint32_t endianness = 0xdeadbeef;
enum endianness { BIG, LITTLE };

#define ENDIANNESS ( *(const char *)&endianness == 0xef ? LITTLE \
                   : *(const char *)&endianness == 0xde ? BIG \
                   : assert(0))

#define NET_ORDER BIG

enum enumReqType {
	eSTAT
};

struct packet {
	enumReqType request;

	//Usually casted to some struct type
	void *data;
};

struct STAT_packet {
	uint16_t mount;

	char filereq[MAX_PATHSIZE];
};

char* serializePacket(packet*, enumReqType packType);
packet* deserializePacket(char *data);
void packetToNetworkOrder(char*);

hton_16(char*);
hton_32)char*);
hton_n(char*,short);

#endif // PACKETS_H_INCLUDED
