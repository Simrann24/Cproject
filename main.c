#include "proxy_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define MAX_BYTES 4096    //max allowed size of request/response
#define MAX_CLIENTS 400     //max number of client requests served at a time
#define MAX_SIZE 200*(1<<20)     //size of the cache
#define MAX_ELEMENT_SIZE 10*(1<<20)     //max size of an element in cache

typedef struct cache_element cache_element;

struct cache_element{
    char* data;         //data stores response
    int len;          //length of data i.e.. sizeof(data)...
    char* url;        //url stores the request
	time_t lru_time_track;    //lru_time_track stores the latest time the element is  accesed
    cache_element* next;    //pointer to next element
};

cache_element* find(char* url);
int add_cache_element(char* data,int size,char* url);
void remove_cache_element();

int port_number = 8080;				// Default Port
int proxy_socketId;					// socket descriptor of proxy server
pthread_t tid[MAX_CLIENTS];         //array to store the thread ids of clients
sem_t seamaphore;	                //if client requests exceeds the max_clients this seamaphore puts the
                                    //waiting threads to sleep and wakes them when traffic on queue decreases
//sem_t cache_lock;			       
pthread_mutex_t lock;               //lock is used for locking the cache


cache_element* head;                //pointer to the cache
int cache_size;             //cache_size denotes the current size of the cache//
			    //
			    //



int main(int argc, char * argv[]) {

	int client_socketId, client_len; // client_socketId == to store the client socket id
	struct sockaddr_in server_addr, client_addr; // Address of client and server to be assigned

    sem_init(&seamaphore,0,MAX_CLIENTS); // Initializing seamaphore and lock
    pthread_mutex_init(&lock,NULL); // Initializing lock for cache


	if(argc == 2)        //checking whether two arguments are received or not
	{
		port_number = atoi(argv[1]);
	}
	else
	{
		printf("Too few arguments\n");
		exit(1);
	}

	printf("Setting Proxy Server Port : %d\n",port_number);

    //creating the proxy socket
	proxy_socketId = socket(AF_INET, SOCK_STREAM, 0);

	if( proxy_socketId < 0)
	{
		perror("Failed to create socket.\n");
		exit(1);
	}





}



E37: No write since last change (add ! to override)                                                                                                                                             49,9-30       AllE37: No write since last change (add ! to override)                                                                                                                                             49,9-30       All
