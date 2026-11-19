/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO5
 * Experiment 26: Implementation of Counting Sort
 * Strategy: Non-comparison integer sorting using frequency & cumulative counts
 * Time Complexity: O(n + k), Space Complexity: O(k)
 */

#include <stdio.h>
#include <stdlib.h>

void printArray(const char *label, int arr[], int n) {
    printf("%-20s: [ ", label);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void countingSort(int arr[], int n) {
    if (n <= 1) return;

    // 1. Find maximum and minimum elements
    int maxVal = arr[0];
    int minVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
        if (arr[i] < minVal) minVal = arr[i];
    }

    int range = maxVal - minVal + 1;
    int *count = (int *)calloc(range, sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));

    if (!count || !output) {
        printf("Memory allocation error!\n");
        return;
    }

    // 2. Store count of each element
    for (int i = 0; i < n; i++) {
        count[arr[i] - minVal]++;
    }

    // 3. Change count[i] so that it contains actual position in output
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    // 4. Build output array in reverse order to ensure STABILITY
    for (int i = n - 1; i >= 0; i--) {
        int val = arr[i];
        output[count[val - minVal] - 1] = val;
        count[val - minVal]--;
    }

    // 5. Copy output array back to arr[]
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

int main(void) {
    printf("=================================================================\n");
    printf(" Experiment 26: Counting Sort Algorithm\n");
    printf("=================================================================\n\n");

    int arr[] = {4, 2, 2, 8, 3, 3, 1, 9, 6, 4, 7, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArray("Original Array", arr, n);
    countingSort(arr, n);
    printArray("Sorted Array", arr, n);

    return 0;
}
