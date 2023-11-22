#include <iostream>
#include <string>
#include <vector>

void CalcPrefFuncForPattern(const std::string& pattern, std::vector<int>& pref_func) {
  for (size_t i = 1; i < pattern.length(); ++i) {
    int k = pref_func[i - 1];
    while (pattern[i] != pattern[k] && k > 0) {
      k = pref_func[k - 1];
    }
    if (pattern[i] == pattern[k]) {
      pref_func[i] = k + 1;
    }
  }
}

void KMP(const std::string& string, const std::string& pattern, std::vector<int>& pref_func) {
  CalcPrefFuncForPattern(pattern, pref_func);
  int last_pref_func = 0;
  for (size_t i = 0; i < string.length(); ++i) {
    int k = last_pref_func;
    while (k > 0 && (k == static_cast<int>(pattern.size()) || string[i] != pattern[k])) {
      k = pref_func[k - 1];
    }
    if (string[i] == pattern[k]) {
      ++k;
    }
    last_pref_func = k;
    if (k == static_cast<int>(pattern.length())) {
      std::cout << i - static_cast<int>(pattern.length()) + 1 << '\n';
    }
  }
}

int main() {
  std::string string;
  std::string pattern;
  std::cin >> string >> pattern;
  std::vector<int> pref_func(pattern.length(), 0);
  KMP(string, pattern, pref_func);
  return 0;
}