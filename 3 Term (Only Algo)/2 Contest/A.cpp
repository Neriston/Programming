#include <iostream>
#include <string>
#include <vector>

void CalcPrefFunc(const std::string& string, std::vector<int>& pref_func) {
  for (size_t i = 1; i < string.length(); ++i) {
    int k = pref_func[i - 1];
    while (string[i] != string[k] && k > 0) {
      k = pref_func[k - 1];
    }
    if (string[i] == string[k]) {
      pref_func[i] = k + 1;
    }
  }
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vector) {
  for (const auto& i : vector) {
    os << i << ' ';
  }
  os << '\n';
  return os;
}

int main() {
  std::string string;
  std::cin >> string;
  std::vector<int> pref_func(string.length(), 0);
  CalcPrefFunc(string, pref_func);
  std::cout << pref_func;
  return 0;
}