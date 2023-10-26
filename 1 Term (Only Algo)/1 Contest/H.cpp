#include <iostream>
using std::string;

void Reverse(char* array, int size) {
  for (int i = 0; i < size / 2; ++i) {
    char temp = array[i];
    array[i] = array[size - 1 - i];
    array[size - 1 - i] = temp;
  }
}
int main() {
  std::string n;
  std::cin >> n;
  int length = n.size() - 1;
  auto array_1 = new char[(length + 1) / 2];
  auto array_2 = new char[length - (length + 1) / 2];
  for (int i = 0; i < length; i += 2) {
    array_1[i / 2] = n[i];
  }
  for (int i = 1; i < length; i += 2) {
    array_2[(i - 1) / 2] = n[i];
  }
  Reverse(array_2, length - (length + 1) / 2);
  for (int i = 0; i < (length + 1) / 2; ++i) {
    std::cout << array_1[i];
  }
  for (int i = 0; i < length - (length + 1) / 2; ++i) {
    std::cout << array_2[i];
  }
  delete[] array_1;
  delete[] array_2;
  return 0;
}