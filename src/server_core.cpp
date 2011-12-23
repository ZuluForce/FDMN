#include "server_core.h"

cSettings *_settings;
cLog *_log;

cServerCore::cServerCore() {
	/* Never will be called */

    return;
}

cServerCore::cServerCore(string settings_file) {
    settings = new cSettings( settings_file );
    if ( settings == NULL )
    	throw ((string) "Fatal Exception: Settings not found!");

    _settings = settings;

    log = new cLog(settings->extractValue<string>("Admin", "log_file"));
    _log = log;

    return;
}

void cServerCore::start_server() {
	int prompt = settings->extractValue<int>("Admin", "admin_prompt");

	cout << "Prompt boolean = " << prompt << endl;

    if ( INI_EXISTS(Admin, admin_prompt) &&
		 INI_EXTRACT(Admin, admin_prompt, bool) ) {
        init_admin();
        start_admin();
    }

	log->log_simple("Shutting down server");
    return;
}
