#include <iostream>

void Swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void Delete(int* arraynow, int* arraynew, int size) {
  int cnt = 1;
  arraynew[0] = arraynow[0];
  for (int i = 1; i < size; ++i) {
    if (arraynow[i] != arraynow[i - 1]) {
      arraynew[cnt] = arraynow[i];
      ++cnt;
    }
  }
}
void QuickSort(int* array, int size) {
  int i = 0;
  int j = size - 1;
  int mid = array[size / 2];
  while (i <= j) {
    while (array[i] < mid) {
      i++;
    }
    while (array[j] > mid) {
      j--;
    }
    if (i <= j) {
      Swap(array[i], array[j]);
      i++;
      j--;
    }
  }
  if (j > 0) {
    QuickSort(array, j + 1);
  }
  if (i < size) {
    QuickSort(&array[i], size - i);
  }
}
int main() {
  int n1;
  int n2;
  std::cin >> n1;
  auto array1 = new int[n1];
  for (int i = 0; i < n1; ++i) {
    std::cin >> array1[i];
  }
  std::cin >> n2;
  auto array2 = new int[n2];
  for (int i = 0; i < n2; ++i) {
    std::cin >> array2[i];
  }
  QuickSort(array1, n1);
  QuickSort(array2, n2);
  int max = n1;
  if (n2 > n1) {
    max = n2;
  }
  auto newarray1 = new int[max]{};
  auto newarray2 = new int[max]{};
  Delete(array1, newarray1, n1);
  Delete(array2, newarray2, n2);
  bool flag = true;
  for (int i = 0; i < max; ++i) {
    if (newarray1[i] != newarray2[i]) {
      flag = false;
    }
  }
  if (flag) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  delete[] array1;
  delete[] array2;
  delete[] newarray1;
  delete[] newarray2;
}