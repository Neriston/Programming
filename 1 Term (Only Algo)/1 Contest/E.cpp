#include <iostream>
#include <cmath>

void Swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
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

int Count(const int* bring_pow, int ind_max) {
  int count = 0;
  for (int i = 0; i < ind_max; ++i) {
    count += bring_pow[i];
  }
  return count;
}

int64_t NowSum(const int* array, const int* bring_pow, int ind_max) {
  int64_t sum = 0;
  for (int i = 0; i < ind_max; ++i) {
    sum += array[i] * bring_pow[i];
  }
  return sum;
}

void Func(int* array, int* bring_pow, int ind_max, int sum_need) {
  auto ans = new int[ind_max]{};
  int min_bring = 2 * ind_max + 1;
  for (int64_t i = 0; i < pow(3, ind_max); ++i) {
    int p = 0;
    ++bring_pow[p];
    while (bring_pow[p] == 3) {
      bring_pow[p] = 0;
      if (p == ind_max - 1) {
        break;
      }
      ++bring_pow[p + 1];
      ++p;
    }
    if (NowSum(array, bring_pow, ind_max) == sum_need) {
      int tmp = Count(bring_pow, ind_max);
      if (min_bring > tmp) {
        min_bring = tmp;
        for (int j = 0; j < ind_max; ++j) {
          ans[j] = bring_pow[j];
        }
      }
    }
  }
  if (min_bring == 2 * ind_max + 1) {
    std::cout << 0;
  } else {
    std::cout << min_bring << "\n";
    for (int i = ind_max - 1; i >= 0; --i) {
      if (ans[i] != 0) {
        for (int x = 0; x < ans[i]; ++x) {
          std::cout << array[i] << " ";
        }
      }
    }
  }
  delete[] ans;
}

int main() {
  int sum_need;
  int sum_max = 0;
  int m;
  std::cin >> sum_need >> m;
  auto* array = new int[m]{};
  for (int i = 0; i < m; ++i) {
    std::cin >> array[i];
    sum_max += 2 * array[i];
  }
  if (sum_max < sum_need) {
    std::cout << -1;
    delete[] array;
    return 0;
  }
  int ind_max = m;
  QuickSort(array, m);
  for (int i = 0; i < m; ++i) {
    if (array[i] > sum_need) {
      ind_max = i;
      break;
    }
  }
  auto* bring_pow = new int[ind_max]{};
  Func(array, bring_pow, ind_max, sum_need);

  delete[] array;
  delete[] bring_pow;
  return 0;
}