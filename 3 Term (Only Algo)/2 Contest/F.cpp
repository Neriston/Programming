#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int CalcPrefFuncReversed(const std::string& string, const int& right_border) {
  int max_pref_func = 0;
  std::string temp_string(right_border + 1, ' ');
  for (int i = 0; i < right_border + 1; ++i) {
    temp_string[i] = string[i];
  }
  std::vector<int> pref_func(temp_string.length(), 0);
  std::reverse(temp_string.begin(), temp_string.end());
  for (size_t i = 1; i < temp_string.length(); ++i) {
    int k = pref_func[i - 1];
    while (temp_string[i] != temp_string[k] && k > 0) {
      k = pref_func[k - 1];
    }
    if (temp_string[i] == temp_string[k]) {
      pref_func[i] = k + 1;
      max_pref_func = max_pref_func > pref_func[i] ? max_pref_func : pref_func[i];
    }
  }
  return static_cast<int>(temp_string.length()) - max_pref_func;
}

int NumOfDiffSubstr(std::string& string) {
  int num = 1;
  for (int i = 1; i < static_cast<int>(string.length()); ++i) {
    num += CalcPrefFuncReversed(string, i);
  }
  return num;
}

int main() {
  std::string string;
  std::cin >> string;
  std::cout << NumOfDiffSubstr(string);
  return 0;
}