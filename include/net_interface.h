#ifndef NET_INTERFACE_H_INCLUDED
#define NET_INTERFACE_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sstream>

/* Networking Headers */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ifaddrs.h> //For reporting ip addresses

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

struct packet; //So inclusion of reqest_mappings works

#include "logging.h"
#include "settings.h"
#include "utility.h"
#include "network/request_mappings.h"

#include "core_classes.h"

#define LISTEN_SIZE 5
#define DEFAULT_RETRIES 2

//#define STR(x) #x
#define INI_EXISTS(section,key) _settings->exists(STR(section), STR(key))
#define INI_EXTRACT(section,key,type) _settings->extractValue<type>(STR(section),STR(key))

class cProtocol {
	public:
		cProtocol();
		~cProtocol();

		virtual void addMsg(int) = 0;
};

class cNetInterface: public cCoreModule {
	private:
		bool initialized;

		int sock;
		struct sockaddr_in server_addr;

		int max_retries;

		cProtocol *protocol;

	public:
		cNetInterface();
		cNetInterface(int port);
		~cNetInterface();

		void init_net(int port);
		void set_protocol(cProtocol*);
		void start_listening();

		void status(stringstream& stream);
		void cleanup();

};

struct packet {
	int client_fd;
	char *request;

	//Usually casted to some struct type
	void *extra_data;
};

class cFDMNProtocol: public cProtocol, cCoreModule {
	private:
		static const char* version() { return "0.1"; };

		ts_queue* msg_queue;
		cID_dispatch msg_ids;

		vector<boost::thread*> listen_threads;

		/* Status Information */
		boost::mutex status_lock;
		unsigned long msg_received;
		unsigned long msg_serviced;

		/* Opitons (loaded on construction) */
		bool wait_enqueue;
		int max_threads;

		/* Mapping for requests */
		map<string, void (*)(packet*)> req_map;

	public:
		cFDMNProtocol();
		~cFDMNProtocol();
		void init_mappings();

		void initQueue();
		void startThreads();
		void listen();

		/* Implementations from cProtocol Class */
		void addMsg(int);

		void status(stringstream& stream);
		void cleanup();
};

#endif // NET_INTERFACE_H_INCLUDED
