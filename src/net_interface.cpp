#include "net_interface.h"

extern cSettings *_settings;
extern cLog *_log;

cNetInterface::cNetInterface() {
	initialized = false;
	return;
}

cNetInterface::cNetInterface(int port) {
	initialized = false;
	init_net( port );

	if ( INI_EXISTS(Network, max_retries) ) {
		max_retries = INI_EXTRACT(Network, max_retries, int);
	} else {
		max_retries = DEFAULT_RETRIES;
	}
	return;
}

void cNetInterface::init_net(int port) {
	if ( initialized ) {
		_log->log_simple("cNetInterface::init_net() called when already initialized");
		return;
	}

	if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Failed to create network socket");
		string msg("Fatal Error: Failed to create network socket (");
		msg += strerror(errno);
		msg += ")";
		_log->log_simple(msg);

		/* Add function in server core to halt after this */
		return;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons( port );
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ( bind(sock, (struct sockaddr*) &server_addr,
			sizeof(server_addr)) == -1) {
		perror("Failed to bind network socket");
        string msg("Fatal Error: Failed to bind network socket (");
		msg += strerror(errno);
		msg += ")";
		_log->log_simple( msg );

		/* Exit Server */
		return;
	}

	/* Enable port reuse incase the server crashes */
	int enable = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
				(char*)&enable, sizeof(int));

	if ( listen(sock, LISTEN_SIZE) == -1 ) {
		perror("Failed to set TCP listen queue");
		string msg("Failed to set TCP listen queue (");
		msg += strerror(errno);
		msg += ")";
		_log->log_simple( msg );

		/* Exit Server */
		return;
	}

	initialized = true;
	return;
}

void cNetInterface::start_listening(cProtocol &_protocol) {
	sockaddr_in client;
	int failed_attempts = 0;

	int client_sz = sizeof(client);
	int client_fd;

    string msg;

	while ( failed_attempts <= max_retries ) {
		if ( (client_fd = accept(sock, (sockaddr*) &client,
					(socklen_t*) &client_sz)) == -1) {

			perror("Error waiting for network connection");

			msg.clear();
			msg += "Error waiting for network connection (";
			msg += strerror(errno);
			msg += ")";

			_log->log_simple( msg );

			++failed_attempts;
			continue;
		}

		msg.clear();
		msg += "Received connection from: ";
		msg += inet_ntoa(client.sin_addr);

		_log->log_simple( msg );

		/* Send msg to protocol handler */

	}

	return;
}

/* Required Server Module Functions */
void cNetInterface::status(stringstream &stream) {
	stream << "Network Information:" << endl;

	struct ifaddrs *addrs;
	struct ifaddrs *ifa;
	void *temp_addr;

	getifaddrs(&addrs);

	char addr4_buffer[INET_ADDRSTRLEN];
	char addr6_buffer[INET6_ADDRSTRLEN];

	for ( ifa = addrs; ifa != NULL; ifa = ifa->ifa_next) {
		if ( ifa->ifa_addr->sa_family == AF_INET) {
			stream << "\t" << ifa->ifa_name << "(";
			stream << "IPv4): ";

			temp_addr = &((struct sockaddr_in*) ifa->ifa_addr)->sin_addr;
			inet_ntop(AF_INET, temp_addr, addr4_buffer, INET_ADDRSTRLEN);
			stream << addr4_buffer << endl;
		} else {
			/* This will display IPV6 info but it doesn't look nice */
			//stream << "\t" << ifa->ifa_name << "(";
			/*
			stream << "IPv6): ";

			temp_addr = &((struct sockaddr_in6*) ifa->ifa_addr)->sin6_addr;
			inet_ntop(AF_INET6, temp_addr, addr6_buffer, INET6_ADDRSTRLEN);
			stream << addr6_buffer << endl;
			*/
		}
	}

	stream << "\tServer Port: " << ntohs(server_addr.sin_port) << endl;

	freeifaddrs( addrs );
	return;
}

void cNetInterface::cleanup() {

	close(sock);
	return;
}



/* FDMN Protocol Class */

cFDMNProtocol::cFDMNProtocol() {
	msg_received = 0;
	msg_serviced = 0;

	initQueue();

	return;
}

cFDMNProtocol::~cFDMNProtocol() {

	return;
}

void cFDMNProtocol::initQueue() {
	int queue_size = INI_EXTRACT(Network,MsgQueueSize,int);

	if ( queue_size < 1 ) {
		cerr << "Error: MsgQueueSize < 1" << endl;
		queue_size = _settings->extractDefault<int>("Network", "MsgQueueSize");
		cerr << "\tReverting to default: " << queue_size << endl;

		_log->log_simple("Error: MsgQueueSize < 1");
	}

	msg_queue = init_queue(queue_size);

	if ( msg_queue == NULL ) {
		_log->log_simple("Fatal Error: Failed to create msg queue");
		throw ((string) "Fatal Error: Failed to create msg queue");
	}

	return;
}

void cFDMNProtocol::startThreads() {
	int num_threads = INI_EXTRACT(Network,MaxNetThreads,int);

	if ( num_threads < 1 ) {
		_log->log_simple("Error: MaxNetThreads < 1");

		cerr << "Error: MaxNetThreads < 1" << endl;
		num_threads = _settings->extractDefault<int>("Network","MaxNetThreads");
		cerr << "\tUsing Default MaxNetThreads = " << num_threads << endl;
	}
}

void cFDMNProtocol::addMsg(int client_fd) {
	add_queue((queue_t*) msg, msg_queue);

	return;
}

void cFDMNProtocol::status(stringstream &stream) {
	stream << "Protocol Handler:" << endl;
	stream << "\tMsg Received: " << msg_received << endl;
	stream << "\tMsg Serviced: " << msg_serviced << endl;
	stream << endl;

	return;
}

void cFDMNProtocol::cleanup() {
	/* Need to free the array inide the queue. To add */
	free(msg_queue);

	return;
}
