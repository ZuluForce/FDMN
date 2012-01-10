#include "network/packet_tests.h"

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
