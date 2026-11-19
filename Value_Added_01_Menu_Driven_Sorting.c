/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO5, CO6
 * Value Added Experiment 01: Menu-Driven Step-by-Step Sorting System
 *
 * Implemented Algorithms:
 *  1. Merge Sort
 *  2. Quick Sort
 *  3. Heap Sort
 *  4. Counting Sort
 *  5. Radix Sort
 *  6. Bucket Sort
 *
 * Reads list of positive integers from user-specified input file.
 * Displays array state after each significant step/phase and pauses for Enter.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ELEMENTS 1000

// Helper to pause and prompt user
void pauseStep(void) {
    printf("   [Press ENTER to continue to next step...]");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void printArrayState(const char *phaseName, int arr[], int n) {
    printf("\n--> %s:\n    [ ", phaseName);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
    pauseStep();
}

int readDataFromFile(const char *filename, int arr[]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Could not open input file '%s'!\n", filename);
        return -1;
    }

    int count = 0;
    int val;
    while (fscanf(fp, "%d", &val) == 1 && count < MAX_ELEMENTS) {
        if (val < 0) {
            printf("Warning: Ignoring non-positive integer %d\n", val);
            continue;
        }
        arr[count++] = val;
    }

    fclose(fp);
    return count;
}

// ---------------- MERGE SORT ----------------
void merge(int arr[], int l, int m, int r, int totalN, int *stepCount) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);

    char msg[64];
    snprintf(msg, sizeof(msg), "Step %d (Merged sub-arrays [%d..%d] and [%d..%d])", ++(*stepCount), l, m, m+1, r);
    printArrayState(msg, arr, totalN);
}

void mergeSortUtil(int arr[], int l, int r, int totalN, int *stepCount) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortUtil(arr, l, m, totalN, stepCount);
        mergeSortUtil(arr, m + 1, r, totalN, stepCount);
        merge(arr, l, m, r, totalN, stepCount);
    }
}

void runMergeSort(int arr[], int n) {
    int stepCount = 0;
    printArrayState("Initial Array before Merge Sort", arr, n);
    mergeSortUtil(arr, 0, n - 1, n, &stepCount);
}

// ---------------- QUICK SORT ----------------
void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

int partition(int arr[], int low, int high, int totalN, int *stepCount) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);

    char msg[64];
    snprintf(msg, sizeof(msg), "Step %d (Partition around pivot %d at index %d)", ++(*stepCount), pivot, i + 1);
    printArrayState(msg, arr, totalN);

    return (i + 1);
}

void quickSortUtil(int arr[], int low, int high, int totalN, int *stepCount) {
    if (low < high) {
        int pi = partition(arr, low, high, totalN, stepCount);
        quickSortUtil(arr, low, pi - 1, totalN, stepCount);
        quickSortUtil(arr, pi + 1, high, totalN, stepCount);
    }
}

void runQuickSort(int arr[], int n) {
    int stepCount = 0;
    printArrayState("Initial Array before Quick Sort", arr, n);
    quickSortUtil(arr, 0, n - 1, n, &stepCount);
}

// ---------------- HEAP SORT ----------------
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void runHeapSort(int arr[], int n) {
    printArrayState("Initial Array before Heap Sort", arr, n);

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    printArrayState("Phase 1: Built Max-Heap", arr, n);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);

        char msg[64];
        snprintf(msg, sizeof(msg), "Extraction Phase (Pass %d)", n - i);
        printArrayState(msg, arr, n);
    }
}

// ---------------- COUNTING SORT ----------------
void runCountingSort(int arr[], int n) {
    printArrayState("Initial Array before Counting Sort", arr, n);

    int maxVal = arr[0], minVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
        if (arr[i] < minVal) minVal = arr[i];
    }

    int range = maxVal - minVal + 1;
    int *count = (int *)calloc(range, sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) count[arr[i] - minVal]++;
    printArrayState("Phase 1: Frequencies Counted", arr, n);

    for (int i = 1; i < range; i++) count[i] += count[i - 1];
    printArrayState("Phase 2: Cumulative Positions Determined", arr, n);

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    for (int i = 0; i < n; i++) arr[i] = output[i];
    printArrayState("Phase 3: Elements Placed in Stable Output Array", arr, n);

    free(count);
    free(output);
}

// ---------------- RADIX SORT ----------------
void runRadixSort(int arr[], int n) {
    printArrayState("Initial Array before Radix Sort", arr, n);

    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    int pass = 1;
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        int *output = (int *)malloc(n * sizeof(int));
        int count[10] = {0};

        for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        for (int i = 0; i < n; i++) arr[i] = output[i];
        free(output);

        char msg[64];
        snprintf(msg, sizeof(msg), "Radix Pass %d (Sorted by digit place %d)", pass++, exp);
        printArrayState(msg, arr, n);
    }
}

