#include <iostream>
#include <string>
#include <vector>

void CalcZFunc(const std::string& string, std::vector<int>& z_func) {
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
}

void InterestingOrNot(const std::string& mystery, const std::string& donkey) {
  std::string mystery_donkey = mystery + "#" + donkey;
  std::vector<int> z_func(mystery_donkey.length(), 0);
  CalcZFunc(mystery_donkey, z_func);
  int cast_len = static_cast<int>(mystery_donkey.length());
  int cast_len_mystery = static_cast<int>(mystery.length());
  int end = cast_len - 1;
  int cnt = 0;
  std::vector<std::string> pref_str;
  while (end > cast_len_mystery) {
    int copy_last_end = end;
    while (z_func[end] == 0 || z_func[end] < copy_last_end - end + 1) {
      --end;
      if (end == cast_len_mystery) {
        break;
      }
    }
    if (end != cast_len_mystery) {
      cnt += copy_last_end - end + 1;
      std::string temp_str(copy_last_end - end + 1, ' ');
      for (int i = end; i <= copy_last_end; ++i) {
        temp_str[i - end] = mystery_donkey[i];
      }
      pref_str.emplace_back(temp_str);
      --end;
    }
  }
  if (cnt == static_cast<int>(donkey.length())) {
    std::cout << "No\n";
    auto it = std::cend(pref_str);
    while (it != std::cbegin(pref_str)) {
      std::cout << *(--it) << ' ';
    }
  } else {
    std::cout << "Yes\n";
  }
}

int main() {
  std::string mystery;
  std::string donkey;
  std::cin >> mystery >> donkey;
  InterestingOrNot(mystery, donkey);
  return 0;
}