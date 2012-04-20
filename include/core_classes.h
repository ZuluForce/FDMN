#ifndef CORE_CLASSES_H_INCLUDED
#define CORE_CLASSES_H_INCLUDED

#include <sstream>

class cCoreModule {
	public:
		virtual void status(stringstream&) = 0;
		virtual void cleanup() = 0;
		virtual const char* version(stringstream& stream) { return ""; };
};

#endif // CORE_CLASSES_H_INCLUDED
