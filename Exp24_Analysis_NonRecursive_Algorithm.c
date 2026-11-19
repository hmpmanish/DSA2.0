/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO4
 * Experiment 24: Mathematical Analysis of Non-recursive (Iterative) Algorithms
 * Focus: Summations, Operation Counts, and Asymptotic Verification
 *
 * Algorithm 1: Selection Sort Comparisons
 *   Summation: C(n) = Sum_{i=0}^{n-2} (n - 1 - i) = n*(n - 1)/2 => Theta(n^2)
 *
 * Algorithm 2: Standard Matrix Multiplication Multiplications
 *   Summation: M(n) = Sum_{i=1}^n Sum_{j=1}^n Sum_{k=1}^n 1 = n^3 => Theta(n^3)
 */

#include <stdio.h>
#include <stdlib.h>

long long selectionSortComparisonCount(int arr[], int n) {
    long long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        int temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
    return comparisons;
}

long long matrixMultiplicationOps(int n) {
    long long multiplications = 0;
    // Simulate n x n matrix multiplication operation counter
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                multiplications++;
            }
        }
    }
    return multiplications;
}

int main(void) {
    printf("=================================================================\n");
    printf(" Experiment 24: Mathematical Analysis of Non-Recursive Algorithms\n");
    printf("=================================================================\n\n");

    printf("--- PART 1: Selection Sort Comparisons Summation ---\n");
    printf("Formula: C(n) = n*(n - 1)/2 (Exact for any input)\n\n");
    printf("+-------+-----------------------+-------------------------+\n");
    printf("|   n   | Empirical Comparisons | Theory: n*(n - 1) / 2   |\n");
    printf("+-------+-----------------------+-------------------------+\n");

    int testSizes[] = {10, 20, 50, 100, 200, 500};
    int numSizes = sizeof(testSizes) / sizeof(testSizes[0]);

    for (int i = 0; i < numSizes; i++) {
        int n = testSizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            arr[j] = n - j; // Reverse sorted
        }

        long long actualComps = selectionSortComparisonCount(arr, n);
        long long theoreticalComps = (long long)n * (n - 1) / 2;

        printf("|  %4d |       %10lld      |        %10lld       |\n",
               n, actualComps, theoreticalComps);

        free(arr);
    }
    printf("+-------+-----------------------+-------------------------+\n\n");

    printf("--- PART 2: Matrix Multiplication Multiplications Summation ---\n");
    printf("Formula: M(n) = Sum_{i=1}^n Sum_{j=1}^n Sum_{k=1}^n 1 = n^3\n\n");
    printf("+-------+-----------------------------+---------------------------+\n");
    printf("|   n   | Measured Multiplications    | Theory: n^3               |\n");
    printf("+-------+-----------------------------+---------------------------+\n");

    int matSizes[] = {10, 20, 30, 50, 100};
    int numMatSizes = sizeof(matSizes) / sizeof(matSizes[0]);

    for (int i = 0; i < numMatSizes; i++) {
        int n = matSizes[i];
        long long actualOps = matrixMultiplicationOps(n);
        long long theoreticalOps = (long long)n * n * n;

        printf("|  %4d |          %10lld         |         %10lld        |\n",
               n, actualOps, theoreticalOps);
    }
    printf("+-------+-----------------------------+---------------------------+\n\n");
    printf("Conclusion: Empirical non-recursive loop execution counts identically match theoretical summations.\n");

    return 0;
}
