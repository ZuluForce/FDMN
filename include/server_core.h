#ifndef SERVER_CORE_H_INCLUDED
#define SERVER_CORE_H_INCLUDED

#include <sstream>

#include "settings.h"
#include "net_interface.h"
#include "admin/interface.h"
#include "file_management/mounts.h"

/* Boost Thread Library */
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "settings/default_settings.h"
#include "utility.h"

#define STR(x) #x
#define toSTR(x) STR(X)
#define INI_EXISTS(section,key) _settings->exists(STR(section), STR(key))
#define INI_EXTRACT(section,key,type) _settings->extractValue<type>(STR(section),STR(key))

#define SERVER_VERSION "0.0.2"

enum {
	SF_ALL = 0xFFFFFFFFF,
	SF_NETWORK = 0x1,
	SF_LOG = SF_NETWORK << 1,
	SF_SETTINGS = SF_LOG << 1,
	SF_ALL_SETTINGS = SF_SETTINGS << 1,
	SF_UPTIME = SF_ALL_SETTINGS << 1,
	SF_VERSION = SF_UPTIME << 1,
	SF_MOUNTS = SF_VERSION << 1
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
        cMountSys *MountSys;

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

        static string version() {
        	stringstream sVersion;
        	sVersion << "Server Core Version: " << SERVER_VERSION << endl;
        	#ifdef __GNUG__
        	sVersion << "Compiled With: g++ " << __VERSION__ << endl;
        	#endif
        	sVersion << "Compiled On: " << __DATE__;
        	sVersion << " at " << __TIME__ << endl;
        	return sVersion.str();
		};
};

#endif // SERVER_CORE_H_INCLUDED
