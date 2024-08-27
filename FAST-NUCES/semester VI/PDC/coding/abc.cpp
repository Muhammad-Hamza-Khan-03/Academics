#include <iostream>
#include <omp.h>
using namespace std;

int main() {
  int nums[20], total = 0;
  bool p;
  for (int i = 0; i < 20; i++)
    nums[i] = i + 1;
#pragma omp parallel for num_threads(4) schedule(static, 3) private(p)
  for (int j = 0; j < 20; j++) {
    int n = nums[j];
    p = true;
    for (int k = 2; k <= (n / 2); k++) {

      if (n % k == 0) {
        p = false;
        break;
      }
    }
    if (p) {
#pragma omp critical
      cout << "At " << omp_get_thread_num() << ": n=" << n << endl;
#pragma omp critical
      total++;
    }
  }
  cout << "\nTotal = " << total << endl;
  return 0;
}