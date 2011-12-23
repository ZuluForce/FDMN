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

    while ( true ) {
        cout << endl << ">> ";
        getline(cin, input);

        #ifdef DEBUG
        cout << "You entered: " << input << endl;
        #endif

        if ( input.compare("exit") == 0 )
            return 0;

        eval_input(input);
    }

	return 0;
}

void* start_admin(void *args) {
	if ( !initialized ) {
		fprintf(stderr, "Admin interface not initialized\n");
		return NULL;
	}

	string input;

    while ( true ) {
        cout << endl << ">> ";
        getline(cin, input);

        #ifdef DEBUG
        cout << "You entered: " << input << endl;
        #endif

        if ( input.compare("exit") == 0 )
            return NULL;

        eval_input(input);
    }

	return NULL;
}

void eval_input(string input) {
    char first_char;

    if ( input.size() > 0)
        first_char = input[0];
    else
        first_char = ' ';

	#ifdef DEBUG
	cout << "First char of input: " << first_char << endl;
	#endif

    switch ( first_char ) {
    	EVAL_CASE('a',a);
    	EVAL_CASE('t',t);
    	/*
        case 'a':
            eval_cmd_a(input);
            break;

		case 't':
			eval_cmd_t(input);
			break;
			*/

        default:
            cerr << "Invalid Command: ";
            cerr <<input.substr(0,input.find_first_of(' '));
            cerr << endl;
    }
    return;
}
