#include <iostream>
#include <vector>
#include <utility>

#include "assignments/ev/euclidean_vector.h"

int main() {
  std::vector<double> vec{1,2,3};
  EuclideanVector a(vec.begin(), vec.end());
  std::cout << a << "\n";
  auto b = std::move(a);
  std::cout << a << "\n";
  std::cout << b << "\n";
}
