#include <iostream>
#include <queue>
#include <iomanip>

int main() {
  int n;
  std::cin >> n;
  std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
  for (int i = 0; i < n; ++i) {
    int num;
    std::cin >> num;
    pq.push(num);
  }
  long double ans = 0;
  while (pq.size() > 1) {
    int res = 0;
    res += pq.top();
    pq.pop();
    res += pq.top();
    pq.pop();
    pq.push(res);
    ans += res;
  }
  std::cout << ans * 0.05;
  return 0;
}