#include <iostream>
#include <vector>
#include <utility>

#include "assignments/ev/euclidean_vector.h"

int main() {
  EuclideanVector a(3, 3.0);
  a.at(0) = 9;
  a[1] = 9;
  a[2] = 9;
  const EuclideanVector b{a};
  std::cout << a[0] << " " << b.at(0) << "\n";
  std::cout << a.at(1) << " " << b[1] << "\n";
  std::cout << a[2] << " " << b.at(2) << "\n";
  std::cout << (a == b) << "\n";
  std::cout << (a != b) << "\n";
  const EuclideanVector c = (a + b) / 3;
  std::cout << a << "\n";
  std::cout << a.GetNumDimensions() << b.GetNumDimensions() << c.GetNumDimensions() << "\n";
}
