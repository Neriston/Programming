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

auto KMP(const std::string& string, const std::string& pattern, std::vector<int>& pref_func) {
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
      return std::pair<bool, int>(true, i + 1);
    }
  }
  return std::pair<bool, int>(false, -1);
}

int main() {
  int n = 0;
  std::string string;
  std::string pattern;
  std::cin >> n >> string >> pattern;
  std::vector<int> pref_func(pattern.length(), 0);
  std::string str0 = "0" + string + "0" + string;
  std::string str1 = "1" + string + "1" + string;
  CalcPrefFuncForPattern(pattern, pref_func);
  auto zero_add = KMP(str0, pattern, pref_func);
  auto one_add = KMP(str1, pattern, pref_func);
  if (zero_add.first && one_add.first) {
    std::cout << "Random\n";
  } else if (zero_add.first) {
    if (str0[zero_add.second] == '1') {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  } else {
    if (str1[one_add.second] == '1') {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  }
  return 0;
}