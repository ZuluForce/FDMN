#ifndef SERVER_CORE_H_INCLUDED
#define SERVER_CORE_H_INCLUDED

#include "settings.h"
#include "admin/interface.h"

class cServerCore {
    private:
        cSettings *settings;

        cServerCore();

    public:
        cServerCore(string settings_file);

        void start_server();
};

#endif // SERVER_CORE_H_INCLUDED
