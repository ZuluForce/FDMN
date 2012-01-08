#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <limits.h>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#define SEC_PER_YEAR 31536000
#define SEC_PER_DAY 86400
#define SEC_PER_HOUR 3600
#define SEC_PER_MIN 60

using namespace std;

string sec_to_time(int seconds, int style = 0);

struct queue_t {
	int fd;
	int id;
};

typedef struct ts_queue {
	boost::mutex q_lock;
	boost::condition_variable q_full;
	boost::condition_variable q_empty;

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

        boost::mutex ID_lock;

    public:
        cID_dispatch();
        cID_dispatch(int limit);
        int ID_getid();
        int ID_getid_ts();
        int ID_recall();
        void ID_returnid(int id);
        void ID_returnid_ts(int id);
} cID_dispatch;
#endif // UTILITY_H_INCLUDED
