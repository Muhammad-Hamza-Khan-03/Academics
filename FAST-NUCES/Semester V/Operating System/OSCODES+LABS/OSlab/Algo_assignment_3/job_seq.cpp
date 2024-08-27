#include <iostream>
using namespace std;

void job_sequence(int profit[], int deadline[], int n) {
  // profit is already sorted

  int i = 0, j;
  cout << i + 1;

  int arr[n];
  for (int it = 0; it < n; it++) {
    arr[it] = 0;
  }
  for (j = 0; j < n; j++) {
    if (arr[deadline[j]] == 0) {
      // insert
      cout << i + 1;
      arr[deadline[j]] = 1;

    } else {
      i++;
    }
  }
}
int main() {
  int n = 5;
  int profits[] = {20, 15, 10, 5, 1};
  int deadline[] = {2, 2, 1, 3, 3};
  job_sequence(profits, deadline, n);
  return 1;
}