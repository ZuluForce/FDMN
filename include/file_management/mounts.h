#ifndef MOUNTS_H_INCLUDED
#define MOUNTS_H_INCLUDED

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <vector>

#include "utility.h"

using namespace std;


class cMountSys {
	private:
		vector<mountStruct*> mounts;

		cID_dispatch mountIDs;

	public:
		cMounts();
		~cMounts();

		void setRoot(string&);

};

#endif // MOUNTS_H_INCLUDED
