#include <iostream>
using namespace std;

int MaxSubArraySum(int A[], int n) {
    if (n == 0) {
        // Handle the case of an empty array.
        return 0;
    }
    int start_index=0;
    int globalSum = A[0];   // Initialize globalSum to the first element of A.
    int MaxSum = A[0];      // Initialize MaxSum[1] to the first element of A.

    for (int i = 1; i < n; i++) {
        if (MaxSum + A[i] > A[i]) {
            MaxSum = MaxSum + A[i];
        } else {
            MaxSum = A[i];
            start_index=i;
        }

        if (globalSum < MaxSum) {
            globalSum = MaxSum;
        }
    }

    return globalSum;
}

int main() {
    int A[] = {2,-4,3,4,-3,5,-5,6,-1}; // Example array
    int n = sizeof(A) / sizeof(A[0]);

    int maxSum = MaxSubArraySum(A, n);
    cout << "Maximum Subarray Sum: " << maxSum << endl;

    return 0;
}
