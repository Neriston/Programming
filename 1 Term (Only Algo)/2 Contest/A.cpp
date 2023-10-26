#include <iostream>
#include <algorithm>
#include <cstring>

struct S {
  char surname[40]{};
  char name[40]{};
  int inf_points;
  int math_points;
  int rus_points;
  int sum;
};

bool Comparator(S first, S second) {
  return !(first.sum <= second.sum);
}

int main() {
  int n;
  std::cin >> n;
  auto ans_array = new S[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> ans_array[i].surname >> ans_array[i].name >> ans_array[i].inf_points >> ans_array[i].math_points >>
        ans_array[i].rus_points;
    ans_array[i].sum = ans_array[i].inf_points + ans_array[i].math_points + ans_array[i].rus_points;
  }
  std::stable_sort(ans_array, ans_array + n, Comparator);
  for (int i = 0; i < n; ++i) {
    std::cout << ans_array[i].surname << ' ' << ans_array[i].name << '\n';
  }
  delete[] ans_array;
}