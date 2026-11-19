/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO3
 * Experiment 21: Hash Table Implementation using Division Hash Function
 * Hash function: h(k) = k mod m (where m is table size)
 * Collision resolution: Linear Probing
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 11
#define EMPTY -1

typedef struct {
    int table[TABLE_SIZE];
} HashTable;

void initHashTable(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = EMPTY;
    }
}

int hashDivision(int key) {
    int hash = key % TABLE_SIZE;
    if (hash < 0) hash += TABLE_SIZE;
    return hash;
}

void insertKey(HashTable *ht, int key) {
    int index = hashDivision(key);
    int startIndex = index;
    int probes = 0;

    while (ht->table[index] != EMPTY) {
        probes++;
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) {
            printf("Error: Hash Table is full! Cannot insert %d\n", key);
            return;
        }
    }

    ht->table[index] = key;
    printf("Inserted %4d -> Hash slot %2d (Probes: %d)\n", key, index, probes);
}

void displayHashTable(HashTable *ht) {
    printf("\n+-------+-----------+\n");
    printf("| Index | Key Value |\n");
    printf("+-------+-----------+\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->table[i] == EMPTY) {
            printf("|  %3d  |   EMPTY   |\n", i);
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
    printf(" Experiment 21: Hash Table with Division Hash Function (m = %d)\n", TABLE_SIZE);
    printf("=================================================================\n");

    int keysToInsert[] = {23, 45, 12, 56, 78, 34, 11, 89, 90};
    int n = sizeof(keysToInsert) / sizeof(keysToInsert[0]);

    for (int i = 0; i < n; i++) {
        insertKey(&ht, keysToInsert[i]);
    }

    displayHashTable(&ht);

    return 0;
}
