#include "admin/interface.h"

static bool initialized = false;

int init_admin() {
	/* Load Options */

	initialized = true;
	return 0;
}

int start_admin() {
	if ( !initialized ) {
		fprintf(stderr, "Admin interface not initialized\n");
		return -1;
	}

	string input;

	getline(cin, input);

	cout << "You entered: " << input << endl;

	return 0;
}
