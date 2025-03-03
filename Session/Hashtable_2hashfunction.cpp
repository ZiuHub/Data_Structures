#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10


typedef struct {
    char *key;
    int value;
    int filled; 
} Entry;


typedef struct {
    Entry table[TABLE_SIZE];
} HashTable;

// Hash function using Mid square technique
int hash_mid_square(const char *key) {
    int hash = 0;
    int len = strlen(key);
    int mid = len / 2;
    char mid_char[2] = {key[mid], '\0'};
    int mid_val = atoi(mid_char);
    hash = mid_val * mid_val;
    return hash % TABLE_SIZE;
}

// Hash function using division
int hash_division(const char *key) {
    int hash = 0;
    int i;
    for (i = 0; key[i] != '\0'; i++) {
        hash += key[i];
    }
    return hash % TABLE_SIZE;
}

// Hash function using digit extraction
int hash_digit_extraction(const char *key) {
    int hash = 0;
    int i;
    for (i = 0; key[i] != '\0'; i++) {
        if (key[i] >= 0 && key[i] <= 9) {
            hash += key[i] - '0';
        }
    }
    return hash % TABLE_SIZE;
}

// Insert a key-value pair into the hash table with linear probing for collision handling
void insert(HashTable *ht, const char *key, int value, int (*hash_function)(const char*)) {
    int index = hash_function(key);
    int original_index = index;

    // Linear probing until an empty slot is found
    while (ht->table[index].filled) {
        index = (index + 1) % TABLE_SIZE;
        // If we wrap around and reach the original index, the table is full
        if (index == original_index) {
//            fprintf(stderr, "Hash table is full\n");
            exit(1);
        }
    }

    ht->table[index].key = strdup(key);
    ht->table[index].value = value;
    ht->table[index].filled = 1;
}

// Search for a key in the hash table
int search(HashTable *ht, const char *key, int (*hash_function)(const char*)) {
    int index = hash_function(key);
    int original_index = index;

    // Linear probing until we find the key or an empty slot
    while (ht->table[index].filled) {
        if (strcmp(ht->table[index].key, key) == 0) {
            return ht->table[index].value;
        }
        index = (index + 1) % TABLE_SIZE;
        // If we wrap around and reach the original index or an empty slot, the key is not in the table
        if (index == original_index || !ht->table[index].filled) {
            return -1;
        }
    }

    return -1; // Key not found
}

// Main function for testing
int main() {
    HashTable ht;
    memset(&ht, 0, sizeof(HashTable));

    insert(&ht, "apple", 5, hash_mid_square);
    insert(&ht, "banana", 7, hash_division);
    insert(&ht, "orange", 10, hash_digit_extraction);
    insert(&ht, "grape", 15, hash_mid_square);
    insert(&ht, "watermelon", 20, hash_division);

    printf("Value for 'apple' using Mid square technique: %d\n", search(&ht, "apple", hash_mid_square));
    printf("Value for 'banana' using division: %d\n", search(&ht, "banana", hash_division));
    printf("Value for 'orange' using digit extraction: %d\n", search(&ht, "orange", hash_digit_extraction));
    printf("Value for 'grape' using Mid square technique: %d\n", search(&ht, "grape", hash_mid_square));
    printf("Value for 'watermelon' using division: %d\n", search(&ht, "watermelon", hash_division));
    printf("Value for 'kiwi' using digit extraction: %d\n", search(&ht, "kiwi", hash_digit_extraction));

    return 0;
}

