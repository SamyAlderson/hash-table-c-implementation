// Include the necessary header for the hash table implementation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the hash table node
typedef struct Node {
    char key[256];
    char value[256];
    struct Node* next;
} Node;

// Define the structure for the hash table
typedef struct HashTable {
    int size;
    Node** buckets;
} HashTable;

// Function to create a new hash table
HashTable* createHashTable(int size) {
    HashTable* table = malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

// Function to insert a key-value pair into the hash table
void insert(HashTable* table, char* key, char* value) {
    int index = hashFunction(key, table->size);
    Node* node = table->buckets[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            // Update the value if the key already exists
            strcpy(node->value, value);
            return;
        }
        node = node->next;
    }
    // Create a new node and add it to the linked list
    Node* newNode = malloc(sizeof(Node));
    strcpy(newNode->key, key);
    strcpy(newNode->value, value);
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

// Function to get the value associated with a key
char* getValue(HashTable* table, char* key) {
    int index = hashFunction(key, table->size);
    Node* node = table->buckets[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

// Function to free the hash table
void freeHashTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        Node* node = table->buckets[i];
        while (node != NULL) {
            Node* next = node->next;
            free(node);
            node = next;
        }
    }
    free(table->buckets);
    free(table);
}
