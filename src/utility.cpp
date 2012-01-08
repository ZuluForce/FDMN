#include "utility.h"

string sec_to_time(int seconds, int style) {
	stringstream stream;
	int num_years = seconds / SEC_PER_YEAR;
	seconds = seconds % SEC_PER_YEAR;

	int num_days = seconds / SEC_PER_DAY;
	seconds = seconds % SEC_PER_DAY;

	int num_hours = seconds / SEC_PER_HOUR;
	seconds = seconds % SEC_PER_HOUR;

	int num_minutes = seconds / SEC_PER_MIN;
	seconds = seconds % SEC_PER_MIN;

	switch ( style ) {
		case 0:
			stream << num_years << " Years ";
			stream << num_days << " Days ";
			stream << num_hours << " Hours ";
			stream << num_minutes << " Minutes ";
			stream << seconds << " Seconds";
			break;

		case 1:
			stream << num_years << ":";
			stream << num_days << ":";
			stream << num_hours << ":";
			stream << num_minutes << ":";
			stream << seconds;
			break;

		default:
		/*
			cerr << "Invalid style argument(" << style;
			cerr << ") give to sec_to_time";
			*/
			break;
	}

	return stream.str();
}



/* Thread-Safe Bounded Queue */

ts_queue* init_queue(int _size) {
	ts_queue *new_queue = (ts_queue*) malloc( sizeof(ts_queue) );

    new_queue->size = _size;
	new_queue->slots_available = _size;
	new_queue->start = 0;
	new_queue->end = 0;

	new_queue->data = (queue_t**) malloc(sizeof(queue_t*) * _size);

	pthread_mutex_init( &new_queue->q_lock, NULL);
	pthread_cond_init( &new_queue->q_empty, NULL);
	pthread_cond_init( &new_queue->q_full, NULL);

	if ( new_queue->data == NULL) {
		fprintf(stderr, "init_queue failed to allocate space\n");
		return NULL;
	}

	return new_queue;
}

int add_queue(queue_t* new_t, ts_queue &q) {

    if ( pthread_mutex_lock( &q.q_lock) ) {
		throw ((string) "Failed to acquire lock, add_queue(...)");
    }

	/* wait for space to become available */
	while ( q.slots_available <= 0 )
		pthread_cond_wait( &q.q_full, &q.q_lock );

	/* The regular queue acts like a ring buffer but
	 * it blocks when it fills unlike the buffer which
	 * overwrites old entries
	 */
    q.data[q.end] = new_t;
    q.end = (q.end + 1) % q.size;
    --q.slots_available;

	pthread_mutex_unlock( &q.q_lock );
    pthread_cond_signal( &q.q_empty );

    return 0;
}

/* Same aas add_queue but doesn't wait for space */
int add_queue_no_wait(queue_t* new_t, ts_queue &q, void (*free_fn) (void*)) {
	#ifdef DEBUG
	fprintf(stderr, "add_queue_no_wait called\n");
	#endif
    if ( pthread_mutex_lock( &q.q_lock) ) {
		throw ((string) "Failed to acquire lock, add_queue_no_wait(...)");
    }

	if ( q.slots_available <= 0 ) {

		/* The caller can give a function to free the
		 * queue_t if it was not added.
		 */
		if ( free_fn != NULL )
			free_fn( new_t );

		pthread_mutex_unlock( &q.q_lock );

		return 1;
	}

	q.data[q.end] = new_t;
	q.end = (q.end + 1) % q.size;
	--q.slots_available;

	pthread_mutex_unlock( &q.q_lock );
    pthread_cond_signal( &q.q_empty );

	return 0;
}

/* Remove item from queue from with blocking */
queue_t* rm_queue(ts_queue &q) {
    if ( pthread_mutex_lock( &q.q_lock) ) {
		throw ((string) "Failed to acquire lock, rm_queue(...)");
    }

    while ( q.slots_available == q.size ) {
       pthread_cond_wait( &q.q_empty, &q.q_lock );
    }

    queue_t* ret_val = q.data[q.start];
    q.start = (q.start + 1) % q.size;
    ++q.slots_available;

	pthread_mutex_unlock( &q.q_lock );
    pthread_cond_signal( &q.q_full );

    return ret_val;
}


/* Class for handling unique IDs */
node::node() {
    value = 0;
    next = NULL;
    return;
}

node::node(int id, node* next_node) {
    value = id;
    next = next_node;
    return;
}

cID_dispatch::cID_dispatch() {
    ID_counter = 0;
    ID_limit = INT_MAX;
    recent_ID = -1;

    /* free_buffer is a singly-linked list of free ID's */
    free_buffer = NULL;

    pthread_mutex_init( &ID_lock, NULL);
    return;
}

cID_dispatch::cID_dispatch(int limit) {
    ID_counter = 0;
    ID_limit = limit;
    recent_ID = -1;
    free_buffer = NULL;

    pthread_mutex_init( &ID_lock, NULL);
    return;
}

int cID_dispatch::ID_getid() {
    if ( free_buffer == NULL ) {
        recent_ID = ID_counter;
        return ID_counter++;
    }
    int new_id = free_buffer->value;

    free_ID* temp = free_buffer;
    free_buffer = free_buffer->next;
    delete(temp);

    recent_ID = new_id;
    return new_id;
}

int cID_dispatch::ID_getid_ts() {
	pthread_mutex_lock( &ID_lock );

    if ( free_buffer == NULL ) {
        recent_ID = ID_counter;
        pthread_mutex_unlock( &ID_lock );
        return ID_counter++;
    }
    int new_id = free_buffer->value;

    free_ID* temp = free_buffer;
    free_buffer = free_buffer->next;
    delete(temp);

    recent_ID = new_id;

    pthread_mutex_unlock( &ID_lock );
    return new_id;
}

int cID_dispatch::ID_recall() {
    return recent_ID;
}

void cID_dispatch::ID_returnid(int id) {
    if ( id == ID_counter ) {
        --ID_counter;
    } else {
        free_ID* reclaimed = new free_ID(id, free_buffer);
        free_buffer = reclaimed;
    }
    return;
}

void cID_dispatch::ID_returnid_ts(int id) {
	pthread_mutex_lock( &ID_lock );

    if ( id == ID_counter ) {
        --ID_counter;
    } else {
        free_ID* reclaimed = new free_ID(id, free_buffer);
        free_buffer = reclaimed;
    }

	pthread_mutex_unlock( &ID_lock );
    return;
}
