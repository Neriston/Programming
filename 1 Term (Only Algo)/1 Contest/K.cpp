#include <iostream>
#include <cstring>

int main() {
  int k;
  char s[1000001]{};
  int cnt = 0;
  freopen("input.txt", "r", stdin);
  std::cin >> k;
  while (std::cin.good()) {
    std::cin >> s[cnt];
    ++cnt;
  }
  cnt = 0;
  int ans = 0;
  int now_cnt;
  int l = strlen(s);
  while (cnt < l - k) {
    if (s[cnt] == s[cnt + k]) {
      ++now_cnt;
      ans += now_cnt;
      ++cnt;
    } else {
      now_cnt = 0;
      ++cnt;
    }
  }
  std::cout << ans;
  return 0;
}