#ifndef FS_UTIL_H_INCLUDED
#define FS_UTIL_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <string>

#include "color_out.h"
#include "utility.h"

#include "boost/filesystem.hpp"
#include "boost/algorithm/string.hpp"

#define MAX_REC_DEPTH 30
#define MAX_REC_PRINT 10

using namespace std;
using namespace boost;

enum fileAttrs {
	FA_PATH,
	FA_SIZE,
};

enum eFileType {
	FT_REG,
	FT_DIR,
	FT_SYM,
	FT_OTH,
	FT_NONE //Sentinel value
};

class AttrVector {
	private:
		vector<fileAttrs> attributes;

	public:
		AttrVector();
		vector<fileAttrs>& getVector();
};

//Used by cMountInfo
static AttrVector MountAttributes;

const termOpts directoryColor[] = { cBlue, eULine, EOO};
const termOpts fileColor[] = { cGreen, eULine, EOO};
const termOpts pathColor[] = { cCyan, EOO};

class cMountInfo {
	protected:

		vector<cMountInfo*> regularFiles;
		vector<cMountInfo*> directories;

		static inline void printIndent(int level);

	public:
		cMountInfo();
		~cMountInfo();

		eFileType entryType;
		filesystem::path entryPath;
		ssize_t entrySize;

		vector<fileAttrs>& getAttrs();

		/* ------ Static Functions ------ */
		static void setPath(cMountInfo&, string path);
		static void setPath(cMountInfo&, filesystem::path path);
		static void setSize(cMountInfo&, ssize_t size);
		static void setType(cMountInfo&, eFileType type);

		static cMountInfo* addFile(cMountInfo&, eFileType);

		static void sortMounts(cMountInfo&);
		/* ------------------------------ */

		void addRegular(cMountInfo*);
		void addDir(cMountInfo*);

		void printContent(int indentLvl = 0);
		int numberFiles(eFileType);

		filesystem::path& getPath();

};

void fillFileInfo(cMountInfo& infoObj, string startPath);
void fillFileInfo(cMountInfo& infoObj, filesystem::path startPath);
void callFileSetters(cMountInfo& infoObj, filesystem::path& currPath, eFileType type);

/* Used as the function parameter to quicksort */
int sortPathForward( cMountInfo* path1, cMountInfo* path2);

#endif // FS_UTIL_H_INCLUDED
