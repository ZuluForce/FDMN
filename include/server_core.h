#ifndef SERVER_CORE_H_INCLUDED
#define SERVER_CORE_H_INCLUDED

#include "settings.h"
#include "net_interface.h"
#include "admin/interface.h"

/* Boost Thread Library */
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#define STR(x) #x
#define INI_EXISTS(section,key) _settings->exists(STR(section), STR(key))
#define INI_EXTRACT(section,key,type) _settings->extractValue<type>(STR(section),STR(key))

class cServerCore {
    private:
    	/* Utility Classes */
    	cNetInterface *network;
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
};

#endif // SERVER_CORE_H_INCLUDED
