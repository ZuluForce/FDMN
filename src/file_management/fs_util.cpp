#include "file_management/fs_util.h"

AttrVector::AttrVector() {
	attributes.push_back(FA_PATH);
	attributes.push_back(FA_SIZE);

	return;
}

vector<fileAttrs>& AttrVector::getVector() {
	return attributes;
}

/* ========== Concrete implementation of absFileInfo ==========*/

cMountInfo::cMountInfo() {

	return;
}

cMountInfo::~cMountInfo() {
	/* Free all the cMountInfo objects held in vectors */

	return;
}

vector<fileAttrs>& cMountInfo::getAttrs() {
	return MountAttributes.getVector();
}

void cMountInfo::setPath(cMountInfo& infoObj, string path) {
	infoObj.entryPath = filesystem::path( path );

	return;
}

void cMountInfo::setPath(cMountInfo& infoObj, filesystem::path path) {
	infoObj.entryPath = path;

	return;
}

void cMountInfo::setType(cMountInfo& infoObj, eFileType type) {
	infoObj.entryType = type;

	return;
}

void cMountInfo::setSize(cMountInfo &infoObj, ssize_t size) {
	infoObj.entrySize = size;

	return;
}

cMountInfo* cMountInfo::addFile(cMountInfo& infoObj, eFileType type) {

	cMountInfo *newMountObj = new cMountInfo();
	newMountObj->setType(*newMountObj, type);

	switch ( type ) {
		case FT_REG:
			infoObj.addRegular(newMountObj);
			break;

		case FT_DIR:
			infoObj.addDir(newMountObj);
			break;

		default:
			/* Not supporting file type yet */
			cerr << "File type not supported by cMountInfo" << endl;
			delete(newMountObj);
			return NULL;
	}

	return newMountObj;
}

void cMountInfo::addRegular(cMountInfo *newInfo) {
	regularFiles.push_back(newInfo);
}

void cMountInfo::addDir(cMountInfo *newInfo) {
	directories.push_back(newInfo);
}

inline void cMountInfo::printIndent(int level) {
	for (int i = 0; i < level; ++i) {
		cout << "  |";
	}

	return;
}

void cMountInfo::printContent(int indentLvl) {
	if ( indentLvl >= MAX_REC_PRINT) {
		cout << "Max recursive depth for printing reached" << endl;
		return;
	}
	if ( indentLvl == 0 ) {
		//cout << "Root Path: " << entryPath << endl;
		print_color("Root Path: ", pathColor, false);
		cout << entryPath << endl;
	}

	vector<cMountInfo*>::iterator file_it, dir_it;

	if ( regularFiles.size() > 0 ) {
		printIndent(indentLvl);
		//cout << "Regular Files:" << endl;
		print_color("Regular Files:", directoryColor, true);

		for ( file_it = regularFiles.begin();
			file_it != regularFiles.end(); ++file_it) {
			printIndent(indentLvl);

			cout << (*file_it)->entryPath << endl;
		}
	}

	if ( directories.size() > 0 ) {
		printIndent(indentLvl);
		//cout << "Directories:" << endl;
		print_color("Directories:", fileColor, true);

		for ( dir_it = directories.begin(); dir_it != directories.end(); ++dir_it) {
			printIndent(indentLvl);

			cout << (*dir_it)->entryPath << endl;
			(*dir_it)->printContent(++indentLvl);
		}
	}
}

int cMountInfo::numberFiles(eFileType type) {
	switch ( type ) {
		FT_REG:
			return regularFiles.size();

		FT_DIR:
			return directories.size();

		default: { //Defaults to all types
			int total;
			total += regularFiles.size();
			total += directories.size();

			return total;
		}
	}
}

filesystem::path& cMountInfo::getPath() {
	return entryPath;
}

/* ============================================================*/

void fillFfileInfo(cMountInfo& infoObj, string startPath) {
	return fillFileInfo(infoObj, filesystem::path(startPath));
}

void fillFileInfo(cMountInfo& infoObj, filesystem::path startPath) {
	infoObj.setPath(infoObj, startPath);

	filesystem::directory_iterator end;
	cMountInfo *newFileEntry;
	eFileType fType = FT_NONE;

	try {
	/* Iterate through everything in the directory */
	for ( filesystem::directory_iterator pos(startPath); pos != end; ++pos) {
		cout << "Path: " << *pos << endl;

		if ( is_regular_file(*pos) )
			fType = FT_REG;

		if ( is_directory(*pos) )
			fType = FT_DIR;

		if ( fType == FT_NONE )
			continue;

		newFileEntry = infoObj.addFile(infoObj, fType);

		if ( !newFileEntry ) {
			/* Error in adding new file */
			cout << "newFileEntry == NULL" << endl;
		} else {
			//cout << pos->path().filename();
			filesystem::path newPath( *pos );
			callFileSetters(*newFileEntry, newPath, fType);
		}

		fType = FT_NONE;
	}
	} catch (filesystem::filesystem_error error) {
		cerr << "Error in fillFileInfo: " << error.what();
	}

	return;
}

void callFileSetters(cMountInfo& infoObj, filesystem::path& currPath, eFileType type)  {
	vector<fileAttrs>& reqAttrs = infoObj.getAttrs();

	vector<fileAttrs>::iterator req_iter;

	for  (req_iter = reqAttrs.begin(); req_iter != reqAttrs.end(); ++req_iter) {
		switch ( *req_iter ) {
			case FA_PATH:
				//Only want to store filename
				//infoObj.setPath(infoObj, currPath);
				infoObj.setPath(infoObj, currPath.filename());
				break;

			case FA_SIZE:
				if ( type != FT_DIR)
					infoObj.setSize(infoObj, filesystem::file_size( currPath ));
				break;

			default:
				cout << "Invalid file attribute request: " << __FILE__ << " on line " << __LINE__ << endl;
				break;
		}
	}
}
