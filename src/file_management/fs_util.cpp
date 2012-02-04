#include "file_management/fs_util.h"

vector<fileAttrs>& absFileInfo::getAttrs() { return Attrs; }
void absFileInfo::setPath(absFileInfo& infoObj, string path) { return; }
void absFileInfo::setPath(absFileInfo& infoObj, filesystem::path& path) { return; }
void absFileInfo::setSize(absFileInfo& infoObj, ssize_t size) { return; }
void absFileInfo::setType(absFileInfo& infoObj, eFileType type) { return; }
absFileInfo* absFileInfo::addFile(absFileInfo& infoObj, eFileType type) { return NULL; }

void fillFfileInfo(absFileInfo& infoObj, string startPath) {
	return fillFileInfo(infoObj, filesystem::path(startPath));
}

void fillFileInfo(absFileInfo& infoObj, filesystem::path startPath) {
	infoObj.setPath(infoObj, startPath);

	filesystem::directory_iterator end;
	absFileInfo *newFileEntry;
	eFileType fType = FT_NONE;

	/* Iterate through everything in the directory */
	for ( filesystem::directory_iterator pos(startPath); pos != end; ++pos) {
		if ( is_regular_file(*pos) )
			fType = FT_REG;

		if ( fType == FT_NONE )
			continue;

		newFileEntry = infoObj.addFile(infoObj, fType);

		filesystem::path newPath( *pos );
		callFileSetters(*newFileEntry, newPath);

		fType = FT_NONE;
	}

	return;
}

void callFileSetters(absFileInfo& infoObj, filesystem::path& currPath)  {
	vector<fileAttrs>& reqAttrs = infoObj.getAttrs();

	vector<fileAttrs>::iterator req_iter;

	for  (req_iter = reqAttrs.begin(); req_iter != reqAttrs.end(); ++req_iter) {
		switch ( *req_iter ) {
			case FA_PATH:
				infoObj.setPath(infoObj, currPath);
				break;

			case FA_SIZE:
				infoObj.setSize(infoObj, filesystem::file_size( currPath ));
				break;

			default:
				cout << "Invalid file attribute request: " << __FILE__ << " on line " << __LINE__ << endl;
				break;
		}
	}
}
