#include "assignments/ev/euclidean_vector.h"

#include <algorithm>
#include <cassert>
#include <utility>

// MEMBER OVERLOADS

// copy assignment
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& original) noexcept {
  EuclideanVector copy{original};
  std::swap(copy, *this);
  return *this;
}

// move assignment (as given in specs)
EuclideanVector& EuclideanVector::operator=(EuclideanVector&& original) noexcept {
  magnitudes_ = std::move(original.magnitudes_);
  dimensions_ = original.GetNumDimensions();
  original.dimensions_ = 0;
  return *this;
}

// [] operator for reading
double EuclideanVector::operator[](const int index) const noexcept {
  assert(index < this->dimensions_ && index >= 0);
  return this->magnitudes_[index];
}

// [] operator for writing
double& EuclideanVector::operator[](const int index) noexcept {
  assert(index < this->dimensions_ && index >= 0);
  return this->magnitudes_[index];
}

// += operator
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& e) {
  if (e.dimensions_ != this->dimensions_)
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  for (auto i = 0; i < e.GetNumDimensions(); ++i) {
    magnitudes_[i] = magnitudes_[i] + e[i];
  }
  return *this;
}

// -= operator
EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& e) {
  if (e.dimensions_ != this->dimensions_)
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  for (auto i = 0; i < e.GetNumDimensions(); ++i) {
    magnitudes_[i] = magnitudes_[i] - e[i];
  }
  return *this;
}

// *= operator
EuclideanVector& EuclideanVector::operator*=(const int& n) noexcept {
  for (auto i = 0; i < dimensions_; ++i) {
    magnitudes_[i] = magnitudes_[i] * n;
  }
  return *this;
}

// /= operator
EuclideanVector& EuclideanVector::operator/=(const int& n) {
  if (n == 0)
    throw EuclideanVectorError("Invalid vector division by 0");
  for (auto i = 0; i < dimensions_; ++i) {
    magnitudes_[i] = magnitudes_[i] / n;
  }
  return *this;
}

// METHOD DEFINITIONS

// Returns a Euclidean vector equal to the unit vector of the euclidean vector it was called from
EuclideanVector EuclideanVector::CreateUnitVector() const {
  // Exception handling
  if (this->GetNumDimensions() == 0)
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a unit vector");
  if (this->GetEuclideanNorm() == 0)
    throw EuclideanVectorError(
        "EuclideanVector with euclidean normal of 0 does not have a unit vector");

  // getting the euclidean norm of the EV so we can calculate the values of the unit vector
  double norm = this->GetEuclideanNorm();
  // constructing an EV of the same size and filling it in with the correct magnitudes (the
  // corresponding magnitudes divided by the norm)
  EuclideanVector temp(dimensions_);
  for (auto i = 0; i < dimensions_; ++i) {
    temp[i] = this->magnitudes_[i] / norm;
  }
  return temp;
}

// calculates and returns the euclidean norm of an euclidean vector as a double
double EuclideanVector::GetEuclideanNorm() const {
  if (this->GetNumDimensions() == 0)
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a norm");
  double sum = 0;
  for (auto i = 0; i < dimensions_; ++i) {
    sum = sum + pow(magnitudes_[i], 2);
  }
  return std::sqrt(sum);
}
