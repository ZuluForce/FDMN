#include "settings.h"

cSettings::cSettings() : ini_file(NULL) {

    return;
}

cSettings::cSettings(INIReader *ini) {
    ini_file = ini;

    initialized = true;
    return;
}

cSettings::cSettings(string filename) {
    ini_file = new INIReader(filename);

    initialized = true;
    return;
}

cSettings::~cSettings() {
	return;
}

bool cSettings::load_settings(string filename) {
    if ( ini_file == NULL) {
        ini_file = new INIReader(filename);
    } else if ( filename.compare("") != 0) {
        delete ini_file;
        ini_file = new INIReader(filename);
    }

    if ( !ini_file->loaded() ) {
        cerr << "cSettings.load_settings(): .ini file not loaded correctly" << endl;
        initialized = false;
        return false;
    }

    initialized = true;
    return true;
}

void cSettings::set_defaults(void (*default_fn) (INIReader *ini)) {
	if ( default_fn ) default_fn( ini_file );
}

bool cSettings::exists(const string& section, const string& key) {
	return ini_file->exists(section, key);
}

void cSettings::status(stringstream &stream) {
	stream << "Settings Information:" << endl;

	//Need to add a wway to get the real name
	stream << "\tLoaded .ini file: " << "settings.ini";
	stream << endl;

}

void cSettings::status_all(stringstream &stream) {
	stream << "Settings Information:";

	stream << "\tLoaded .ini file: " << "settings.ini";
	stream << endl;

	/* Display settings from each section
	stream << "Admin Section: " << endl;
	*/
}

void cSettings::cleanup() {
	delete ini_file;
}
