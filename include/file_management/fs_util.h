#ifndef FS_UTIL_H_INCLUDED
#define FS_UTIL_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <string>
#include "boost/filesystem.hpp"

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

class absFileInfo {
	private:
		vector<fileAttrs> Attrs;

	public:
		/* The function iterating over the FS will send
		 * the info specified to the fileInfo object */
		virtual vector<fileAttrs>& getAttrs() __attribute__((warning("Should not use base absFileInfo class")));

		/* Functions called to fill in information */
		static void setPath(absFileInfo&, string) __attribute__((warning("Should not use base absFileInfo class")));
		static void setPath(absFileInfo&, filesystem::path&) __attribute__((warning("Should not use base absFileInfo class")));
		static void setSize(absFileInfo&, ssize_t size) __attribute__((warning("Should not use base absFileInfo class")));
		static void setType(absFileInfo&,eFileType) __attribute__((warning("Should not use base absFileInfo class")));

		/* Add file/directory entry */
		//Should return ref to new obj so info can be set
		static absFileInfo* addFile(absFileInfo&, eFileType) __attribute__((warning("Should not use base absFileInfo class")));
};

void fillFfileInfo(absFileInfo& infoObj, string startPath);
void fillFileInfo(absFileInfo& infoObj, filesystem::path startPath);
void callFileSetters(absFileInfo& infoObj, filesystem::path& currPath);

#endif // FS_UTIL_H_INCLUDED
