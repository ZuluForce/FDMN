#ifndef SERVER_CORE_H_INCLUDED
#define SERVER_CORE_H_INCLUDED

#include "settings.h"
#include "admin/interface.h"

#define STR(x) #x
#define INI_EXISTS(section,key) _settings->exists(STR(section), STR(key))
#define INI_EXTRACT(section,key,type) _settings->extractValue<type>(STR(section),STR(key))

class cServerCore {
    private:
    	/* Utility Classes */
        cSettings *settings;
        cLog *log;

        cServerCore();

    public:
        cServerCore(string settings_file);

        void start_server();
};

#endif // SERVER_CORE_H_INCLUDED
