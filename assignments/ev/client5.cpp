#include <iostream>
#include <vector>
#include <utility>

#include "assignments/ev/euclidean_vector.h"

int main() {
  EuclideanVector a(3, 3.0);
  std::cout << a << "\n";
  a *= 3;
  std::cout << a << "\n";
  a /= 3;
  std::cout << a << "\n";
}
