#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a key-value pair
typedef struct KeyValue {
char* key;
char* value;
struct KeyValue* next;
} KeyValue;

// Define the structure for the hash table
typedef struct HashTable {
KeyValue* table[100];
} HashTable;

// Hash function to convert a string into an index in the hash table
unsigned int hash(const char* key) {
unsigned int hash_val = 0;
while (*key != '\0') {
hash_val = (hash_val << 5) + *key;
key++;
}
return (hash_val%100);
}

// Function to initialize the hash table
void initHashTable(HashTable* ht) {
for (int i = 0; i < 100; i++)
ht->table[i] = NULL;
}

// Function to insert a key-value pair into the hash table
void insert(HashTable* ht, const char* key, const char* value) {
unsigned int index = hash(key);

// Create a new key-value pair
KeyValue* new_pair = (KeyValue*)malloc(sizeof(KeyValue));
new_pair->key = strdup(key);
new_pair->value = strdup(value);
new_pair->next = NULL;

// Check if the index is empty
if (ht->table[index] == NULL) {
    ht->table[index] = new_pair;
} 
else {
    // Handle collision by chaining
    KeyValue* current = ht->table[index];
    while (current->next != NULL)
        current = current->next;
    current->next = new_pair;
}
}

// Function to retrieve the value associated with a key from the hash table
const char* get(HashTable* ht, const char* key) {
unsigned int index = hash(key);

// Search for the key in the linked list at the calculated index
KeyValue* current = ht->table[index];
while (current != NULL) {
    if (strcmp(current->key, key) == 0)
        return current->value;
    current = current->next;
}

// Key not found
return NULL;
}

// Function to free the memory used by the hash table
void freeHashTable(HashTable* ht) {
for (int i = 0; i < 100; i++) {
KeyValue* current = ht->table[i];
while (current != NULL) {
KeyValue* next = current->next;
free(current->key);
free(current->value);
free(current);
current = next;
}
}
}

int main() {
// Create and initialize a hash table
HashTable myHT;
initHashTable(&myHT);

// Insert key-value pairs
insert(&myHT, "name", "John");
insert(&myHT, "age", "25");
insert(&myHT, "city", "New York");

// Retrieve values based on keys
printf("Name: %s\n", get(&myHT, "name"));
printf("Age: %s\n", get(&myHT, "age"));
printf("City: %s\n", get(&myHT, "city"));

// Free the memory used by the hash table
freeHashTable(&myHT);

return 0;
}
