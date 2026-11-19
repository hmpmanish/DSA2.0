# CSCR2501 - Advanced Data Structures Lab (DSA 2.0)

[![Language](https://img.shields.io/badge/Language-C%20%2F%20C99-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Compiler](https://img.shields.io/badge/Compiler-GCC%20MinGW-green.svg)](https://gcc.gnu.org/)
[![Status](https://img.shields.io/badge/Build-Passing%20(30%2F30)-brightgreen.svg)]()
[![License](https://img.shields.io/badge/License-MIT-orange.svg)]()

> **Sharda School of Computing Science & Engineering**  
> **Department of Computer Science & Engineering**  
> **Course Code:** CSCR2501  
> **Course Title:** Advanced Data Structures Lab  
> **Term:** 2601 | **Credits:** 2 (L: 0, T: 0, P: 4, C: 2)  
> **Repository:** [https://github.com/hmpmanish/DSA2.0](https://github.com/hmpmanish/DSA2.0)

---

## 🎯 Course Outcomes (COs)

- **CO1:** Explain the fundamental concepts of linear and non-linear data structures including stacks, queues, trees, and graphs.
- **CO2:** Implement operations on linear data structures and binary trees using appropriate algorithms.
- **CO3:** Apply graph algorithms and hashing techniques to solve computational problems.
- **CO4:** Analyze algorithm complexities using asymptotic notations and recurrence relations.
- **CO5:** Construct efficient solutions using divide-and-conquer strategies and related sorting algorithms.
- **CO6:** Evaluate various sorting methods based on performance metrics and problem constraints.

---

## 📚 List of Lab Experiments (30 / 30 Implemented)

### Core Experiments (1 - 28)

| Exp # | Source File | Experiment Name | Course Outcome |
|:-----:|:------------|:----------------|:--------------:|
| **01** | [`Exp01_Stack_Array.c`](Exp01_Stack_Array.c) | Implement Stack using Array (Push, Pop, Peek, Display) | **CO1** |
| **02** | [`Exp02_Infix_To_Postfix.c`](Exp02_Infix_To_Postfix.c) | Convert Infix Expression to Postfix Expression using Stack | **CO1** |
| **03** | [`Exp03_Linear_Queue_Array.c`](Exp03_Linear_Queue_Array.c) | Implement Linear Queue using Array | **CO1** |
| **04** | [`Exp04_Postfix_Evaluation.c`](Exp04_Postfix_Evaluation.c) | Evaluate Postfix Expression using Stack | **CO2** |
| **05** | [`Exp05_Stack_LinkedList.c`](Exp05_Stack_LinkedList.c) | Implement Stack using Singly Linked List | **CO2** |
| **06** | [`Exp06_Circular_Queue_LinkedList.c`](Exp06_Circular_Queue_LinkedList.c) | Implement Circular Queue using Linked List | **CO2** |
| **07** | [`Exp07_Priority_Queue_LinkedList.c`](Exp07_Priority_Queue_LinkedList.c) | Implement Priority Queue using Linked List | **CO2** |
| **08** | [`Exp08_Deque.c`](Exp08_Deque.c) | Implement Double Ended Queue (Deque) | **CO2** |
| **09** | [`Exp09_Linear_Queue_LinkedList.c`](Exp09_Linear_Queue_LinkedList.c) | Implement Linear Queue using Linked List | **CO2** |
| **10** | [`Exp10_Binary_Tree_LinkedList.c`](Exp10_Binary_Tree_LinkedList.c) | Implement Binary Tree using Linked List | **CO2** |
| **11** | [`Exp11_Binary_Tree_Traversals.c`](Exp11_Binary_Tree_Traversals.c) | Preorder, Inorder, and Postorder Traversals of Binary Tree | **CO2** |
| **12** | [`Exp12_Binary_Tree_Count_Leaf_Height.c`](Exp12_Binary_Tree_Count_Leaf_Height.c) | Count Total Nodes, Leaf Nodes, and Height of Binary Tree | **CO2** |
| **13** | [`Exp13_BST_Insert_Search_Delete.c`](Exp13_BST_Insert_Search_Delete.c) | Binary Search Tree (BST) with Insertion, Search, Deletion | **CO2** |
| **14** | [`Exp14_BST_Search.c`](Exp14_BST_Search.c) | Recursive vs Iterative Search in Binary Search Tree | **CO2** |
| **15** | [`Exp15_AVL_Tree.c`](Exp15_AVL_Tree.c) | Self-Balancing AVL Tree (Rotations: LL, RR, LR, RL) | **CO2** |
| **16** | [`Exp16_Graph_AdjMatrix_AdjList.c`](Exp16_Graph_AdjMatrix_AdjList.c) | Graph Representation using Adjacency Matrix & Adjacency List | **CO3** |
| **17** | [`Exp17_BFS_Traversal.c`](Exp17_BFS_Traversal.c) | Breadth First Search (BFS) Traversal of Graph | **CO3** |
| **18** | [`Exp18_DFS_Traversal.c`](Exp18_DFS_Traversal.c) | Depth First Search (DFS) Traversal of Graph | **CO3** |
| **19** | [`Exp19_Prims_MST.c`](Exp19_Prims_MST.c) | Minimum Spanning Tree (MST) using Prim's Algorithm | **CO3** |
| **20** | [`Exp20_Kruskals_MST.c`](Exp20_Kruskals_MST.c) | Minimum Spanning Tree (MST) using Kruskal's Algorithm | **CO3** |
| **21** | [`Exp21_HashTable_DivisionMethod.c`](Exp21_HashTable_DivisionMethod.c) | Simple Hash Table using Division Hash Function & Linear Probing | **CO3** |
| **22** | [`Exp22_HashTable_Operations.c`](Exp22_HashTable_Operations.c) | Hash Table Insertion, Searching, and Deletion with Tombstones | **CO3** |
| **23** | [`Exp23_Analysis_Recursive_Algorithm.c`](Exp23_Analysis_Recursive_Algorithm.c) | Mathematical Analysis of Recursive Algorithm (Hanoi & Binary Search) | **CO4** |
| **24** | [`Exp24_Analysis_NonRecursive_Algorithm.c`](Exp24_Analysis_NonRecursive_Algorithm.c) | Mathematical Analysis of Non-Recursive Algorithm (Summations) | **CO4** |
| **25** | [`Exp25_Heap_Sort.c`](Exp25_Heap_Sort.c) | Implementation of Heap Sort Algorithm | **CO5** |
| **26** | [`Exp26_Counting_Sort.c`](Exp26_Counting_Sort.c) | Implementation of Stable Counting Sort Algorithm | **CO5** |
| **27** | [`Exp27_Radix_Sort.c`](Exp27_Radix_Sort.c) | Implementation of Radix Sort (LSD) Algorithm | **CO5** |
| **28** | [`Exp28_Bucket_Sort.c`](Exp28_Bucket_Sort.c) | Implementation of Bucket Sort Algorithm | **CO5** |

---

### Value Added Experiments

| Exp # | Source File | Experiment Name | Course Outcome | Description |
|:-----:|:------------|:----------------|:--------------:|:------------|
| **VA-01** | [`Value_Added_01_Menu_Driven_Sorting.c`](Value_Added_01_Menu_Driven_Sorting.c) | Menu-Driven Sorting System | **CO5, CO6** | Interactive step-by-step sorting for Merge Sort, Quick Sort, Heap Sort, Counting Sort, Radix Sort, and Bucket Sort reading from a user file. Pauses after each phase. |
| **VA-02** | [`Value_Added_02_Sorting_Performance_Analysis.c`](Value_Added_02_Sorting_Performance_Analysis.c) | Performance Analysis & Benchmark | **CO4, CO6** | Benchmarks all 6 sorting algorithms on identical data. Generates comparative reports with comparisons, movements, execution time, and asymptotic bounds. |

---

## 🛠️ How to Compile and Run

### Prerequisites
- GCC / MinGW compiler installed and added to PATH.

### Compile Any Single Experiment
```bash
gcc -Wall -Wextra -std=c99 Exp01_Stack_Array.c -o Exp01.exe
./Exp01.exe
```

### Run Value Added Experiment 01 (Step-by-Step Menu)
```bash
gcc -Wall -Wextra -std=c99 Value_Added_01_Menu_Driven_Sorting.c -o VA01.exe
./VA01.exe sample_input.txt
```

### Run Value Added Experiment 02 (Benchmark & Output Report)
```bash
gcc -Wall -Wextra -std=c99 Value_Added_02_Sorting_Performance_Analysis.c -o VA02.exe
./VA02.exe sample_input.txt
```
This generates `sorting_analysis_report.txt` containing the performance table and suitability analysis.

---

## 📊 Summary of Sorting Complexities

| Algorithm | Best Time | Average Time | Worst Time | Space | Stability |
|:----------|:---------:|:------------:|:----------:|:-----:|:---------:|
| **Merge Sort** | $\Omega(n \log n)$ | $\Theta(n \log n)$ | $O(n \log n)$ | $O(n)$ | Yes (Stable) |
| **Quick Sort** | $\Omega(n \log n)$ | $\Theta(n \log n)$ | $O(n^2)$ | $O(\log n)$ | No (Unstable) |
| **Heap Sort** | $\Omega(n \log n)$ | $\Theta(n \log n)$ | $O(n \log n)$ | $O(1)$ | No (Unstable) |
| **Counting Sort** | $\Omega(n + k)$ | $\Theta(n + k)$ | $O(n + k)$ | $O(k)$ | Yes (Stable) |
| **Radix Sort** | $\Omega(d(n + b))$ | $\Theta(d(n + b))$ | $O(d(n + b))$ | $O(n + b)$ | Yes (Stable) |
| **Bucket Sort** | $\Omega(n + k)$ | $\Theta(n + k)$ | $O(n^2)$ | $O(n + k)$ | Yes (Stable) |

---

## 👤 Author
- **Manish Pandey** ([@hmpmanish](https://github.com/hmpmanish))
- Course: CSCR2501 - Advanced Data Structures Lab
