#include "file_management/mounts.h"

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

void cMountInfo::setPath(absFileInfo& infoObj, string path) {
	try {
		cMountInfo& mountObj = dynamic_cast<cMountInfo&>( infoObj );
		mountObj.entryPath = filesystem::path(path);
	} catch (std::bad_cast ex) {
		cerr << "Error casting to cMountInfo: " << __FILE__ << endl;
		return;
	}

	return;
}

void cMountInfo::setPath(absFileInfo& infoObj, filesystem::path path) {
	try {
		cMountInfo& mountObj = dynamic_cast<cMountInfo&>( infoObj );
		mountObj.entryPath = path;
	} catch (std::bad_cast ex) {
		cerr << "Error casting to cMountInfo" << endl;
		return;
	}

	return;
}

void cMountInfo::setType(absFileInfo& infoObj, eFileType type) {
	try {
		cMountInfo& mountObj = dynamic_cast<cMountInfo&>( infoObj );
		mountObj.entryType = type;
	} catch (std::bad_cast ex) {
		cerr << "Error casting to cMountInfo" << endl;
		return;
	}

	return;
}

void cMountInfo::setSize(absFileInfo &infoObj, ssize_t size) {
	try {
		cMountInfo& mountObj = dynamic_cast<cMountInfo&>( infoObj );
		mountObj.entrySize = size;
	} catch (std::bad_cast ex) {
		cerr << "Error casting to cMountInfo" << endl;
		return;
	}

	return;
}

absFileInfo* cMountInfo::addFile(absFileInfo& infoObj, eFileType type) {
	cMountInfo *mountObjPtr = NULL;
	try {
		cMountInfo& mountObj = dynamic_cast<cMountInfo&>( infoObj );
		mountObjPtr = &mountObj; //Get around try-block scope restriction
	} catch (std::bad_cast ex) {
		cerr << "Error casting to cMountInfo" << endl;
		return NULL;
	}

	cMountInfo *newMountObj = new cMountInfo();
	newMountObj->setType(*newMountObj, type);

	switch ( type ) {
		case FT_REG:
			mountObjPtr->addRegular(newMountObj);
			break;

		default:
			/* Not supporting file type yet */
			delete(newMountObj);
			return NULL;
	}

	return newMountObj;
}

void cMountInfo::addRegular(cMountInfo *newInfo) {
	regularFiles.push_back(newInfo);
}

void cMountInfo::printContent(int indentLvl) {
	for ( int i = 0; i < indentLvl; ++i) {
		cout << "  ";
	}

	cout << entryPath << endl;
}

/* ============================================================*/

cMountSys::cMountSys() {
	mounts.reserve(defaultVectorInit);
	return;
}

cMountSys::~cMountSys() {

	return;
}

void cMountSys::setRoot(string &rootDir) {
	/*
	if ( chdir(rootDir.c_str()) == -1 ) {
		string error("Failed to change root directory: ");
		error += strerror(errno);
		fprintf(stderr, error.c_str());
		_log->log_simple(error.c_str());

		return;
	}

	string msg("Root directory changed to: ");
	msg += rootDir;
	_log->log_simple(msg.c_str());
	*/
	return;
}

bool cMountSys::newMount(string location) {
	int newID = mountIDs.ID_getid_ts();

	//Check if the vector needs to be expanded
	if ( newID >= mounts.size())
		mounts.resize( mounts.size() * defaultVectorResize);

	cMountInfo *newMountInfo = new cMountInfo();
	mounts[newID] = newMountInfo;

	try {
		fillFileInfo(*newMountInfo, location);
	} catch (boost::filesystem::filesystem_error error) {
		string err_msg = "Failed to build mount information object: \n\tError: ";
		err_msg += error.what();

		_log->log_color(err_msg, redErrorStrong);

		return false;
	}

	return false;
}
