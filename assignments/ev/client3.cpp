#include <iostream>
#include <vector>
#include <utility>

#include "assignments/ev/euclidean_vector.h"

int main() {
  EuclideanVector a(2);

  try {
    std::cout << a.at(0) << "\n";
    std::cout << a.at(1) << "\n";
    std::cout << a.at(2) << "\n";
  } catch (const std::exception& e) {
    std::cout << e.what() << "\n";
  }
}
