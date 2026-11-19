/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO4, CO6
 * Value Added Experiment 02: Sorting Algorithms Empirical & Theoretical Benchmark
 *
 * Implemented Algorithms for Benchmark:
 *   1. Merge Sort
 *   2. Quick Sort
 *   3. Heap Sort
 *   4. Counting Sort
 *   5. Radix Sort (LSD)
 *   6. Bucket Sort
 *
 * Reads list of positive integers from user-specified input file.
 * Executes each on an identical copy of the dataset.
 * Measures:
 *   - Execution time (microseconds / milliseconds using clock())
 *   - Comparisons count
 *   - Data movements / Swaps count
 * Summarizes Best, Average, Worst case Time Complexities and Space Complexity.
 * Generates formatted comparative performance report in an output file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ELEMENTS 50000

typedef struct {
    char name[30];
    double timeTakenMs;
    long long comparisons;
    long long dataMovements;
    char bestTime[20];
    char avgTime[20];
    char worstTime[20];
    char spaceComplexity[20];
    char stability[10];
    char suitability[80];
} SortMetrics;

// Global counters for metrics tracking
long long g_comparisons = 0;
long long g_movements = 0;

void resetMetrics(void) {
    g_comparisons = 0;
    g_movements = 0;
}

// ---------------- 1. MERGE SORT ----------------
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        g_movements++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
        g_movements++;
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        g_comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
        g_movements++;
    }
    while (i < n1) {
        arr[k++] = L[i++];
        g_movements++;
    }
    while (j < n2) {
        arr[k++] = R[j++];
        g_movements++;
    }

    free(L);
    free(R);
}

