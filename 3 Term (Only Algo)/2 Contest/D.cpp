#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

const std::string StringFromPrefFunc(const std::vector<int>& pref_func_val) {
  std::string string(pref_func_val.size(), ' ');
  string[0] = 'a';  //  if len == 0, [] doesn't do anything
  for (size_t i = 1; i < pref_func_val.size(); ++i) {
    if (pref_func_val[i] > 0) {
      string[i] = string[pref_func_val[i] - 1];
    } else {
      std::unordered_set<char> banned;
      int k = pref_func_val[i - 1];
      while (k > 0) {
        banned.emplace(string[k]);
        k = pref_func_val[k - 1];
      }
      for (char symbol = 'b'; symbol <= 'z'; ++symbol) {  // start with 'b' because 'a' have already banned
        if (banned.find(symbol) == banned.end()) {
          string[i] = symbol;
          break;
        }
      }
    }
  }
  return string;
}

std::istream& operator>>(std::istream& is, std::vector<int>& vector) {
  for (size_t i = 0; i < vector.size(); ++i) {
    is >> vector[i];
  }
  return is;
}

const std::vector<int>& ConvertZFuncToPrefFunc(std::vector<int>& z_func_val, std::vector<int>& pref_func_val) {
  z_func_val[0] = 0;
  for (int i = 0; i < static_cast<int>(z_func_val.size()); ++i) {
    for (int delta = z_func_val[i] - 1; delta >= 0; --delta) {
      if (pref_func_val[i + delta] > 0) {
        break;
      }
      pref_func_val[i + delta] = delta + 1;
    }
  }
  return pref_func_val;
}

int main() {
  int n = 0;
  std::cin >> n;
  if (n == 0) {
    return 0;
  }
  std::vector<int> pref_func_val(n, 0);
  std::vector<int> z_func_val(n, 0);
  std::cin >> z_func_val;
  std::cout << StringFromPrefFunc(ConvertZFuncToPrefFunc(z_func_val, pref_func_val));
  return 0;
}