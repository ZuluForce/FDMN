#include "network/packets.h"

char* serializePacket(packet *_packet, enumReqType packType) {
	char *serialPacket;

	int serialzedSize = bytesCopied = 0;
	serialzedSize = sizeof(packet);
	serialzedSize -= sizeof(void*);

	switch ( packType ) {
	case eSTAT:
		serialzedSize += sizeof(STAT_packet);
		serialPacket = malloc( sizeof(char) * serializedSize );

		STAT_packet *stat_data = (STAT_packet*) _packet->data;

		serialPacket[bytesCopied] = _packet->request;
		bytesCopied += sizeof(enumReqType);

		serialPacket[bytesCopied] = stat_data;
		bytesCopied += sizeof(STAT_packet);
		break;

	default:
		break;

	}

	packetToNetworkOrder( serialPacket );
	return serialPacket;
}

void packetToNetworkOrder(char*) {
	int pos = 0;
	char[pos] = htonl(char[0]);
	pos += sizeof(enumReqType);
	char[pos] = hton_16(char + pos);

	return;
}

void packetToHostOrder(char*) {
	char[0] = ntohl(char[0]);
	char[sizeof(enumReqType)] = ntohl(char[sizeof(enumReqType]));
}

packet* deserializePacket(char *data) {
	packet *newPacket = malloc( sizeof(packet) );
	newPacket->request = ntohl(data[0]);

	return newPacket;
}


hton_16(char *data) {
	if ( ENDIANNESS == NET_ORDER )
		return;

	char temp = char[0];
	char[0] = char[1];
	char[1] = temp;

	return;
}

hton_32(char *data) {
	if ( ENDIANNESS == NET_ORDER )
		return;

	char temp = char[0];
	char[0] = char[3];
	char[3] = temp;
	temp = char[1];
	char[1] = char[2];
	char[2] = temp;
}

hton_n(char *data, short size) {
	n = n / 8;

	int i;
	char temp;
	for (i = 0; i < n / 2; ++i) {
		temp = char[i];
		char[i] = char[i - 1];
		char[i - 1] = temp;
	}

	return;
}
