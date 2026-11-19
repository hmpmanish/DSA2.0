/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO5
 * Experiment 25: Implementation of Heap Sort
 * Strategy: Max-Heap construction followed by repeated root extraction
 */

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// To heapify a subtree rooted with node i which is an index in arr[].
// n is size of heap
void heapify(int arr[], int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // left = 2*i + 1
    int right = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void printArray(const char *prefix, int arr[], int n) {
    printf("%-22s: [ ", prefix);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void heapSort(int arr[], int n) {
    // Step 1: Build max heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    printArray("After Building Max Heap", arr, n);

    // Step 2: One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);

        char stepMsg[32];
        snprintf(stepMsg, sizeof(stepMsg), "After Pass %d", n - i);
        printArray(stepMsg, arr, n);
    }
}

int main(void) {
    printf("=================================================================\n");
    printf(" Experiment 25: Heap Sort Algorithm\n");
    printf("=================================================================\n\n");

    int arr[] = {12, 11, 13, 5, 6, 7, 19, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArray("Original Array", arr, n);
    printf("-----------------------------------------------------------------\n");

    heapSort(arr, n);

    printf("-----------------------------------------------------------------\n");
    printArray("Sorted Array (Result)", arr, n);

    return 0;
}
