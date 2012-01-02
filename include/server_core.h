#ifndef SERVER_CORE_H_INCLUDED
#define SERVER_CORE_H_INCLUDED

#include <sstream>

#include "settings.h"
#include "net_interface.h"
#include "admin/interface.h"

/* Boost Thread Library */
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "settings/default_settings.h"
#include "utility.h"

#define STR(x) #x
#define INI_EXISTS(section,key) _settings->exists(STR(section), STR(key))
#define INI_EXTRACT(section,key,type) _settings->extractValue<type>(STR(section),STR(key))

enum {
	SF_ALL = 0xFFFFFFFF,
	SF_NETWORK = 0x1,
	SF_LOG = SF_NETWORK << 1,
	SF_SETTINGS = SF_LOG << 1,
	SF_ALL_SETTINGS = SF_SETTINGS << 1,
	SF_UPTIME = SF_ALL_SETTINGS << 1
};

class cServerCore {
    private:
		/* Status Information */
		time_t start_time;

    	/* Utility Classes */
    	cNetInterface *network;
    	cFDMNProtocol *protocol;
        cSettings *settings;
        cLog *log;

        cServerCore();

        /* Threads */
        boost::thread *net_thread;
        boost::thread *prompt_thread;

    public:
        cServerCore(string settings_file);
        ~cServerCore();

        void cleanup();

        void start_server();

        void status(uint32_t flags, bool log);
};

#endif // SERVER_CORE_H_INCLUDED
