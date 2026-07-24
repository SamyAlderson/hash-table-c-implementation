#include "config.h"
#include <stdlib.h>
#include <string.h>

// Hash table structure
typedef struct hash_table {
    unsigned int size;
    unsigned int num_buckets;
    struct bucket {
        char* key;
        int value;
        struct bucket* next;
    }** buckets;
} hash_table_t;

// Hash function to map key to bucket index
unsigned int hash(char* key) {
    unsigned int hash_value = 0;
    while (*key != '\0') {
        hash_value = (hash_value * 31 + *key) % (HASH_TABLE_SIZE + 1);
        key++;
    }
    return hash_value;
}

// Initialize hash table
hash_table_t* init_hash_table(unsigned int size) {
    // Allocate memory for the hash table structure
    hash_table_t* ht = (hash_table_t*) malloc(sizeof(hash_table_t));
    if (!ht) {
        fprintf(stderr, "Error initializing hash table: memory allocation failed\n");
        return NULL;
    }

    // Allocate memory for the buckets
    ht->buckets = (struct bucket**) malloc(size * sizeof(struct bucket*));
    if (!ht->buckets) {
        free(ht);
        fprintf(stderr, "Error initializing hash table: memory allocation failed\n");
        return NULL;
    }

    // Initialize each bucket to NULL
    for (unsigned int i = 0; i < size; i++) {
        ht->buckets[i] = NULL;
    }

    ht->size = size;
    ht->num_buckets = 0;
    return ht;
}

// Add a key-value pair to the hash table
int add(hash_table_t* ht, char* key, int value) {
    if (!ht) {
        fprintf(stderr, "Error adding key-value pair: hash table is NULL\n");
        return -1;
    }

    unsigned int bucket_index = hash(key) % ht->size;
    struct bucket* bucket = ht->buckets[bucket_index];

    // If the bucket is empty, create a new bucket
    if (!bucket) {
        bucket = (struct bucket*) malloc(sizeof(struct bucket));
        if (!bucket) {
            fprintf(stderr, "Error adding key-value pair: memory allocation failed\n");
            return -1;
        }
        bucket->key = (char*) malloc(strlen(key) + 1);
        if (!bucket->key) {
            free(bucket);
            fprintf(stderr, "Error adding key-value pair: memory allocation failed\n");
            return -1;
        }
        strcpy(bucket->key, key);
        bucket->value = value;
        bucket->next = NULL;
        ht->buckets[bucket_index] = bucket;
        ht->num_buckets++;
    } else {
        // If the bucket is not empty, check if the key already exists
        while (bucket) {
            if (strcmp(bucket->key, key) == 0) {
                // If the key already exists, update the value
                bucket->value = value;
                return 0;
            }
            if (bucket->next) {
                bucket = bucket->next;
            } else {
                // If the key does not exist, add a new entry to the end of the bucket
                struct bucket* new_bucket = (struct bucket*) malloc(sizeof(struct bucket));
                if (!new_bucket) {
                    fprintf(stderr, "Error adding key-value pair: memory allocation failed\n");
                    return -1;
                }
                new_bucket->key = (char*) malloc(strlen(key) + 1);
                if (!new_bucket->key) {
                    free(new_bucket);
                    fprintf(stderr, "Error adding key-value pair: memory allocation failed\n");
                    return -1;
                }
                strcpy(new_bucket->key, key);
                new_bucket->value = value;
                new_bucket->next = NULL;
                bucket->next = new_bucket;
                ht->num_buckets++;
                return 0;
            }
        }
    }
    // If the bucket is not empty and the key does not exist, add a new entry to the end of the bucket
    struct bucket* new_bucket = (struct bucket*) malloc(sizeof(struct bucket));
    if (!new_bucket) {
        fprintf(stderr, "Error adding key-value pair: memory allocation failed\n");
        return -1;
    }
    new_bucket->key = (char*) malloc(strlen(key) + 1);
    if (!new_bucket->key) {
        free(new_bucket);
        fprintf(stderr, "Error adding key-value pair: memory allocation failed\n");
        return -1;
    }
    strcpy(new_bucket->key, key);
    new_bucket->value = value;
    new_bucket->next = NULL;
    bucket->next = new_bucket;
    ht->num_buckets++;
    return 0;
}

// Get the value associated with a key from the hash table
int get(hash_table_t* ht, char* key) {
    if (!ht) {
        fprintf(stderr, "Error getting value: hash table is NULL\n");
        return -1;
    }

    unsigned int bucket_index = hash(key) % ht->size;
    struct bucket* bucket = ht->buckets[bucket_index];

    while (bucket) {
        if (strcmp(bucket->key, key) == 0) {
            return bucket->value;
        }
        if (bucket->next) {
            bucket = bucket->next;
        } else {
            break;
        }
    }

    // If the key is not found, return -1
    return -1;
}

// Free the memory allocated by the hash table
void free_hash_table(hash_table_t* ht) {
    if (!ht) {
        return;
    }

    for (unsigned int i = 0; i < ht->size; i++) {
        struct bucket* bucket = ht->buckets[i];
        while (bucket) {
            struct bucket* next = bucket->next;
            free(bucket->key);
            free(bucket);
            bucket = next;
        }
    }

    free(ht->buckets);
    free(ht);
}