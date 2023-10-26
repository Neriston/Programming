#include <iostream>
#include <vector>
#include <algorithm>

struct Points {
  int tasks, fine_time, number;
  Points() : tasks(0), fine_time(0), number(0) {
  }
  Points(const int& tasks, const int& fine_time) : tasks(tasks), fine_time(fine_time) {
  }
};

bool Comparator(const Points& first, const Points& second) {
  if (first.tasks > second.tasks) {
    return true;
  }
  if (first.tasks == second.tasks) {
    if (first.fine_time < second.fine_time) {
      return true;
    }
    if (first.fine_time == second.fine_time) {
      return first.number < second.number;
    }
    return false;
  }
  return false;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<Points> table(n);
  for (int i = 1; i < n + 1; ++i) {
    std::cin >> table[i - 1].tasks >> table[i - 1].fine_time;
    table[i - 1].number = i;
  }
  std::sort(table.begin(), table.end(), Comparator);
  for (int i = 0; i < n; ++i) {
    std::cout << table[i].number << '\n';
  }
  return 0;
}