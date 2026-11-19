/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO3
 * Experiment 22: Hash Table with Insertion, Searching, and Deletion Operations
 * Collision resolution: Linear Probing with Tombstone marker (DELETED)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10
#define EMPTY -1
#define DELETED -2

typedef struct {
    int table[TABLE_SIZE];
} HashTable;

void initHashTable(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = EMPTY;
    }
}

int hashFunction(int key) {
    int h = key % TABLE_SIZE;
    if (h < 0) h += TABLE_SIZE;
    return h;
}

bool insert(HashTable *ht, int key) {
    int index = hashFunction(key);
    int startIndex = index;
    int firstDeleted = -1;

    // First check if key already exists or find suitable slot
    do {
        if (ht->table[index] == key) {
            printf("Key %d already exists in Hash Table!\n", key);
            return false;
        }
        if (ht->table[index] == DELETED && firstDeleted == -1) {
            firstDeleted = index;
        }
        if (ht->table[index] == EMPTY) {
            break;
        }
        index = (index + 1) % TABLE_SIZE;
    } while (index != startIndex);

    int targetSlot = (firstDeleted != -1) ? firstDeleted : index;

    if (ht->table[targetSlot] == EMPTY || ht->table[targetSlot] == DELETED) {
        ht->table[targetSlot] = key;
        printf("Inserted key %d at index %d\n", key, targetSlot);
        return true;
    }

    printf("Hash Table is completely full! Cannot insert %d\n", key);
    return false;
}

int search(HashTable *ht, int key) {
    int index = hashFunction(key);
    int startIndex = index;

    do {
        if (ht->table[index] == key) {
            return index; // Found
        }
        if (ht->table[index] == EMPTY) {
            return -1; // Not found because empty terminates probe sequence
        }
        index = (index + 1) % TABLE_SIZE;
    } while (index != startIndex);

    return -1;
}

bool deleteKey(HashTable *ht, int key) {
    int index = search(ht, key);
    if (index == -1) {
        printf("Key %d not found! Cannot delete.\n", key);
        return false;
    }

    // Place tombstone
    ht->table[index] = DELETED;
    printf("Deleted key %d from index %d (marked as DELETED).\n", key, index);
    return true;
}

void display(HashTable *ht) {
    printf("\n+-------+-----------+\n");
    printf("| Index | Key Value |\n");
    printf("+-------+-----------+\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->table[i] == EMPTY) {
            printf("|  %3d  |   EMPTY   |\n", i);
        } else if (ht->table[i] == DELETED) {
            printf("|  %3d  |  DELETED  |\n", i);
        } else {
            printf("|  %3d  |   %5d   |\n", i, ht->table[i]);
        }
    }
    printf("+-------+-----------+\n\n");
}

int main(void) {
    HashTable ht;
    initHashTable(&ht);

    printf("=================================================================\n");
    printf(" Experiment 22: Hash Table Insertion, Searching, and Deletion\n");
    printf("=================================================================\n");

    insert(&ht, 12);
    insert(&ht, 22); // Collides with 12
    insert(&ht, 32); // Collides with 12, 22
    insert(&ht, 45);
    insert(&ht, 77);

    display(&ht);

    // Searching
    int searchKey = 22;
    int idx = search(&ht, searchKey);
    printf("Searching for %d -> %s (at index %d)\n", searchKey, idx != -1 ? "FOUND" : "NOT FOUND", idx);

    // Deletion
    deleteKey(&ht, 22);
    display(&ht);

    // Search after deletion: 32 must still be found despite 22 being deleted!
    searchKey = 32;
    idx = search(&ht, searchKey);
    printf("Searching for %d after deleting 22 -> %s (at index %d)\n", searchKey, idx != -1 ? "FOUND" : "NOT FOUND", idx);

    // Insert new key that reuses tombstone slot
    insert(&ht, 52);
    display(&ht);

    return 0;
}
