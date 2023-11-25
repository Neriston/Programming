#include <iostream>
#include <string>
#include <vector>

int CalcPrefFunc(const std::string& pattern, const std::string& string) {
  std::vector<int> pref_func(pattern.length(), 0);
  int cast_len_string = static_cast<int>(string.length());
  int cast_len_pattern = static_cast<int>(pattern.length());
  for (size_t i = 1; i < pattern.length(); ++i) {
    int k = pref_func[i - 1];
    while (k > 0 && pattern[i] != pattern[k]) {
      k = pref_func[k - 1];
    }
    if (pattern[i] == pattern[k]) {
      pref_func[i] = k + 1;
    }
  }
  int last_pref_func = 0;
  int k = 0;
  int diff = cast_len_string - cast_len_pattern;
  int start = diff > 0 ? diff : 0;
  for (int i = start; i < cast_len_string; ++i) {
    k = last_pref_func;
    while (k > 0 && (k == static_cast<int>(pattern.size()) || string[i] != pattern[k])) {
      k = pref_func[k - 1];
    }
    if (string[i] == pattern[k]) {
      ++k;
    }
    last_pref_func = k;
  }
  return last_pref_func;
}

std::string SmartConcatenation(const int& n) {
  std::string conc_str;
  std::cin >> conc_str;
  if (n == 1) {
    return conc_str;
  }
  std::string now_str;
  for (int i = 0; i < n - 1; ++i) {
    std::cin >> now_str;
    const int size_of_the_common_suf_and_pref = CalcPrefFunc(now_str, conc_str);
    int cast_len = static_cast<int>(now_str.size());
    for (int i = size_of_the_common_suf_and_pref; i < cast_len; ++i) {
      conc_str += now_str[i];
    }
  }
  return conc_str;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::cout << SmartConcatenation(n) << '\n';
  return 0;
}