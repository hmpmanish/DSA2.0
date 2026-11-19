/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO5
 * Experiment 27: Implementation of Radix Sort (LSD)
 * Strategy: Non-comparative digit-by-digit sorting using Counting Sort subroutine
 * Time Complexity: O(d * (n + b)), Space Complexity: O(n + b)
 */

#include <stdio.h>
#include <stdlib.h>

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

void printArray(const char *label, int arr[], int n) {
    printf("%-24s: [ ", label);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

// A function to do counting sort of arr[] according to the digit represented by exp (1, 10, 100, ...)
void countSortForRadix(int arr[], int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Change count[i] so that count[i] now contains actual position of this digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array (traverse backwards for stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy the output array to arr[], so that arr[] now contains sorted numbers according to current digit
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);

    // Do counting sort for every digit.
    // Note that instead of passing digit number, exp is passed (1, 10, 100, ...)
    int pass = 1;
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countSortForRadix(arr, n, exp);

        char passMsg[32];
        snprintf(passMsg, sizeof(passMsg), "After Exp = %d (Pass %d)", exp, pass++);
        printArray(passMsg, arr, n);
    }
}

int main(void) {
    printf("=================================================================\n");
    printf(" Experiment 27: Radix Sort Algorithm (LSD)\n");
    printf("=================================================================\n\n");

    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArray("Initial Array", arr, n);
    printf("-----------------------------------------------------------------\n");

    radixSort(arr, n);

    printf("-----------------------------------------------------------------\n");
    printArray("Fully Sorted Array", arr, n);

    return 0;
}
