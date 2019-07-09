#include "assignments/ev/euclidean_vector.h"

#include <cassert>
#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm

// MEMBER OVERLOADS ################################
// copy assignment
// testing github again
EuclideanVector EuclideanVector::operator=(const EuclideanVector& original) {
        EuclideanVector temp = EuclideanVector(original.dimensions_);
        for (auto i = 0; i < original.dimensions_; ++i) {
            temp.magnitudes_[i] = original.magnitudes_[i];
        }
        return temp;
}

// move assignment
EuclideanVector& EuclideanVector::operator=(EuclideanVector&& original) noexcept {
    magnitudes_ = std::move(original.magnitudes_);
    dimensions_ = original.dimensions_;
    original.dimensions_ = 0;
    return *this;
}

// [] operator for reading
double EuclideanVector::operator[](const int index) const {
    assert(index < this->dimensions_ && index >= 0);
    return this->magnitudes_[index];
}

// [] operator for writing
double& EuclideanVector::operator[](const int index) {
    assert(index < this->dimensions_ && index >= 0);
    return this->magnitudes_[index];
}

// += operator
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& e) {
  //  std::cout << "+= operator called" << std::endl;
    if (e.dimensions_ != this->dimensions_) {
        throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
    }
    for (auto i = 0; i < e.dimensions_; ++i) {
        magnitudes_[i] = magnitudes_[i] + e.magnitudes_[i];
    }
    return *this;
}

// -= operator
EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& e) {
//    std::cout << "-= operator called" << std::endl;
    if (e.dimensions_ != this->dimensions_) {
        throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
    }
    for (auto i = 0; i < e.dimensions_; ++i) {
        magnitudes_[i] = magnitudes_[i] - e.magnitudes_[i];
    }
    return *this;
}

// *= operator
EuclideanVector& EuclideanVector::operator*=(const int& n) {
    for (auto i = 0; i < dimensions_; ++i) {
        magnitudes_[i] = magnitudes_[i] * n;
    }
    return *this;
}

// /= operator
EuclideanVector& EuclideanVector::operator/=(const int& n){
 //   std::cout << "/= operator called" << std::endl;
    if (n == 0) {
        throw EuclideanVectorError("Invalid vector division by 0");
    }
    for (auto i = 0; i < dimensions_; ++i) {
        magnitudes_[i] = magnitudes_[i] / n;
    }
    return *this;
}


// FRIEND OVERLOADS #######################################
// == operator
bool operator==(const EuclideanVector& v1, const EuclideanVector& v2){
    if (v1.dimensions_ == v2.dimensions_) {
        for (auto i = 0; i < v1.dimensions_; ++i) {
            if (v1.magnitudes_[i] != v2.magnitudes_[i]) return false;
        }
        return true;
    }
    return false;
}

// != operator
bool operator!=(const EuclideanVector& v1, const EuclideanVector& v2){
    if (v1.dimensions_ == v2.dimensions_) {
        for (auto i = 0; i < v1.dimensions_; ++i) {
            if (v1.magnitudes_[i] != v2.magnitudes_[i]) return true;
        }
        return false;
    }
    return true;
}

// + operator,  STILL NEED TO IMPLEMENT ERROR HANDLING FOR WHEN DIMENSION DIFF
EuclideanVector operator+(const EuclideanVector& v1, const EuclideanVector& v2) {
    EuclideanVector compilerpleaser = EuclideanVector{v1.dimensions_}; // just to make compiler happy for now
    if (v1.dimensions_ == v2.dimensions_) {
        EuclideanVector sum = EuclideanVector{v1.dimensions_};
        for (auto i = 0; i < v1.dimensions_; ++i) {
            sum.magnitudes_[i] = v1.magnitudes_[i] + v2.magnitudes_[i];
        }
        return sum;
    }
    return compilerpleaser;
}

// - operator
EuclideanVector operator-(const EuclideanVector& v1, const EuclideanVector& v2){
    EuclideanVector compilerpleaser = EuclideanVector{v1.dimensions_}; // just to make compiler happy for now
    if (v1.dimensions_ == v2.dimensions_) {
        EuclideanVector v = EuclideanVector{v1.dimensions_};
        for (auto i = 0; i < v1.dimensions_; ++i) {
            v.magnitudes_[i] = v1.magnitudes_[i] - v2.magnitudes_[i];
        }
        return v;
    }
    return compilerpleaser;
}

// * operator (vector dot product)
double operator*(const EuclideanVector& v1, const EuclideanVector& v2){
    double dot_product = 0;
    if (v1.dimensions_ == v2.dimensions_) {
        for (auto i = 0; i < v1.dimensions_; ++i) {
            dot_product = dot_product + (v2.magnitudes_[i]*v1.magnitudes_[i]);
        }
        return dot_product;
    }
    return dot_product;
}

// * operator (scalar second)
EuclideanVector operator*(const EuclideanVector& v1, const int& n){
    EuclideanVector v = EuclideanVector{v1.dimensions_};
    for (auto i = 0; i < v1.dimensions_; ++i) {
        v.magnitudes_[i] = (v1.magnitudes_[i] * n);
    }
    return v;
}

// * operator (scalar first)
EuclideanVector operator*(const int& n, const EuclideanVector& v1){
    EuclideanVector v = EuclideanVector{v1.dimensions_};
    for (auto i = 0; i < v1.dimensions_; ++i) {
        v.magnitudes_[i] = (v1.magnitudes_[i] * n);
    }
    return v;
}


// / operator
EuclideanVector operator/(const EuclideanVector& v1, const int& n){
    EuclideanVector v = EuclideanVector{v1.dimensions_};
    for (auto i = 0; i < v1.dimensions_; ++i) {
        v.magnitudes_[i] = (v1.magnitudes_[i] / n);
    }
    return v;
}

// << operator
std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) {
 //   std::cout << "<< operator called" << std::endl;
    os << "[";
    for (auto i = 0; i < v.dimensions_; ++i) {
        os << v.magnitudes_[i] << " ";
    }
    os <<  "]";
    return os;
}


