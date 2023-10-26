#include <iostream>

void Merge(int* array, int l, int r, int mid, int64_t& ans) {
  auto new_array = new int[r - l + 1];
  int ind = 0;
  int first = l;
  int second = mid + 1;
  while (first <= mid && second <= r) {
    if (array[first] <= array[second]) {
      new_array[ind] = array[first];
      ++first;
      ++ind;
    } else {
      new_array[ind] = array[second];
      ans += mid - first + 1;
      ++second;
      ++ind;
    }
  }
  while (first <= mid) {
    new_array[ind] = array[first];
    ++first;
    ++ind;
  }
  while (second <= r) {
    new_array[ind] = array[second];
    ++second;
    ++ind;
  }
  for (int i = 0; i < r - l + 1; ++i) {
    array[l + i] = new_array[i];
  }
  delete[] new_array;
}

void MergeSort(int* array, int l, int r, int64_t& ans) {
  if (l >= r) {
    return;
  }
  int mid = (r - l) / 2 + l;
  MergeSort(array, l, mid, ans);
  MergeSort(array, mid + 1, r, ans);
  Merge(array, l, r, mid, ans);
}

int main() {
  int n;
  int64_t ans = 0;
  std::cin >> n;
  auto array = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  MergeSort(array, 0, n - 1, ans);
  std::cout << ans;
  delete[] array;
  return 0;
}