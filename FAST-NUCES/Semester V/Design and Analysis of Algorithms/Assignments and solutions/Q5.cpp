#include <iostream>
#include <vector>
#include <algorithm> 
#include <chrono>

// Global variables to count comparisons
int heap_count = 0;
int merge_count = 0;
int quick_count = 0;

using namespace std;

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    heap_count++;

    if (r < n && arr[r] > arr[largest])
        largest = r;
    heap_count++;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        merge_count++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) {
        return; // returns recursively
    }
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // pivot
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            quick_count++;
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printVector(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << "\n";
}

int main() {
    int n = 1000000; // Set the size of the array

    // Generate random numbers and store them in vector A
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        A[i] = rand();
    }

    vector<int> B = A; // Copy A to B
    vector<int> C = A; // Copy A to C

    // Measure time for Heap Sort
    auto start = chrono::high_resolution_clock::now();
    heapSort(A, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duration = end - start;

    cout << "\nHeap Sort : ";
    // printVector(A); // Uncomment if you want to print the sorted array
    cout << "Number of comparisons made in heap sort : " << heap_count;
    cout << "\nTime taken by Heap Sort: " << duration.count() << " milliseconds" << endl;

    // Measure time for Merge Sort
    start = chrono::high_resolution_clock::now();
    mergeSort(B, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    duration = end - start;

    cout << "\nMerge Sort : ";
    // printVector(B); // Uncomment if you want to print the sorted array
    cout << "Number of comparisons made in Merge sort : " << merge_count;
    cout << "\nTime taken by Merge Sort: " << duration.count() << " milliseconds" << endl;

    // Measure time for Quick Sort
    start = chrono::high_resolution_clock::now();
    quickSort(C, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    duration = end - start;

    cout << "\nQuick Sort : ";
    // printVector(C); // Uncomment if you want to print the sorted array
    cout << "Number of comparisons made in Quick sort : " << quick_count;
    cout << "\nTime taken by Quick Sort: " << duration.count() << " milliseconds" << endl;

    return 0;
}
