#ifndef MOUNTS_H_INCLUDED
#define MOUNTS_H_INCLUDED

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <vector>

#include "utility.h"
#include "logging.h"
#include "file_management/fs_util.h"

#include "boost/filesystem.hpp"

using namespace std;
using namespace boost;

class AttrVector {
	private:
		vector<fileAttrs> attributes;

	public:
		AttrVector();
		vector<fileAttrs>& getVector();
};

//Used by cMountInfo
static AttrVector MountAttributes;

class cMountInfo: public absFileInfo {
	protected:
		eFileType entryType;
		filesystem::path entryPath;
		ssize_t entrySize;

		vector<cMountInfo*> regularFiles;

	public:
		cMountInfo();
		~cMountInfo();

		vector<fileAttrs>& getAttrs();

		static void setPath(absFileInfo&, string path);
		static void setPath(absFileInfo&, filesystem::path path);
		static void setSize(absFileInfo&, ssize_t size);
		static void setType(absFileInfo&, eFileType type);

		static absFileInfo* addFile(absFileInfo&, eFileType);

		void addRegular(cMountInfo*);

		void printContent(int indentLvl = 0);

};

static int defaultVectorInit = 10;
static int defaultVectorResize = 2;

class cMountSys {
	private:
		vector<cMountInfo*> mounts;

		cID_dispatch mountIDs;

	public:
		cMountSys();
		~cMountSys();

		void setRoot(string&);
		bool newMount(string location);
};

#endif // MOUNTS_H_INCLUDED
