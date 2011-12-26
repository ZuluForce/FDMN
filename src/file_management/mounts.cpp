#include "mounts.h"

cMounts::cMounts() {

	return;
}

cMounts::~~cMounts() {
	return;
}

void cMounts::add_local(string &path) {
	mount *new_mount = malloc( sizeof(mount) );
	new_mount->type = MT_LOCAL;

	strncpy(new_mount->mountLoc._local.full_path, path.c_str(), FILENAME_MAX);

	mounts.push_back(new_mount);

	return;
}

void cMounts::add_local(char *path) {
	mount *new_mount = malloc( sizeof(mount) );
	new_mount->type = MT_LOCAL;

	strncpy(new_mount->mountLoc._local.full_path, path, FILENAME_MAX);

	mounts.push_back(new_mount);

	return;
}
