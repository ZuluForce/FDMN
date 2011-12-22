#include "server_core.h"

cServerCore::cServerCore() {

    return;
}

cServerCore::cServerCore(string settings_file) {
    settings = new cSettings( settings_file );

    return;
}

void cServerCore::start_server() {
	int prompt = settings->extractValue<int>("Admin", "admin_prompt");

	cout << "Prompt boolean = " << prompt << endl;
    if ( settings->extractValue<bool>("Admin", "admin_prompt") ) {
        init_admin();
        start_admin();
    }

    return;
}
