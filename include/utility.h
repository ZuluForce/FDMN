#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <limits.h>
#include <signal.h>
#include <sys/types.h>

#include <pthread.h>
//#include <boost/thread/mutex.hpp>
//#include <boost/thread/condition_variable.hpp>

#define SEC_PER_YEAR 31536000
#define SEC_PER_DAY 86400
#define SEC_PER_HOUR 3600
#define SEC_PER_MIN 60

#define STR(x) #x

using namespace std;

string sec_to_time(int seconds, int style = 0);

struct queue_t {
	int fd;
	int id;
};

typedef struct ts_queue {
	pthread_mutex_t q_lock;
	pthread_cond_t q_full;
	pthread_cond_t q_empty;

    int size;
    int slots_available;
    int start;
    int end;

	queue_t **data;
} ts_queue;

/* ------- Regular Thread-Safe Queue ----------- */
ts_queue* init_queue(int);
int add_queue(queue_t*, ts_queue&);
int add_queue_no_wait(queue_t*, ts_queue&, void (*free_fn) (queue_t*));
queue_t* rm_queue(ts_queue&);
/* --------------------------------------------- */


/* ID System */
typedef struct node {
    public:
        int value;
        node* next;
        node();
        node(int, node*);
} free_ID;

typedef class cID_dispatch {
    private:
        int ID_counter;
        int ID_limit;
        int recent_ID;
        node* free_buffer;

        pthread_mutex_t ID_lock;

    public:
        cID_dispatch();
        cID_dispatch(int limit);
        int ID_getid();
        int ID_getid_ts();
        int ID_recall();
        void ID_returnid(int id);
        void ID_returnid_ts(int id);
} cID_dispatch;



/* Sort Functions Return Values:
 * -1 : Desired order
 * 0  : Equal
 * 1  : Reverse order (will be switched)
 */
template <typename T>
void QuickPartition(std::vector<T> items, int (*sort_fn) (T,T),
					int left, int right, int pivot) {

	T temp;
	T pivotValue = items[pivot];

	temp = items[right];
	items[right] = pivotValue;
	items[pivot] = temp;

	int placeIndex = left;
	for (int i = left; i < right; ++i) {
		if (sort_fn(items[i], pivotValue) == 1) {
			/* Swap the values */
			temp = items[i];
			items[i] = items[placeIndex];
			items[placeIndex] = temp;

			++placeIndex;
		}
	}

	/* Put pivot into correct location */
	items[right] = items[placeIndex];
	items[placeIndex] = pivotValue;

	return;
}

enum pivotType {
	pivotMiddle,
	pivotRandom
};

/* Quicksort Implementation for std::vectors
 * Uses in-place partitioning for better cache performance
 */
template <typename T>
void QuicksortVector(std::vector<T> items, int (*sort_fn) (T,T), pivotType pType,
						int start, int end) {
	if ( (end - start) <= 1 )
		return;
	int pivot;

	switch ( pType ) {
		case pivotMiddle:
			pivot = (start + end) / 2;
			break;

		case pivotRandom:
			pivot = start + (rand() % (start - end));
			break;

		default:
			return;
	}

	QuickPartition<T>(items, sort_fn, start, end, pivot);
	QuicksortVector<T>(items, sort_fn, pType, start, pivot - 1);
	QuicksortVector<T>(items, sort_fn, pType, start, pivot + 1);
	return;
}


/* Flag Parser */
#define ADD_OPTION(map,x) map[x]
#define ADD_EXTRA(map,option,extra) map[option][extra]
#define ACCEPT_ANY_EXTRA(map,option) map[option][' ']
#define OPTION_SET(map,option,delimit) map[option][delimit].set
#define EXTRA_SET(map,option,extra) map[option][extra].set

#define INT_ARG_FLAG (char) 0
#define STR_ARG_FLAG (char) 1

#define ADD_INT_ARG(map,option) map[option][INT_ARG_FLAG]
#define ADD_STR_ARG(map,option) map[option][STR_ARG_FLAG]

#define GET_INT_ARG(map,option) map[option][INT_ARG_FLAG].intArg
#define GET_STR_START(map,option) map[option][STR_ARG_FLAG].strStart
#define GET_STR_LEN(map,option) map[option][STR_ARG_FLAG].strLen
#define EXTRACT_STRING(map,option,str) str.substr(GET_STR_START(map,option),GET_STR_LEN(map,option))

#define BUF_SIZE 20

typedef struct {
	bool set;
	int intArg;
	int strStart, strLen;
} uOption;

typedef std::map<char, std::map<char,uOption> > argMap;

//bool nextChar(string &str, char &dest, int &index);
void parseFlags(argMap &args, string &input, char argDelimit = '-');
void clearFlags(argMap &args);

class staticOptions {
	private:
		argMap options;

	public:
		argMap& operator ()();
};
#endif // UTILITY_H_INCLUDED