// ---------------- BUCKET SORT ----------------
typedef struct BNode {
    int data;
    struct BNode *next;
} BNode;

void runBucketSort(int arr[], int n) {
    printArrayState("Initial Array before Bucket Sort", arr, n);

    int maxVal = arr[0], minVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
        if (arr[i] < minVal) minVal = arr[i];
    }

    int numBuckets = (n > 5) ? 5 : n;
    BNode **buckets = (BNode **)calloc(numBuckets, sizeof(BNode *));
    int range = maxVal - minVal + 1;

    // Scatter
    for (int i = 0; i < n; i++) {
        int bIdx = (int)((long long)(arr[i] - minVal) * numBuckets / (range > 0 ? range : 1));
        if (bIdx >= numBuckets) bIdx = numBuckets - 1;

        BNode *newNode = (BNode *)malloc(sizeof(BNode));
        newNode->data = arr[i];
        newNode->next = buckets[bIdx];
        buckets[bIdx] = newNode;
    }
    printArrayState("Phase 1: Scattered Elements into Buckets", arr, n);

    // Sort & Gather
    int idx = 0;
    for (int b = 0; b < numBuckets; b++) {
        // Insertion sort on bucket linked list
        BNode *sorted = NULL;
        BNode *curr = buckets[b];
        while (curr != NULL) {
            BNode *nxt = curr->next;
            if (sorted == NULL || sorted->data >= curr->data) {
                curr->next = sorted;
                sorted = curr;
            } else {
                BNode *t = sorted;
                while (t->next != NULL && t->next->data < curr->data) {
                    t = t->next;
                }
                curr->next = t->next;
                t->next = curr;
            }
            curr = nxt;
        }

        // Put back into arr
        curr = sorted;
        while (curr != NULL) {
            arr[idx++] = curr->data;
            BNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    printArrayState("Phase 2: Buckets Sorted and Gathered", arr, n);
    free(buckets);
}

int main(int argc, char *argv[]) {
    char filename[256] = "sample_input.txt";

    printf("=================================================================\n");
    printf(" Value Added Exp 01: Menu-Driven Sorting System\n");
    printf("=================================================================\n\n");

    if (argc > 1) {
        strncpy(filename, argv[1], sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
    } else {
        printf("Using default input file: '%s'\n", filename);
    }

    int originalData[MAX_ELEMENTS];
    int workData[MAX_ELEMENTS];
    int n = readDataFromFile(filename, originalData);

    if (n <= 0) {
        printf("Failed to load data. Exiting...\n");
        return 1;
    }
    printf("Successfully loaded %d elements from '%s'.\n", n, filename);

    int choice = 0;
    while (1) {
        // Reset working copy
        for (int i = 0; i < n; i++) workData[i] = originalData[i];

        printf("\n------------- SORTING ALGORITHMS MENU -------------\n");
        printf(" 1. Merge Sort\n");
        printf(" 2. Quick Sort\n");
        printf(" 3. Heap Sort\n");
        printf(" 4. Counting Sort\n");
        printf(" 5. Radix Sort\n");
        printf(" 6. Bucket Sort\n");
        printf(" 7. Change Input File\n");
        printf(" 8. Exit\n");
        printf("---------------------------------------------------\n");
        printf("Enter your choice (1-8): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Exiting menu.\n");
            break;
        }

        // Consume trailing newline from scanf
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        if (choice == 8) {
            printf("\nExiting. Thank you!\n");
            break;
        }

        switch (choice) {
            case 1: runMergeSort(workData, n); break;
            case 2: runQuickSort(workData, n); break;
            case 3: runHeapSort(workData, n); break;
            case 4: runCountingSort(workData, n); break;
            case 5: runRadixSort(workData, n); break;
            case 6: runBucketSort(workData, n); break;
            case 7: {
                printf("Enter new filename: ");
                if (scanf("%255s", filename) == 1) {
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    n = readDataFromFile(filename, originalData);
                    if (n > 0) {
                        printf("Loaded %d elements from '%s'.\n", n, filename);
                    }
                }
                continue;
            }
            default:
                printf("Invalid choice (%d)! Please choose a valid option (1-8).\n", choice);
                continue;
        }

        printf("\n===================================================\n");
        printf(" RESULT: Data has been sorted successfully!\n");
        printf(" Sorted Array: [ ");
        for (int i = 0; i < n; i++) {
            printf("%d ", workData[i]);
        }
        printf("]\n");
        printf("===================================================\n");
    }

    return 0;
}
