#include "HashOneD.h"
#include "HashTwoD.h"
#include "bst.cpp"
#include <iostream>

int main() {
  std::srand(1);
  int values[100];
  int checks[3] = {0, 0, 0};
  HashOneD h1d;
  HashTwoD h2d;
  BST<int> bst;
  for (int i = 0; i < 100; i++) {
    values[i] = std::rand();
  }
  for (int i = 0; i < 50; i++) {
    checks[0] += h1d.Insert(values[i]);
    checks[1] += h2d.Insert(values[i]);
    checks[2] += bst.Insert(new int(values[i]));
  }
  std::cout << "Checks for insert\nHashOneD: " << checks[0]
            << "\nHashTwoD: " << checks[1] << "\nBST: " << checks[2]
            << std::endl;
  checks[0] = 0;
  checks[1] = 0;
  checks[2] = 0;
  for (int i = 0; i < 50; i++) {
    if (i % 7 != 0)
      continue;
    checks[0] += h1d.Remove(values[i]);
    checks[1] += h2d.Remove(values[i]);
    bst.RemoveChecked(new int(values[i]), &checks[2]);
  }
  std::cout << "Checks for remove\nHashOneD: " << checks[0]
            << "\nHashTwoD: " << checks[1] << "\nBST: " << checks[2]
            << std::endl;
  checks[0] = 0;
  checks[1] = 0;
  checks[2] = 0;
  for (int i = 50; i < 100; i++) {
    checks[0] += h1d.Insert(values[i]);
    checks[1] += h2d.Insert(values[i]);
    checks[2] += bst.Insert(new int(values[i]));
  }
  std::cout << "Checks for insert\nHashOneD: " << checks[0]
            << "\nHashTwoD: " << checks[1] << "\nBST: " << checks[2]
            << std::endl;
  checks[0] = 0;
  checks[1] = 0;
  checks[2] = 0;
  for (int i = 0; i < 100; i++) {
    if (i % 9 != 0 && (i < 50 && i % 7 != 0))
      continue;
    checks[0] += h1d.Find(values[i]);
    checks[1] += h2d.Find(values[i]);
    bst.FindChecked(new int(values[i]), &checks[2]);
  }
  std::cout << "Checks for find\nHashOneD: " << checks[0]
            << "\nHashTwoD: " << checks[1] << "\nBST: " << checks[2]
            << std::endl;

  return 0;
}
