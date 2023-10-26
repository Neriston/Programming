#include <iostream>
#include <vector>
#include <stack>

struct Answer {
  std::vector<int> days;
  size_t size = 0;
  int64_t ans = -1;
  int l = 0;
  int r = 0;
  Answer() = default;

  explicit Answer(const std::vector<int>& days) : days(days) {
    size = days.size();
  }

  void SolveStackLeft(std::stack<std::pair<int, int>>& stack, std::vector<int>& vector) {
    for (size_t i = 0; i < size; ++i) {
      int cnt = 1;  //  just for conveniences
      while (!stack.empty() && stack.top().first > days[i]) {
        cnt += stack.top().second;
        stack.pop();
      }
      std::pair<int, int> temp_pair = {days[i], cnt};
      stack.push(temp_pair);
      vector[i] = cnt - 1;
    }
  }

  void SolveStackRight(std::stack<std::pair<int, int>>& stack, std::vector<int>& vector) {
    for (int i = static_cast<int>(size) - 1; i >= 0; --i) {
      int cnt = 1;  //  just for conveniences
      while (!stack.empty() && stack.top().first >= days[i]) {
        cnt += stack.top().second;
        stack.pop();
      }
      std::pair<int, int> temp_pair = {days[i], cnt};
      stack.push(temp_pair);
      vector[i] = cnt - 1;
    }
  }

  void MaxProductWithMin() {
    std::vector<int> left_cnt(size);   //  how many consecutive numbers on the left are greater than this
    std::vector<int> right_cnt(size);  //  the same, but on the right
    std::vector<int64_t> prefix_sum(size);
    prefix_sum[0] = days[0];
    for (size_t i = 1; i < size; ++i) {
      prefix_sum[i] = prefix_sum[i - 1] + days[i];
    }
    std::stack<std::pair<int, int>> left_stack;   // for left_cnt
    std::stack<std::pair<int, int>> right_stack;  //  for right_cnt
    SolveStackLeft(left_stack, left_cnt);
    SolveStackRight(right_stack, right_cnt);
    for (size_t i = 0; i < size; ++i) {
      int left = static_cast<int>(i) - left_cnt[i];    //  left border
      int right = static_cast<int>(i) + right_cnt[i];  //  right border
      int64_t prefix_sum_l_r = prefix_sum[right] - ((left > 0) ? prefix_sum[left - 1] : 0);
      int64_t temp_ans = prefix_sum_l_r * days[i];
      if (temp_ans > ans) {
        ans = temp_ans;
        l = left + 1;
        r = right + 1;
      }
    }
  }
};

std::istream& operator>>(std::istream& is, Answer& ans) {
  std::cin >> ans.size;
  ans.days.resize(ans.size);
  for (size_t i = 0; i < ans.size; ++i) {
    is >> ans.days[i];
  }
  return is;
}

int main() {
  Answer ans;
  std::cin >> ans;
  ans.MaxProductWithMin();
  std::cout << ans.ans << '\n' << ans.l << ' ' << ans.r;
  return 0;
}