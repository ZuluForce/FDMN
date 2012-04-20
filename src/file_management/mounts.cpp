#include "file_management/mounts.h"

extern cLog *_log;

cMountSys::cMountSys() {
	mounts.resize(defaultVectorInit);

	for (int i = 0; i < mounts.size(); ++i) {
		mounts[i] = NULL;
	}

	cout << "Initial size of mounts vector: " << mounts.size() << endl;

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
	if ( newID >= mounts.size() )
		mounts.resize( mounts.size() * defaultVectorResize);

	cMountInfo *newMountInfo = new cMountInfo();
	mounts[newID] = newMountInfo;

	try {
		filesystem::path newPath(location);
		fillFileInfo(*newMountInfo, newPath);
	} catch (boost::filesystem::filesystem_error error) {
		string err_msg = "Failed to build mount information object: \n\tError: ";
		err_msg += error.what();

		_log->log_color(err_msg, redErrorStrong);

		/* Cleanup */
		mountIDs.ID_returnid_ts(newID);
		delete(newMountInfo);

		return false;
	}

	cMountInfo::sortMounts(*mounts[newID]); //Sort the files and directories
	mounts[newID]->printContent();
	cMountInfo* mount = mounts[newID];
	cout << "Finished indexing mount " << newID << endl;
	//cout << "There are " << mounts[newID]->numberFiles(FT_REG) << " files in the new mount" << endl;
	cout << "Mount " << newID << " has " << cMountInfo::getSubFiles(*mount);
	cout << " files in " << cMountInfo::getSubDirs(*mount) << " directories" << endl;
	cout << "The new mount contains " << cMountInfo::getSubSize(*mount) << " bytes of data" << endl;

	return true;
}

bool cMountSys::newMount(filesystem::path& location) {
	cout << "Can't process now" << endl;

	return false;
}

void cMountSys::printMounts() {
	//cout << "mounts.size() = " << mounts.size() << endl;

	for ( int i = 0; i < mounts.size(); ++i) {
		//cout << "mount[" << i << "] = " << mounts[i] << endl;
		if ( mounts[i] != NULL ) {
			cout << "Mount " << i << ": " << mounts[i]->getPath() << endl;
		}
	}

	return;
}

void cMountSys::status(stringstream& stream) {
	if ( mountIDs.ID_recall() != -1) {
		stream << "Mount System:" << endl;

		for ( int i = 0; i < mounts.size(); ++i) {
			if ( mounts[i] != NULL )
				stream << "\tMount " << i << ": " << mounts[i]->getPath() << endl;
		}

		stream << endl;
	}

	return;
}

void cMountSys::cleanup() {

	return;
}
