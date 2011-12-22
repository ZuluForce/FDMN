#include "fdmn.h"

int main(int argc, char** argv) {
    if ( argc < 2 ) {
        cerr << "Usage: " << argv[0] << " <ini file>" << endl;
        return 1;
    }

    /* Create Core Server Object */
    cServerCore core( argv[1] /* Settings File */);
    core.start_server();

	return 0;
}
