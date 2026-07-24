// Include necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the hash table structure
typedef struct HashTable {
    int size;
    int capacity;
    int* keys;
    int* values;
} HashTable;

// Function to create a new hash table
HashTable* createHashTable(int capacity) {
    HashTable* table = malloc(sizeof(HashTable));
    table->size = 0;
    table->capacity = capacity;
    table->keys = malloc(sizeof(int) * capacity);
    table->values = malloc(sizeof(int) * capacity);
    return table;
}

// Function to insert a key-value pair into the hash table
void insert(HashTable* table, int key, int value) {
    int index = key % table->capacity;
    if (table->keys[index] == 0) {
        table->keys[index] = key;
        table->values[index] = value;
        table->size++;
    } else {
        printf("Key already exists in the hash table\n");
    }
}

// Function to print the hash table
void printHashTable(HashTable* table) {
    for (int i = 0; i < table->capacity; i++) {
        if (table->keys[i] != 0) {
            printf("Key: %d, Value: %d\n", table->keys[i], table->values[i]);
        }
    }
}

int main() {
    HashTable* table = createHashTable(10);
    insert(table, 5, 10);
    insert(table, 15, 20);
    printHashTable(table);
    return 0;
}