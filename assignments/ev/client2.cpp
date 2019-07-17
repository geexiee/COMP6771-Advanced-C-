#include <iostream>
#include <vector>
#include <utility>

#include "assignments/ev/euclidean_vector.h"

int main() {
  EuclideanVector a(2);
  EuclideanVector b(3);

  try {
    std::cout << a + b << "\n";
  } catch (const std::exception& e) {
    std::cout << e.what() << "\n";
  }
}
