#ifndef NET_INTERFACE_H_INCLUDED
#define NET_INTERFACE_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* Networking Headers */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "logging.h"
#include "settings.h"

#define LISTEN_SIZE 5
#define DEFAULT_RETRIES 2

#define STR(x) #x
#define INI_EXISTS(section,key) _settings->exists(STR(section), STR(key))
#define INI_EXTRACT(section,key,type) _settings->extractValue<type>(STR(section),STR(key))

class cNetInterface {
	private:
		bool initialized;

		int sock;
		struct sockaddr_in server_addr;

		int max_retries;

	public:
		cNetInterface();
		cNetInterface(int port);
		~cNetInterface();

		void init_net(int port);
		void start_listening();

};

#endif // NET_INTERFACE_H_INCLUDED
