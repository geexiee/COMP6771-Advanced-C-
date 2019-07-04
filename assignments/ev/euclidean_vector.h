// TODO(you): Include header guards

#include <exception>
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <math.h>

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
        std::cout << dimensions;
    }

    // regular constructor
    EuclideanVector(int dimensions, double magnitudes) : dimensions_{dimensions}, magnitudes_{std::make_unique<double[]>(dimensions)} {
        //std::cout << dimensions << " " << magnitudes_ << std::endl;
        for (auto j = 0; j < dimensions; ++j) {
            magnitudes_[j] = magnitudes;
        }
    }

    // iterator constructor
    EuclideanVector(std::vector<double>::const_iterator begin, std::vector<double>::const_iterator end) {
        std::cout << "why";
        int count = 0;
        for (auto iter = begin; iter != end; ++iter) {
            magnitudes_[count] = *iter;
            count++;
        }
        dimensions_ = count;
    }

    // copy constructor
    EuclideanVector(const EuclideanVector& original) : dimensions_(original.dimensions_) {
        for (int i = 0; i < original.dimensions_; ++i) {
            magnitudes_[i] = original.magnitudes_[i];
        }
    }

    // move constructor
    EuclideanVector(EuclideanVector&& original) noexcept : dimensions_(std::move(original.dimensions_)) {
        for (int i = 0; i < original.dimensions_; ++i) {
            magnitudes_[i] = original.magnitudes_[i];
        }
        original.magnitudes_ = nullptr;
        original.dimensions_ = 0;
    }

    // = operator
    EuclideanVector& operator=(const EuclideanVector& original);

    // move operator
    EuclideanVector& operator=(EuclideanVector&& original) noexcept;

    // += operator, STILL NEED TO IMPLEMENT ERROR HANDLING FOR WHEN DIMENSION DIFF
    EuclideanVector& operator+=(const EuclideanVector& e);
    EuclideanVector& operator-=(const EuclideanVector& e);
    EuclideanVector& operator*=(const int& n);
    EuclideanVector& operator/=(const int& n);


    // + operator/friend,  STILL NEED TO IMPLEMENT ERROR HANDLING FOR WHEN DIMENSION DIFF
    friend bool operator==(const EuclideanVector& v1, const EuclideanVector& v2);
    friend bool operator!=(const EuclideanVector& v1, const EuclideanVector& v2);
    friend EuclideanVector operator+(const EuclideanVector& v1, const EuclideanVector& v2);
    friend EuclideanVector operator-(const EuclideanVector& v1, const EuclideanVector& v2);
    friend double operator*(const EuclideanVector& v1, const EuclideanVector& v2);
    friend EuclideanVector operator*(const EuclideanVector& v1, const int& n);
    friend EuclideanVector operator/(const EuclideanVector& v1, const int& n);




    // destructor
    ~EuclideanVector() noexcept = default;

    //friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);

    // methods
    int GetNumDimensions() { return dimensions_;}
    double at(const int& n) { return magnitudes_[n];}
    double GetEuclideanNorm() {
        double sum = 0;
        for (auto i = 0; i < dimensions_; ++i) {
            sum = sum + pow(magnitudes_[i], 2);
        }
        return sqrt(sum);
    }

 private:
    int dimensions_;
    std::unique_ptr<double[]> magnitudes_;
};
