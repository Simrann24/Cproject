#include <stdio.h>

#include "../proxy_parse.h"

#include "cache_element.h"


cache_element* find(char* url){

// Checks for url in the cache if found returns pointer to the respective cache element or else returns NULL
    cache_element* site=NULL;
	//sem_wait(&cache_lock);
    int temp_lock_val = pthread_mutex_lock(&lock);
	printf("Remove Cache Lock Acquired %d\n",temp_lock_val);
    if(head!=NULL){
        site = head;
        while (site!=NULL)
        {
            if(!strcmp(site->url,url)){
				printf("LRU Time Track Before : %ld", site->lru_time_track);
                printf("\nurl found\n");
				// Updating the time_track
				site->lru_time_track = time(NULL);
				printf("LRU Time Track After : %ld", site->lru_time_track);
				break;
            }
            site=site->next;
        }
    }
	else {
    printf("\nurl not found\n");
	}
	//sem_post(&cache_lock);
    temp_lock_val = pthread_mutex_unlock(&lock);
	printf("Remove Cache Lock Unlocked %d\n",temp_lock_val);
    return site;
}

void remove_cache_element(){
    // If cache is not empty searches for the node which has the least lru_time_track and deletes it
    cache_element * p ;  	// Cache_element Pointer (Prev. Pointer)
	cache_element * q ;		// Cache_element Pointer (Next Pointer)
	cache_element * temp;	// Cache element to remove
    //sem_wait(&cache_lock);
    int temp_lock_val = pthread_mutex_lock(&lock);
	printf("Remove Cache Lock Acquired %d\n",temp_lock_val);
	if( head != NULL) { // Cache != empty
		for (q = head, p = head, temp =head ; q -> next != NULL;
			q = q -> next) { // Iterate through entire cache and search for oldest time track
			if(( (q -> next) -> lru_time_track) < (temp -> lru_time_track)) {
				temp = q -> next;
				p = q;
			}
		}
		if(temp == head) {
			head = head -> next; /*Handle the base case*/
		} else {
			p->next = temp->next;
		}
		cache_size = cache_size - (temp -> len) - sizeof(cache_element) -
		strlen(temp -> url) - 1;     //updating the cache size
		free(temp->data);
		free(temp->url); // Free the removed element
		free(temp);
	}
	//sem_post(&cache_lock);
    temp_lock_val = pthread_mutex_unlock(&lock);
	printf("Remove Cache Lock Unlocked %d\n",temp_lock_val);
}

int add_cache_element(char* data, int size, char* url) {
    // Adds element to the cache
    int temp_lock_val = pthread_mutex_lock(&lock);
    printf("Add Cache Lock Acquired %d\n", temp_lock_val);

    int element_size = size + 1 + strlen(url) + sizeof(cache_element); // Calculate size of the new element

    // If element size is larger than the allowed max element size, reject the addition
    if (element_size > MAX_ELEMENT_SIZE) {
        printf("Element too large to cache.\n");
        pthread_mutex_unlock(&lock);
        return -1;
    }

    // While the cache size plus new element exceeds maximum cache size, remove elements (LRU)
    while (cache_size + element_size > MAX_SIZE) {
        remove_cache_element(); // Remove least recently used element
    }

    // Allocate memory for the new cache element
    cache_element* new_element = (cache_element*)malloc(sizeof(cache_element));
    if (!new_element) {
        perror("Failed to allocate memory for cache element\n");
        pthread_mutex_unlock(&lock);
        return -1;
    }

    // Fill the new cache element data
    new_element->data = (char*)malloc(size);
    memcpy(new_element->data, data, size);
    new_element->len = size;

    new_element->url = (char*)malloc(strlen(url) + 1);
    strcpy(new_element->url, url);

    // Set the LRU time to current time
    new_element->lru_time_track = time(NULL);

    // Add new element at the head of the cache list
    new_element->next = head;
    head = new_element;

    // Update cache size
    cache_size += element_size;

    printf("Added to cache: %s\n", url);

    pthread_mutex_unlock(&lock);
    printf("Add Cache Lock Released\n");

    return 0;
}
