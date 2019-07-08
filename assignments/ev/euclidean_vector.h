// TODO(you): Include header guards

#include <exception>
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <math.h>
#include <iterator>
#include <list>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept{ return what_.c_str(); }
 private:
  std::string what_;
};

class EuclideanVector {
 public:
    // CONSTRUCTORS
    // default constructor
    explicit EuclideanVector(int dimensions = 1) : EuclideanVector{dimensions, 0} {
        //std::cout << "default constructor called " << dimensions << std::endl;
    }

    // regular constructor
    EuclideanVector(int dimensions, double magnitudes) : dimensions_{dimensions}, magnitudes_{std::make_unique<double[]>(dimensions)} {
       // std::cout << "regular constructor called" << std::endl;
        for (auto j = 0; j < dimensions; ++j) {
            magnitudes_[j] = magnitudes;
        }
    }

    // iterator constructor
    EuclideanVector(std::vector<double>::const_iterator begin, std::vector<double>::const_iterator end) {
       // std::cout << "iterator constructor called" << std::endl;
        int n_dimensions = 0;
        for (auto iter = begin; iter != end; ++iter) {
            n_dimensions++;
        }
        dimensions_ = n_dimensions;
        magnitudes_ = std::make_unique<double[]>(n_dimensions);
        auto index = 0;
        for (auto iter = begin; iter != end; ++iter) {
            magnitudes_[index] = *iter;
            ++index;
        }
    }

    // copy constructor
    EuclideanVector(const EuclideanVector& original) : dimensions_(original.dimensions_) {
     //   std::cout << "copy constructor called" << std::endl;
        magnitudes_ = std::make_unique<double[]>(original.dimensions_);
        for (int i = 0; i < original.dimensions_; ++i) {
            magnitudes_[i] = original.magnitudes_[i];
        }
    }

    EuclideanVector(EuclideanVector&& o) noexcept : dimensions_{o.dimensions_}, magnitudes_{std::move(o.magnitudes_)} {
     //   std::cout << "move constructor called" << std::endl;
        o.dimensions_ = 0;
    }


    // INTERNAL OPERATORS #############################################################################################

    // copy operator
    EuclideanVector operator=(const EuclideanVector& original);
    // move operator
    EuclideanVector& operator=(EuclideanVector&& original) noexcept;
    // other operators, STILL NEED TO IMPLEMENT ERROR HANDLING FOR WHEN DIMENSION DIFF
    EuclideanVector& operator+=(const EuclideanVector& e);
    EuclideanVector& operator-=(const EuclideanVector& e);
    EuclideanVector& operator*=(const int& n);
    EuclideanVector& operator/=(const int& n);
    double& operator[](const int index);
    double operator[](const int index) const;
    // vector type conversion
    explicit operator std::vector<double>() {
     //   std::cout << "vector converter called" << std::endl;
        std::vector<double> temp;
        for (auto i = 0; i < this->dimensions_; ++i) {
            temp.emplace_back(this->magnitudes_[i]);
        }
        return temp;
    }
    // List type conversion
    explicit operator std::list<double>() {
    //    std::cout << "list converter called" << std::endl;
        std::list<double> temp;
        for (auto i = 0; i < this->dimensions_; ++i) {
            temp.emplace_back(this->magnitudes_[i]);
        }
        return temp;
    }


    // + operator/friend,  STILL NEED TO IMPLEMENT ERROR HANDLING FOR WHEN DIMENSION DIFF ##############################################
    friend bool operator==(const EuclideanVector& v1, const EuclideanVector& v2);
    friend bool operator!=(const EuclideanVector& v1, const EuclideanVector& v2);
    friend EuclideanVector operator+(const EuclideanVector& v1, const EuclideanVector& v2);
    friend EuclideanVector operator-(const EuclideanVector& v1, const EuclideanVector& v2);
    friend double operator*(const EuclideanVector& v1, const EuclideanVector& v2);
    friend EuclideanVector operator*(const EuclideanVector& v1, const int& n);
    friend EuclideanVector operator*(const int& n, const EuclideanVector& v1);
    friend EuclideanVector operator/(const EuclideanVector& v1, const int& n);
    friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);

    // destructor
    ~EuclideanVector() noexcept = default;

    // methods ##############################################################################################
    double at(const int& n) const {
        if (n < 0 || n >= dimensions_) {
            throw EuclideanVectorError("Index X is not valid for this EuclideanVector object");
        }
        return magnitudes_[n];
    }
    double& at(const int& n) {
        if (n < 0 || n >= dimensions_) {
            throw EuclideanVectorError("Index X is not valid for this EuclideanVector object");
        }
        return magnitudes_[n];
    }
    int GetNumDimensions() { return dimensions_;}
    double GetEuclideanNorm() {
        if (this->GetNumDimensions() == 0) {
            throw EuclideanVectorError("EuclideanVector with no dimensions does not have a norm");
        }
        double sum = 0;
        for (auto i = 0; i < dimensions_; ++i) {
            sum = sum + pow(magnitudes_[i], 2);
        }
        return sqrt(sum);
    }
    EuclideanVector CreateUnitVector() {
        if (this->GetNumDimensions() == 0) {
            throw EuclideanVectorError("EuclideanVector with no dimensions does not have a unit vector");
        }
        if (this->GetEuclideanNorm() == 0) {
            throw  EuclideanVectorError("EuclideanVector with euclidean normal of 0 does not have a unit vector");
        }
        double norm = this->GetEuclideanNorm();
        EuclideanVector temp(dimensions_);
        for (auto i = 0; i < dimensions_; ++i) {
            temp.magnitudes_[i] = this->magnitudes_[i]/norm;
        }
        return temp;
    }

 private:
    int dimensions_;
    std::unique_ptr<double[]> magnitudes_;
};
