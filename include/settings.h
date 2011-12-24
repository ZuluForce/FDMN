#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <string>
#include "iniReader.h"

class cSettings {
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
};

template<class T>
T cSettings::extractValue(const string& section, const string& key) {
    return ini_file->extractValue<T>(section, key);
}

#endif // SETTINGS_H_INCLUDED
