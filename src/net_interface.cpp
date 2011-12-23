#include "net_interface.cpp"

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
		perror("Failed to create network socket")
		_log->log_simple("Fatal Error: Failed to create network socket (" strerror(errno) ")");

		/* Add function in server core to halt after this */
		return;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons( port );
	server_addr.sin_addr = htonl(INADDR_ANY);

	if ( bind(sock, (struct sockaddr*) &server_addr,
			sizeof(server_addr)) == -1) {
		perror("Failed to bind network socket");
		_log->log_simple("Fatal Error: Failed to bind network socket (" strerror(errno) ")");

		/* Exit Server */
		return;
	}

	/* Enable port reuse incase the server crashes */
	int enable = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
				(char*)&enable, sizeof(int));

	if ( listen(sock, LISTEN_SIZE) == -1 ) {
		perror("Failed to set TCP listen queue");
		_log->log_simple("Failed to set TCP listen queue (" strerror(errno) ")");

		/* Exit Server */
		return;
	}

	initialized = true;
	return;
}

void cNetInterface::start_listening() {
	sockaddr_in client;
	int failed_attempts = 0;

	while ( failed_attempts <= max_retries ) {
		if ( accept(sock, (sockaddr*) &client,
					sizeof(client)) == -1) {

			perror("Error waiting for network connection");
			_log->log_simple("Error waiting for network connection (" strerror(errno) ")");

			++failed_attempts;
			continue;
		}

		_log->log_simple("Recived connection from: " inet_ntoa(client.sin_addr));
	}

	return;
}
