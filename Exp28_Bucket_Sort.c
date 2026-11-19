/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO5
 * Experiment 28: Implementation of Bucket Sort
 * Strategy: Scatter elements into buckets, sort buckets individually, gather results
 * Average Time Complexity: O(n + k)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void insertionSortBucket(Node **bucket) {
    if (*bucket == NULL || (*bucket)->next == NULL) {
        return;
    }

    Node *sorted = NULL;
    Node *curr = *bucket;

    while (curr != NULL) {
        Node *next = curr->next;

        if (sorted == NULL || sorted->data >= curr->data) {
            curr->next = sorted;
            sorted = curr;
        } else {
            Node *temp = sorted;
            while (temp->next != NULL && temp->next->data < curr->data) {
                temp = temp->next;
            }
            curr->next = temp->next;
            temp->next = curr;
        }
        curr = next;
    }
    *bucket = sorted;
}

void bucketSort(int arr[], int n, int numBuckets) {
    if (n <= 1) return;

    // 1. Find max and min
    int maxVal = arr[0], minVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
        if (arr[i] < minVal) minVal = arr[i];
    }

    // Allocate array of bucket heads
    Node **buckets = (Node **)calloc(numBuckets, sizeof(Node *));
    int range = maxVal - minVal + 1;

    // 2. Scatter elements into buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = (int)((long long)(arr[i] - minVal) * numBuckets / (range > 0 ? range : 1));
        if (bucketIndex >= numBuckets) {
            bucketIndex = numBuckets - 1;
        }

        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = arr[i];
        newNode->next = buckets[bucketIndex];
        buckets[bucketIndex] = newNode;
    }

    // 3. Sort each bucket and gather elements back into arr[]
    int idx = 0;
    for (int i = 0; i < numBuckets; i++) {
        insertionSortBucket(&buckets[i]);

        Node *curr = buckets[i];
        while (curr != NULL) {
            arr[idx++] = curr->data;
            Node *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    free(buckets);
}

void printArray(const char *label, int arr[], int n) {
    printf("%-20s: [ ", label);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

int main(void) {
    printf("=================================================================\n");
    printf(" Experiment 28: Bucket Sort Algorithm\n");
    printf("=================================================================\n\n");

    int arr[] = {29, 25, 3, 49, 9, 37, 21, 43, 15, 8, 32};
    int n = sizeof(arr) / sizeof(arr[0]);
    int numBuckets = 5;

    printArray("Unsorted Array", arr, n);
    printf("Sorting using %d buckets...\n", numBuckets);
    bucketSort(arr, n, numBuckets);
    printArray("Sorted Array", arr, n);

    return 0;
}
