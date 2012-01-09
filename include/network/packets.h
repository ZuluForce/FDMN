#ifndef PACKETS_H_INCLUDED
#define PACKETS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>

#define MAX_PACKET 4096
#define MAX_PATHSIZE 1028

static uint32_t endianness = 0xdeadbeef;
enum endianness { BIG, LITTLE };

#define ENDIANNESS  (*(const char *) &endianness == 0xef ? LITTLE : BIG)

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

char* serializePacket(packet*);
packet* deserializePacket(char*);

void free_packet(packet*);

void hton_16(char*);
void hton_32(char*);
void hton_n(char*,short);
void ntoh_n(char*,short);

#endif // PACKETS_H_INCLUDED
