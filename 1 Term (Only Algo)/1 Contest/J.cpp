#include <iostream>
#include <cstring>

void Sw(char& a, char& b) {
  int temp = a;
  a = b;
  b = temp;
}

void DeleteElem(char* new_n, int new_l, bool& flag, int ind) {
  if (!flag) {
    bool flag_1 = true;
    for (int i = ind; i > 0; --i) {
      Sw(new_n[i], new_n[i - 1]);
    }
    for (int i = 1; i <= new_l / 2; ++i) {
      if (new_n[i] != new_n[new_l - i]) {
        flag_1 = false;
        break;
      }
    }
    if (flag_1) {
      flag = true;
      return;
    }
  }
}

void Swap(char* new_n, int new_l, bool& flag, int ind1, int ind2) {
  if (!flag) {
    bool flag_1 = true;
    char temp = new_n[ind1];
    new_n[ind1] = new_n[ind2];
    for (int i = 0; i < new_l / 2; ++i) {
      if (new_n[i] != new_n[new_l - i - 1]) {
        flag_1 = false;
        break;
      }
    }
    if (flag_1) {
      flag = true;
    } else {
      new_n[ind1] = temp;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  auto n = new char[100001]{};
  int cnt = 0;
  freopen("input.txt", "r", stdin);
  while (std::cin.good()) {
    std::cin >> n[cnt];
    ++cnt;
  }
  auto new_n = new char[100001]{};
  auto new_n1 = new char[100001]{};
  int l = strlen(n);
  int new_cnt = 0;
  for (int i = 0; i < l; ++i) {
    if (n[i] >= 97 && n[i] <= 122) {
      n[i] -= 32;
      new_n[new_cnt] = n[i];
      ++new_cnt;
    } else if (n[i] >= 65 && n[i] <= 90) {
      new_n[new_cnt] = n[i];
      ++new_cnt;
    }
  }
  bool flag = true;
  int new_l = strlen(new_n);
  for (int i = 0; i < new_l; ++i) {
    new_n1[i] = new_n[i];
  }
  int ind1 = 0;
  int ind2 = 0;
  for (int i = 0; i < new_l / 2; ++i) {
    if (new_n[i] != new_n[new_l - 1 - i]) {
      flag = false;
      ind1 = i;
      ind2 = new_l - 1 - i;
      break;
    }
  }
  if (flag) {
    std::cout << "YES\n";
    for (int i = 0; i < new_l; ++i) {
      std::cout << new_n[i];
    }
    delete[] n;
    delete[] new_n;
    delete[] new_n1;
    return 0;
  }
  Swap(new_n, new_l, flag, ind1, ind2);
  if (flag) {
    std::cout << "YES\n" << new_n;
    delete[] n;
    delete[] new_n;
    delete[] new_n1;
    return 0;
  }
  DeleteElem(new_n, new_l, flag, ind1);
  if (flag) {
    std::cout << "YES\n";
    for (int i = 1; i < new_l; ++i) {
      std::cout << new_n[i];
    }
    delete[] n;
    delete[] new_n;
    delete[] new_n1;
    return 0;
  }
  DeleteElem(new_n1, new_l, flag, ind2);
  if (flag) {
    std::cout << "YES\n";
    for (int i = 1; i < new_l; ++i) {
      std::cout << new_n1[i];
    }
    delete[] n;
    delete[] new_n;
    delete[] new_n1;
    return 0;
  }
  std::cout << "NO";
  delete[] n;
  delete[] new_n;
  delete[] new_n1;
}