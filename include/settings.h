#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <string>
#include <sstream>
#include "iniReader.h"
#include "core_classes.h"

class cSettings : public cCoreModule {
    private:
        bool initialized;
        INIReader *ini_file;

    public:
        cSettings();
        cSettings(INIReader *ini);
        cSettings(string filename);

        ~cSettings();

        bool load_settings(string filename = "");
        void set_defaults(void (*default_fn) (INIReader*));

        bool exists(const string& section, const string& key);

        template<class T> T extractValue(const string& section, const string& key);
        template<class T> T extractDefault(const string& section, const string& key);

        /* Function from cCoreModule */
        void status(stringstream &stream);
        void status_all(stringstream &stream);
        void cleanup();
};

template<class T>
T cSettings::extractValue(const string& section, const string& key) {
    return ini_file->extractValue<T>(section, key);
}

template<class T>
T cSettings::extractDefault(const string& section, const string& key) {
	stringstream stream;
	stream << ini_file->getDefault(section, key);

	T ret_val;
	stream >> ret_val;
	return ret_val;
}
#endif // SETTINGS_H_INCLUDED
