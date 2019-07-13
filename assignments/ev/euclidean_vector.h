#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <cmath>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <string>
#include <strstream>
#include <utility>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // CONSTRUCTORS

  // default constructor
  explicit EuclideanVector(int dimensions = 1) : EuclideanVector{dimensions, 0} {}

  // regular constructor
  EuclideanVector(int dimensions, double magnitudes)
    : dimensions_{dimensions}, magnitudes_{std::make_unique<double[]>(dimensions)} {
    for (auto j = 0; j < dimensions; ++j) {
      magnitudes_[j] = magnitudes;
    }
  }

  // iterator constructor
  EuclideanVector(std::vector<double>::const_iterator begin,
                  std::vector<double>::const_iterator end) {
    int n_dimensions = 0;
    // counting the number of dimensions in the vector
    for (auto iter = begin; iter != end; ++iter) {
      n_dimensions++;
    }
    dimensions_ = n_dimensions;
    magnitudes_ = std::make_unique<double[]>(n_dimensions);
    auto index = 0;
    // copying the value of each element in the vector into the newly constructed EV
    for (auto iter = begin; iter != end; ++iter) {
      magnitudes_[index] = *iter;
      ++index;
    }
  }

  // copy constructor
  EuclideanVector(const EuclideanVector& original) : dimensions_(original.dimensions_) {
    magnitudes_ = std::make_unique<double[]>(original.GetNumDimensions());
    for (int i = 0; i < original.GetNumDimensions(); ++i) {
      magnitudes_[i] = original[i];
    }
  }

  // move constructor (as given in specs)
  EuclideanVector(EuclideanVector&& o) noexcept
    : dimensions_{o.dimensions_}, magnitudes_{std::move(o.magnitudes_)} {
    o.dimensions_ = 0;
  }

  // default destructor
  ~EuclideanVector() noexcept = default;

  // MEMBER FUNCTIONS

  // copy operator (used to copy one EV to another)
  EuclideanVector& operator=(const EuclideanVector& original) noexcept;
  // move operator (used to move everything from one EV to another, so the original becomes empty)
  EuclideanVector& operator=(EuclideanVector&& original) noexcept;
  // += operator
  EuclideanVector& operator+=(const EuclideanVector& e);
  // -= operator
  EuclideanVector& operator-=(const EuclideanVector& e);
  // *= operator
  EuclideanVector& operator*=(const int& n) noexcept;
  // /= operator
  EuclideanVector& operator/=(const int& n);
  // [] operator for writing/setting values
  double& operator[](int index) noexcept;
  // [] operator for reading values
  double operator[](int index) const noexcept;

  // Vector type conversion
  explicit operator std::vector<double>() const noexcept {
    std::vector<double> temp;
    for (auto i = 0; i < this->dimensions_; ++i) {
      temp.emplace_back(this->magnitudes_[i]);
    }
    return temp;
  }

  // List type conversion
  explicit operator std::list<double>() const noexcept {
    std::list<double> temp;
    for (auto i = 0; i < this->dimensions_; ++i) {
      temp.emplace_back(this->magnitudes_[i]);
    }
    return temp;
  }

  // FRIENDS

  // == operator to check if two EVs are identical. Returns true if they are, false otherwise
  friend bool operator==(const EuclideanVector& v1, const EuclideanVector& v2) noexcept {
    if (v1.dimensions_ == v2.dimensions_) {
      for (auto i = 0; i < v1.dimensions_; ++i) {
        if (v1[i] != v2[i])
          return false;
      }
      return true;
    }
    return false;
  }

  // == operator to check if two EVs are different. returns true if they are, false otherwise
  friend bool operator!=(const EuclideanVector& v1, const EuclideanVector& v2) noexcept {
    if (v1 == v2)
      return false;
    return true;
  }

  // + operator to add two EVs. Throws exception if the two EVs have different dimensions
  friend EuclideanVector operator+(const EuclideanVector& v1, const EuclideanVector& v2) {
    if (v1.GetNumDimensions() != v2.GetNumDimensions())
      throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
    EuclideanVector sum = EuclideanVector{v1.dimensions_};
    for (auto i = 0; i < v1.dimensions_; ++i) {
      sum[i] = v1[i] + v2[i];
    }
    return sum;
  }

  // - operator to subtract 2 EVs. Throws exception if the two EVs have different dimensions
  friend EuclideanVector operator-(const EuclideanVector& v1, const EuclideanVector& v2) {
    if (v1.GetNumDimensions() != v2.GetNumDimensions())
      throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
    EuclideanVector v = EuclideanVector{v1.dimensions_};
    for (auto i = 0; i < v1.dimensions_; ++i) {
      v[i] = v1[i] - v2[i];
    }
    return v;
  }

  // * operator to find the dot product of 2 EVs. Throws exception if the two EVs have different
  // dimensions
  friend double operator*(const EuclideanVector& v1, const EuclideanVector& v2) {
    if (v1.GetNumDimensions() != v2.GetNumDimensions())
      throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
    double dot_product = 0;
    for (auto i = 0; i < v1.dimensions_; ++i) {
      dot_product = dot_product + (v2[i] * v1[i]);
    }
    return dot_product;
  }

  // * operator to multiply an EV by a scalar, where the scalar comes after the *
  friend EuclideanVector operator*(const EuclideanVector& v1, const int& n) noexcept {
    EuclideanVector v = EuclideanVector{v1.dimensions_};
    for (auto i = 0; i < v1.dimensions_; ++i) {
      v[i] = (v1[i] * n);
    }
    return v;
  }

  // * operator to multiply an EV by a scalar, where the scalar comes before the *
  friend EuclideanVector operator*(const int& n, const EuclideanVector& v1) noexcept {
    EuclideanVector v = EuclideanVector{v1.dimensions_};
    for (auto i = 0; i < v1.dimensions_; ++i) {
      v[i] = (v1[i] * n);
    }
    return v;
  }

  // division operator to divide each dimension of an EV by a scalar. Throws exception if trying to
  // divide by 0
  friend EuclideanVector operator/(const EuclideanVector& v1, const int& n) {
    if (n == 0)
      throw EuclideanVectorError("Invalid vector division by 0");
    EuclideanVector v = EuclideanVector{v1.dimensions_};
    for (auto i = 0; i < v1.dimensions_; ++i) {
      v[i] = (v1[i] / n);
    }
    return v;
  }

  // output stream operator to print out the contents of an EV in the form [1,2,3]
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) noexcept {
    os << "[";
    for (auto i = 0; i < v.dimensions_; ++i) {
      os << v[i];
      if (i != (v.dimensions_ - 1))
        os << " ";
    }
    os << "]";
    return os;
  }

  // METHODS

  // at method to get the value at a certain index in an EV. Throws exception if the index is out of
  // bounds
  double at(const int& n) const {
    if (n < 0 || n >= dimensions_)
      throw EuclideanVectorError("Index X is not valid for this EuclideanVector object");
    return magnitudes_[n];
  }

  // at method to set the value at a certain index in an EV. Throws exception if the index is out of
  // bounds
  double& at(const int& n) {
    if (n < 0 || n >= dimensions_)
      throw EuclideanVectorError("Index X is not valid for this EuclideanVector object");
    return magnitudes_[n];
  }

  // method to get the number of dimensions in an EV
  int GetNumDimensions() const noexcept { return dimensions_; }

  // method to get the Euclidean Norm of an EV. Throws exception if the number of dimensions in the
  // EV is 0
  double GetEuclideanNorm() const;

  // method to create a unit vector from an EV. Throws exception if the EV has no dimensions or has
  // a euclidean normal of 0
  EuclideanVector CreateUnitVector() const;

 private:
  int dimensions_;  // stores number of dimensions in the EV
  std::unique_ptr<double[]> magnitudes_;
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
