#ifndef MOUNTS_H_INCLUDED
#define MOUNTS_H_INCLUDED

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <vector>

#include "utility.h"
#include "logging.h"
#include "core_classes.h"

#include "boost/filesystem.hpp"
#include "file_management/fs_util.h"

using namespace std;
using namespace boost;

static int defaultVectorInit = 10;
static int defaultVectorResize = 2;

class cMountSys: public cCoreModule {
	private:
		vector<cMountInfo*> mounts;

		cID_dispatch mountIDs;

	public:
		cMountSys();
		~cMountSys();

		void setRoot(string&);
		bool newMount(string location);
		bool newMount(filesystem::path& location);

		void printMounts();

		/* ------- Core Module Fn's --------- */
		void status(stringstream&);
		void cleanup();
		const char* version() { return "0.2"; };
		/* ---------------------------------- */
};

#endif // MOUNTS_H_INCLUDED
