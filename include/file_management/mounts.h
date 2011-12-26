#ifndef MOUNTS_H_INCLUDED
#define MOUNTS_H_INCLUDED

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

enum enumMountType {
	MT_LOCAL,
	MT_REMOTE
};

typedef struct remoteLoc {
	in_addr_t ip_addr;
};

typedef struct localLoc {
	char full_path[FILENAME_MAX];
};

typedef union mountLocation {
	remoteLoc _remote;
	localLoc _local;
};

typedef struct mountStruct {
	enumMountType type;
	mountLocation mountLoc;
};

class cMounts {
	private:
		vector<mountStruct*> mounts;

	public:
		cMounts();
		~cMounts();

		add_local(string&);
		add_local(char*);
};

#endif // MOUNTS_H_INCLUDED
