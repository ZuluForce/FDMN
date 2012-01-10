#include "network/test_msg.h"

int main(int argc, char**argv) {
	if ( argc < 3 ) {
		cerr << "Usaged: " << argv[0];
		cerr << " address msgType" << endl;

		exit(1);
	}
	int error;
	char *port = strstr(argv[1], ":");
	char *address = argv[1];

	if ( port == NULL ) {
		cerr << "Ivalid format for address parameter: ";
		cerr << "--.--.--.--:port" << endl;

		exit(1);
	}
	*port = '\0';
	port += 1;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if ( sockfd == -1 ) {
		cerr << "Error creating socket: " << strerror(errno) << endl;
		exit(-1);
	}

	struct addrinfo *result;
	error = getaddrinfo(address, port, NULL, &result);
	if ( error != 0 ) {
		cerr << "Error getting address info: ";
		cerr << strerror(errno) << endl;
		exit(-1);
	}

	error = connect(sockfd, result->ai_addr, sizeof(*(result->ai_addr)));
	if ( error == -1 ) {
		perror("Error connecting socket");
		exit(-1);
	}

	packet *pack;
	char *serial_pack;

	//enum request type
	pack->request = (enumReqType) atoi( argv[2] );

	switch ( atoi(argv[2]) ) {
		case eSTAT: {
			STAT_packet *s_pack = (STAT_packet*) malloc( sizeof(STAT_packet) );
			if ( s_pack == NULL ) {
				cerr << "Error allocating space for packet" << endl;
				exit(1);
			}

			pack->data = s_pack;

			s_pack->mount = 1234;
			strcpy(s_pack->filereq, "root/test.txt");

			serial_pack = serializePacket( pack );

			error = send(sockfd, serial_pack, MAX_PACKET, 0);
			if ( error == -1 ) {
				perror( "Error seding data" );
				exit(-1);
			}

			close(sockfd);

			packet *dsPack = deserializePacket(serial_pack);
			printPacket( dsPack );
			break;
		}

		default:
			break;
	}

	return 0;
}
