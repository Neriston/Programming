#include <iostream>
#include <string>
#include <vector>

const std::vector<int>& CalcZFunc(const std::string& string, std::vector<int>& z_func) {
  z_func[0] = static_cast<int>(string.length());
  int left = 0;
  int right = 0;
  for (int i = 1; i < static_cast<int>(string.length()); ++i) {
    if (i < right) {
      z_func[i] = z_func[i - left] > right - i ? right - i : z_func[i - left];
    }
    while (i + z_func[i] < static_cast<int>(string.length()) && string[z_func[i]] == string[z_func[i] + i]) {
      ++z_func[i];
    }
    (i + z_func[i] > right) ? (right = i + z_func[i], left = i) : 0;
  }
  return z_func;
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
  std::vector<int> z_func(string.length(), 0);
  std::cout << CalcZFunc(string, z_func);
  return 0;
}