void mergeSortUtil(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortUtil(arr, l, m);
        mergeSortUtil(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void benchMergeSort(int arr[], int n) {
    resetMetrics();
    mergeSortUtil(arr, 0, n - 1);
}

// ---------------- 2. QUICK SORT ----------------
void swapCount(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
    g_movements += 3; // 3 assignments per swap
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    g_movements++;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        g_comparisons++;
        if (arr[j] < pivot) {
            i++;
            swapCount(&arr[i], &arr[j]);
        }
    }
    swapCount(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortUtil(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortUtil(arr, low, pi - 1);
        quickSortUtil(arr, pi + 1, high);
    }
}

void benchQuickSort(int arr[], int n) {
    resetMetrics();
    quickSortUtil(arr, 0, n - 1);
}

// ---------------- 3. HEAP SORT ----------------
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n) {
        g_comparisons++;
        if (arr[l] > arr[largest]) largest = l;
    }
    if (r < n) {
        g_comparisons++;
        if (arr[r] > arr[largest]) largest = r;
    }

    if (largest != i) {
        swapCount(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void benchHeapSort(int arr[], int n) {
    resetMetrics();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swapCount(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// ---------------- 4. COUNTING SORT ----------------
void benchCountingSort(int arr[], int n) {
    resetMetrics();
    if (n <= 1) return;

    int maxVal = arr[0], minVal = arr[0];
    for (int i = 1; i < n; i++) {
        g_comparisons++;
        if (arr[i] > maxVal) maxVal = arr[i];
        g_comparisons++;
        if (arr[i] < minVal) minVal = arr[i];
    }

    int range = maxVal - minVal + 1;
    int *count = (int *)calloc(range, sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        count[arr[i] - minVal]++;
    }
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
        g_movements++;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        g_movements++;
    }

    free(count);
    free(output);
}

// ---------------- 5. RADIX SORT ----------------
void countSortRadix(int arr[], int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int d = (arr[i] / exp) % 10;
        output[count[d] - 1] = arr[i];
        count[d]--;
        g_movements++;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        g_movements++;
    }
    free(output);
}

void benchRadixSort(int arr[], int n) {
    resetMetrics();
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        g_comparisons++;
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countSortRadix(arr, n, exp);
    }
}

// ---------------- 6. BUCKET SORT ----------------
typedef struct BNode {
    int data;
    struct BNode *next;
} BNode;

void benchBucketSort(int arr[], int n) {
    resetMetrics();
    if (n <= 1) return;

    int maxVal = arr[0], minVal = arr[0];
    for (int i = 1; i < n; i++) {
        g_comparisons++;
        if (arr[i] > maxVal) maxVal = arr[i];
        g_comparisons++;
        if (arr[i] < minVal) minVal = arr[i];
    }

    int numBuckets = (n > 5) ? 5 : n;
    BNode **buckets = (BNode **)calloc(numBuckets, sizeof(BNode *));
    int range = maxVal - minVal + 1;

    for (int i = 0; i < n; i++) {
        int bIdx = (int)((long long)(arr[i] - minVal) * numBuckets / (range > 0 ? range : 1));
        if (bIdx >= numBuckets) bIdx = numBuckets - 1;

        BNode *newNode = (BNode *)malloc(sizeof(BNode));
        newNode->data = arr[i];
        newNode->next = buckets[bIdx];
        buckets[bIdx] = newNode;
        g_movements++;
    }

    int idx = 0;
    for (int b = 0; b < numBuckets; b++) {
        BNode *sorted = NULL;
        BNode *curr = buckets[b];
        while (curr != NULL) {
            BNode *nxt = curr->next;
            g_comparisons++;
            if (sorted == NULL || sorted->data >= curr->data) {
                curr->next = sorted;
                sorted = curr;
            } else {
                BNode *t = sorted;
                while (t->next != NULL && t->next->data < curr->data) {
                    g_comparisons++;
                    t = t->next;
                }
                curr->next = t->next;
                t->next = curr;
            }
            g_movements++;
            curr = nxt;
        }

        curr = sorted;
        while (curr != NULL) {
            arr[idx++] = curr->data;
            g_movements++;
            BNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(buckets);
}

int readData(const char *filename, int arr[]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return -1;
    int count = 0, val;
    while (fscanf(fp, "%d", &val) == 1 && count < MAX_ELEMENTS) {
        if (val >= 0) arr[count++] = val;
    }
    fclose(fp);
    return count;
}

void printReport(FILE *out, SortMetrics metrics[], int count, int datasetSize, const char *filename) {
    fprintf(out, "========================================================================================================\n");
    fprintf(out, "          PERFORMANCE ANALYSIS AND COMPARATIVE REPORT OF SORTING ALGORITHMS\n");
    fprintf(out, "========================================================================================================\n");
    fprintf(out, "Input File    : %s\n", filename);
    fprintf(out, "Dataset Size  : %d elements\n", datasetSize);
    fprintf(out, "Analysis Date : Automated Lab Evaluation Benchmark\n");
    fprintf(out, "--------------------------------------------------------------------------------------------------------\n\n");

    fprintf(out, "+----+---------------+----------+---------------+--------------+------------+------------+------------+---------+\n");
    fprintf(out, "| No | Algorithm     | Time(ms) | Comparisons   | Movements    | Best Time  | Avg Time   | Worst Time | Space   |\n");
    fprintf(out, "+----+---------------+----------+---------------+--------------+------------+------------+------------+---------+\n");

    for (int i = 0; i < count; i++) {
        fprintf(out, "| %2d | %-13s | %8.4f | %13lld | %12lld | %-10s | %-10s | %-10s | %-7s |\n",
                i + 1,
                metrics[i].name,
                metrics[i].timeTakenMs,
                metrics[i].comparisons,
                metrics[i].dataMovements,
                metrics[i].bestTime,
                metrics[i].avgTime,
                metrics[i].worstTime,
                metrics[i].spaceComplexity);
    }
    fprintf(out, "+----+---------------+----------+---------------+--------------+------------+------------+------------+---------+\n\n");

    fprintf(out, "DETAILED ALGORITHM PROPERTIES & SUITABILITY MATRIX:\n");
    fprintf(out, "--------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        fprintf(out, "[%d] %s:\n", i + 1, metrics[i].name);
        fprintf(out, "    * Stability            : %s\n", metrics[i].stability);
        fprintf(out, "    * Asymptotic Complexities: Best=%s, Avg=%s, Worst=%s, Space=%s\n",
                metrics[i].bestTime, metrics[i].avgTime, metrics[i].worstTime, metrics[i].spaceComplexity);
        fprintf(out, "    * Suitability Analysis : %s\n\n", metrics[i].suitability);
    }
    fprintf(out, "========================================================================================================\n");
}

int main(int argc, char *argv[]) {
    char inputFilename[256] = "sample_input.txt";
    char reportFilename[256] = "sorting_analysis_report.txt";

    if (argc > 1) {
        strncpy(inputFilename, argv[1], sizeof(inputFilename) - 1);
        inputFilename[sizeof(inputFilename) - 1] = '\0';
    }

    int originalData[MAX_ELEMENTS];
    int n = readData(inputFilename, originalData);

    if (n <= 0) {
        printf("Error: Could not read valid data from '%s'!\n", inputFilename);
        return 1;
    }

    printf("=================================================================\n");
    printf(" Value Added Exp 02: Comparative Sorting Performance Analysis\n");
    printf("=================================================================\n");
    printf("Loaded %d elements from '%s'.\n", n, inputFilename);
    printf("Executing sorting algorithms on identical copies of dataset...\n\n");

    SortMetrics metrics[6] = {
        {"Merge Sort",    0, 0, 0, "O(n log n)", "O(n log n)", "O(n log n)", "O(n)",   "Stable",   "Large datasets, external sorting, linked lists; guaranteed O(n log n)."},
        {"Quick Sort",    0, 0, 0, "O(n log n)", "O(n log n)", "O(n^2)",     "O(log n)","Unstable", "General in-memory arrays; very fast cache-friendly partitioning."},
        {"Heap Sort",     0, 0, 0, "O(n log n)", "O(n log n)", "O(n log n)", "O(1)",   "Unstable", "Systems with strict O(1) memory budget and worst-case time guarantees."},
        {"Counting Sort", 0, 0, 0, "O(n + k)",   "O(n + k)",   "O(n + k)",   "O(k)",   "Stable",   "Small positive integer ranges where range k is comparable to n."},
        {"Radix Sort",    0, 0, 0, "O(d*(n+b))", "O(d*(n+b))", "O(d*(n+b))", "O(n + b)","Stable",  "Fixed-length integers/keys; overcomes comparison-based lower bounds."},
        {"Bucket Sort",   0, 0, 0, "O(n + k)",   "O(n + k)",   "O(n^2)",     "O(n + k)","Stable",  "Uniformly distributed data across an interval; fast linear expectation."}
    };

    int workArr[MAX_ELEMENTS];
    clock_t start, end;

    // 1. Merge Sort
    memcpy(workArr, originalData, n * sizeof(int));
    start = clock();
    benchMergeSort(workArr, n);
    end = clock();
    metrics[0].timeTakenMs = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    metrics[0].comparisons = g_comparisons;
    metrics[0].dataMovements = g_movements;

    // 2. Quick Sort
    memcpy(workArr, originalData, n * sizeof(int));
    start = clock();
    benchQuickSort(workArr, n);
    end = clock();
    metrics[1].timeTakenMs = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    metrics[1].comparisons = g_comparisons;
    metrics[1].dataMovements = g_movements;

    // 3. Heap Sort
    memcpy(workArr, originalData, n * sizeof(int));
    start = clock();
    benchHeapSort(workArr, n);
    end = clock();
    metrics[2].timeTakenMs = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    metrics[2].comparisons = g_comparisons;
    metrics[2].dataMovements = g_movements;

    // 4. Counting Sort
    memcpy(workArr, originalData, n * sizeof(int));
    start = clock();
    benchCountingSort(workArr, n);
    end = clock();
    metrics[3].timeTakenMs = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    metrics[3].comparisons = g_comparisons;
    metrics[3].dataMovements = g_movements;

    // 5. Radix Sort
    memcpy(workArr, originalData, n * sizeof(int));
    start = clock();
    benchRadixSort(workArr, n);
    end = clock();
    metrics[4].timeTakenMs = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    metrics[4].comparisons = g_comparisons;
    metrics[4].dataMovements = g_movements;

    // 6. Bucket Sort
    memcpy(workArr, originalData, n * sizeof(int));
    start = clock();
    benchBucketSort(workArr, n);
    end = clock();
    metrics[5].timeTakenMs = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    metrics[5].comparisons = g_comparisons;
    metrics[5].dataMovements = g_movements;

    // Print summary to console
    printReport(stdout, metrics, 6, n, inputFilename);

    // Save summary to output report file
    FILE *reportFp = fopen(reportFilename, "w");
    if (reportFp) {
        printReport(reportFp, metrics, 6, n, inputFilename);
        fclose(reportFp);
        printf("\nDetailed comparative performance report generated at '%s'.\n", reportFilename);
    }

    return 0;
}
