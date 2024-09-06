#ifndef CACHE_ELEMENT_H
#define CACHE_ELEMENT_H

#include <semaphore.h>
#include <time.h>
#include <pthread.h>

typedef struct cache_element cache_element;

struct cache_element {
    char* data;              // data stores response
    int len;                // length of data i.e., sizeof(data)...
    char* url;              // url stores the request
    time_t lru_time_track;  // lru_time_track stores the latest time the element is accessed
    cache_element* next;    // pointer to next element
};

#define MAX_BYTES 4096               // max allowed size of request/response
#define MAX_CLIENTS 400             // max number of client requests served at a time
#define MAX_SIZE (200 * (1 << 20))  // size of the cache
#define MAX_ELEMENT_SIZE (10 * (1 << 20)) // max size of an element in cache

// Function declarations
cache_element* find(char* url);
int add_cache_element(char* data, int size, char* url);
void remove_cache_element();

// Extern declarations
extern int port_number;              // Default Port
extern int proxy_socketId;          // socket descriptor of proxy server
extern pthread_t tid[MAX_CLIENTS];  // array to store the thread ids of clients

extern pthread_mutex_t lock;        // lock is used for locking the cache
extern sem_t seamaphore;             // semaphore used for synchronization

extern cache_element* head;         // pointer to the cache
extern int cache_size;              // cache_size denotes the current size of the cache

#endif // CACHE_ELEMENT_H

