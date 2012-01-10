#include "network/packets.h"

ssize_t enumSize = sizeof(enumReqType);

void printPacket(packet *_packet) {
	fprintf(stderr, "Request Type: %d\n", _packet->request);

	switch (_packet->request) {
	case eSTAT: {
		STAT_packet *stat_pack = (STAT_packet*) _packet->data;
		fprintf(stderr, "Mount #: %d\n", stat_pack->mount);
		fprintf(stderr, "Filename: %s\n", stat_pack->filereq);

		break;
	}
	}
	return;
}

char* serializePacket(packet *_packet) {
	char *serialPacket;

	int serializedSize, bytesCopied;
	serializedSize = bytesCopied = 0;

	serializedSize = sizeof(packet);
	serializedSize -= sizeof(void*);

	switch ( _packet->request ) {
	case eSTAT: {
		serializedSize += sizeof(STAT_packet);

		#ifdef DEBUG
		fprintf(stderr, "Serialized size = %d\n", serializedSize);
		#endif

		serialPacket = (char*) malloc( sizeof(char) * serializedSize );

		STAT_packet *stat_data = (STAT_packet*) _packet->data;

		//Copy Request Type
		//serialPacket[bytesCopied] = _packet->request;
		memcpy(serialPacket + bytesCopied, (void*) &_packet->request, sizeof(enumReqType));
		bytesCopied += sizeof(enumReqType);

		memcpy(serialPacket + bytesCopied, stat_data, sizeof(STAT_packet));
		hton_n(serialPacket + bytesCopied, sizeof(uint16_t));
		bytesCopied += sizeof(STAT_packet);


		break;
	}

	default:
		break;

	}

	//Order the packet request type
	hton_n(serialPacket, enumSize);
	return serialPacket;
}

packet* deserializePacket(char *data) {
	int index = 0;

	packet *newPacket = (packet*) malloc( sizeof(packet) );

	ntoh_n(data + index, sizeof(int)); unsigned int _request = data[index];
	newPacket->request = (enumReqType) _request;
	index += sizeof(int);

	switch ( newPacket->request ) {
		case eSTAT: {
			STAT_packet *stat_pack = (STAT_packet*) malloc( sizeof(STAT_packet) );

			ntoh_n(data + index, 2);
			memcpy((void*) &stat_pack->mount, (void*) (data + index), sizeof(uint16_t));
			index += sizeof(uint16_t);

			strncpy(stat_pack->filereq, data + index, MAX_PATHSIZE);
			newPacket->data = (void*) stat_pack;

			break;
		}

		default:
			fprintf(stderr, "Unknown packet type");
	}

	return newPacket;
}

void free_packet(packet *_packet) {
	switch (_packet->request) {
		case eSTAT:
			free(_packet->data);
			break;

		default:
			break;
	}

	free(_packet);

	return;
}


void hton_16(char *data) {
	if ( ENDIANNESS == NET_ORDER )
		return;

	#ifdef DEBUG
	fprintf(stderr, "hton_16 reordering data\n");
	#endif

	char temp = data[0];
	data[0] = data[1];
	data[1] = temp;

	return;
}

//size = byte size
void ntoh_n(char *data, short size) {
	if ( ENDIANNESS == NET_ORDER )
		return;

	#ifdef DEBUG
	fprintf(stderr, "ntoh_n reordering data\n");
	#endif

	int i;
	char temp;
	for (i = 0; i < size / 2; ++i) {
		temp = data[i];
		data[i] = data[size - 1];
		data[size - 1] = temp;
	}

	return;
}

void hton_32(char *data) {
	if ( ENDIANNESS == NET_ORDER )
		return;

	#ifdef DEBUG
	fprintf(stderr, "hton_32 reordering data\n");
	#endif

	char temp = data[0];
	data[0] = data[3];
	data[3] = temp;
	temp = data[1];
	data[1] = data[2];
	data[2] = temp;
}

void hton_n(char *data, short size) {
	if ( ENDIANNESS == NET_ORDER )
		return;

	#ifdef DEBUG
	fprintf(stderr, "hton_n reordering data\n");
	#endif

	size = size / 8;

	int i;
	char temp;
	for (i = 0; i < size / 2; ++i) {
		temp = data[i];
		data[i] = data[size - 1];
		data[size - 1] = temp;
	}

	return;
}
