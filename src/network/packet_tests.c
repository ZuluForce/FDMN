#include "network/packet_tests.h"

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

int main(int argc, char **argv) {
	packet test_pack;
	STAT_packet *data = (STAT_packet*) malloc( sizeof(STAT_packet) );
	data->mount = 1234;
	strcpy(data->filereq, "test.txt");

	test_pack.request = eSTAT;
	test_pack.data = data;
	printPacket(&test_pack);

	char *serialized = serializePacket( &test_pack );
	packet *dsPack;
	dsPack = deserializePacket( serialized );
	printPacket(dsPack);

	return 0;
}
