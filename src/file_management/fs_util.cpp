#include "file_management/fs_util.h"

extern cLog *_log;

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

void cMountInfo::setSubFiles(cMountInfo &infoObj, int dirs) {
	infoObj.subFiles = dirs;

	return;
}

void cMountInfo::setSubDirs(cMountInfo &infoObj, int files) {
	infoObj.subDirs = files;

	return;
}

void cMountInfo::setSubSize(cMountInfo &infoObj, uint64_t size) {
	infoObj.subSize = size;

	return;
}

int cMountInfo::getSubFiles(cMountInfo &infoObj) {
	return infoObj.subFiles;
}

int cMountInfo::getSubDirs(cMountInfo &infoObj) {
	return infoObj.subDirs;
}

uint64_t cMountInfo::getSubSize(cMountInfo &infoObj) {
	return infoObj.subSize;
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
			(*dir_it)->printContent(indentLvl + 1);
		}
	}
}

int cMountInfo::numberFiles(eFileType ftype) {
	int total = 0;

	switch ( ftype ) {
		case FT_DIR:
			total += directories.size();
			break;

		case FT_REG:
			total += regularFiles.size();
			break;

		case FT_SYM:
		case FT_OTH:
		case FT_NONE:
			break;

		case FT_ALL:
			total += regularFiles.size();
			total += directories.size();
			break;

		default:
			cout << "Type = " << ftype << endl;
			string msg = "cMountInfo::numberFiles invalid type: ";
			msg += ftype;
			_log->log_color(msg, redError);

			throw ((string) msg);
	}

	return total;
}

void cMountInfo::sortMounts(cMountInfo& mount) {
	QuicksortVector<cMountInfo*>(mount.regularFiles, sortPathForward, pivotMiddle, 0, mount.regularFiles.size() - 1);
	QuicksortVector<cMountInfo*>(mount.directories, sortPathForward, pivotMiddle, 0, mount.directories.size() - 1);

	return;
}


filesystem::path& cMountInfo::getPath() {
	return entryPath;
}

cMountInfo::iterator::iterator() {
	this->i = -1;
	this->infoInstance = NULL;

	return;
}

cMountInfo::iterator::iterator(cMountInfo* info, int start) {
	this->i = start;
	this->infoInstance = info;

	return;
}

cMountInfo::iterator cMountInfo::begin() {
	return iterator(this, 0);
}

cMountInfo::iterator cMountInfo::end() {
	return iterator(this, directories.size());
}

/* ============================================================*/

void fillFfileInfo(cMountInfo& infoObj, string startPath) {
	boost::filesystem::path tempPath(startPath);
	return fillFileInfo(infoObj, /*filesystem::path(startPath)*/ tempPath);
}

void fillFileInfo(cMountInfo& infoObj, filesystem::path& startPath, bool recursive) {
	infoObj.setPath(infoObj, startPath);

	filesystem::directory_iterator end;
	cMountInfo *newFileEntry;
	eFileType fType = FT_NONE;

	/* Size of all files in this and all sub directories */
	uint64_t subSize = 0;

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
			//cout << "newFileEntry == NULL" << endl;
			_log->log_color("newFileEntry == NULL", redError);
		} else {
			//cout << pos->path().filename();
			filesystem::path newPath( *pos );
			callFileSetters(*newFileEntry, newPath, fType, subSize);
		}

		fType = FT_NONE;
	}

	cMountInfo::iterator it;
	if ( recursive ) {
		_log->log_color("Scanning subdirectory", yellowWarn);

		//Loop through all the directories in the current infoObj
		//and recursively calls fillFileInfo to index the whole
		//sub-directory
		for ( it = infoObj.begin(); it != infoObj.end(); ++it) {
			fillFileInfo(**it, (*it)->entryPath);
		}
	}

	//Get info on contents below infoObj
	int subDirs = 0;
	int subFiles = 0;

	for ( it = infoObj.begin(); it != infoObj.end(); ++it ) {

		/* Get the directories below the ones in the
		 * current and add the number of current sub-
		 * directories.
		 */
		subDirs += cMountInfo::getSubDirs(**it);
		//subDirs += (*it)->numberFiles(FT_DIR);

		/* Get files in sub-directories + the ones
		 * in the current directory */
		subFiles += cMountInfo::getSubFiles(**it);
		//subFiles += (*it)->numberFiles(FT_REG);

		subSize += cMountInfo::getSubSize(**it);

		//subSize += (*it)->getSubSize();
	}

	subDirs += infoObj.numberFiles(FT_DIR);
	subFiles += infoObj.numberFiles(FT_REG);

	infoObj.setSubDirs(infoObj, subDirs);
	infoObj.setSubFiles(infoObj, subFiles);
	infoObj.setSubSize(infoObj, subSize);

	return;
}

void callFileSetters(cMountInfo& infoObj, filesystem::path& currPath, eFileType type, uint64_t& size)  {
	vector<fileAttrs>& reqAttrs = infoObj.getAttrs();

	vector<fileAttrs>::iterator req_iter;

	for  (req_iter = reqAttrs.begin(); req_iter != reqAttrs.end(); ++req_iter) {
		switch ( *req_iter ) {
			case FA_PATH:
				//Only want to store filename
				infoObj.setPath(infoObj, currPath);

				//In order to iterate it is easier if we take the whole
				//pathname rather than just the filename
				//infoObj.setPath(infoObj, currPath.filename());
				break;

			case FA_SIZE:
				if ( type != FT_DIR) {
					uint64_t fsize = filesystem::file_size( currPath );
					size += fsize;
					infoObj.setSize(infoObj, fsize);

				}
				break;

			default:
				cout << "Invalid file attribute request: " << __FILE__ << " on line " << __LINE__ << endl;
				break;
		}
	}
}

/* ======== For sorting cMount information ======== */
int sortPathForward( cMountInfo* path1, cMountInfo* path2) {
	if ( path1 == NULL || path2 == NULL )
		throw ((string) "Null pointer passed to sortPathForward");

	cout << "Inside sortPathForward" << endl;

	cout << "Getting string for path1" << endl;
	string sPath1 = path1->entryPath.filename();
	cout << "Getting string for path2" << endl;
	string sPath2 = path2->entryPath.filename();

	boost::algorithm::to_lower(sPath1);
	boost::algorithm::to_lower(sPath2);

	//To lowercase using std library
	//std::transform(sPath1.begin(), sPath1.end(), sPath1.begin(), ::tolower);
	//std::transform(sPath2.begin(), sPath2.end(), sPath2.begin(), ::tolower);

	cout << "sPath1 = " << sPath1 << endl;
	cout << "sPath2 = " << sPath2 << endl;

	int compVal = sPath1.compare(sPath2);
	cout << "compVal = " << compVal << endl;

	if ( compVal == 0 ) {
		return 0;
	}
	if ( compVal > 0 ) {
		return -1;
	}
	if ( compVal < 0 ) {
		return 1;
	}
}

