#ifndef FS_UTIL_H_INCLUDED
#define FS_UTIL_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <string>

#include "color_out.h"
#include "utility.h"
#include "logging.h"

#include "boost/filesystem.hpp"
#include "boost/algorithm/string.hpp"

#define MAX_REC_DEPTH 30
#define MAX_REC_PRINT 10

using namespace std;
using namespace boost;

/** Assigned to a cMountInfo object to determine desired info
 *
 *	When a cMountInfo object is filled with file/directory entries
 *	you can specify what attributes you want to save by adding
 *	these flags to the classes attribute vector.
 */
enum fileAttrs {
	FA_PATH,
	FA_SIZE,
	FA_DIRSIZE
};

enum eFileType {
	FT_REG,
	FT_DIR,
	FT_SYM,
	FT_OTH,
	FT_ALL, /**< Only used in functions like cMountInfo::numberFiles */
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

		/** This is the sum of this directories files
		 *	plus those of all subdirectories.
		 */
		int subFiles;

		/** The number of directories under this one. */
		int subDirs;

		/** Total size of index files/direcotires below here */
		uint64_t subSize;

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
		static void setSubFiles(cMountInfo&, int);
		static void setSubDirs(cMountInfo&, int);
		static void setSubSize(cMountInfo&, uint64_t);

		static int getSubFiles(cMountInfo&);
		static int getSubDirs(cMountInfo&);
		static uint64_t getSubSize(cMountInfo&);

		static cMountInfo* addFile(cMountInfo&, eFileType);

		static void sortMounts(cMountInfo&);
		/* ------------------------------ */

		void addRegular(cMountInfo*);
		void addDir(cMountInfo*);

		void printContent(int indentLvl = 0);
		int numberFiles(eFileType);

		filesystem::path& getPath();

		class iterator {
			protected:
				int i;
				cMountInfo* infoInstance;

			public:
				iterator();
				iterator(cMountInfo*, int);

				iterator& operator++() {
					++i;

					return *this;
				}

				cMountInfo* operator*() {
					return infoInstance->directories.at(i);
				}

				bool operator==(const iterator& iter) {
					/* This only checks that the indexes are the same.
					 * Later I should also check that iter.infoInstance
					 * is the same to this->infoInstance
					 */
					return iter.i == this->i ? true : false;
				}

				bool operator!=(const iterator& iter) {
					return iter.i == this->i ? false : true;
				}
		};

		cMountInfo::iterator begin();
		cMountInfo::iterator end();

};

void fillFileInfo(cMountInfo& infoObj, string startPath);
void fillFileInfo(cMountInfo& infoObj, filesystem::path& startPath, bool recursive = true);
void callFileSetters(cMountInfo& infoObj, filesystem::path& currPath, eFileType type, uint64_t& size);

/* Used as the function parameter to quicksort */
int sortPathForward( cMountInfo* path1, cMountInfo* path2);

#endif // FS_UTIL_H_INCLUDED
