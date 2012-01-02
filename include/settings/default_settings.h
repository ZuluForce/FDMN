#ifndef DEFAULT_SETTINGS_H_INCLUDED
#define DEFAULT_SETTINGS_H_INCLUDED

#include "iniReader.h"

#define STR(x) #x
#define ADD(section,key,value) ini->addDefault(STR(section),STR(key),STR(value))

inline void setDefaults(INIReader *ini) {
	/* Section Admin */
	ADD(Admin,admin_prompt,1);
	ADD(Admin,log_file,log.txt);
	ADD(Admin,log_timestamp,1);

	/* Formatting */
	ADD(Format,time_style,1);

	/* Section Network */
	ADD(Network,port,9000);
	ADD(Network,MaxNetThreads,4);
	ADD(Network,MsgQueueSize,10);
}

#endif // DEFAULT_SETTINGS_H_INCLUDED
