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

	settings->set_defaults( setDefaults );

    _settings = settings;

    log = new cLog(settings->extractValue<string>("Admin", "log_file"));
    _log = log;

    /* Start up network */
    network = new cNetInterface(INI_EXTRACT(Network , port, int));

    return;
}

cServerCore::~cServerCore() {
	return;
}

void cServerCore::cleanup() {
	/* Cleanup threads and data */
	delete log;
	return;
}

void cServerCore::start_server() {
	time( &start_time );

	net_thread = new boost::thread(boost::bind(&cNetInterface::start_listening, network));

    if ( INI_EXTRACT(Admin, admin_prompt, bool) ) {
        init_admin();
        prompt_thread = new boost::thread(start_admin);
    }

    return;
}

void cServerCore::status(uint32_t flags, bool log) {
	stringstream stream;
	stream << "Sever Status Information:" << endl;

	if ( flags & SF_UPTIME ) {
		time_t curr_time;
		time( &curr_time );
		stream << "Uptime: " << difftime(curr_time,start_time) << endl;
	}
	if ( flags & SF_NETWORK ) {
		network->status(stream);
	}

	if ( log )
		_log->log_block_msg(stream.str());

	cout << stream.str();
	return;
}
