//
// Created by Gordon Xie on 2019-07-18.
//

#ifndef UNTITLED_TUTE7_H
#define UNTITLED_TUTE7_H

#include <algorithm>
class tute7 {

};

namespace meme {
    template<typename T, int Size = 3>
    class FixedVector {
    public:
        explicit FixedVector(const T &val = T{}) {
            std::fill_n(data_, Size, val);
        }

        // initialiser list
        FixedVector(std::initializer_list<T> init) {
            static_assert(init.size() == Size);
            std::copy(init.begin(), init.end(), data_);
        }

        T &operator[](int i) {

        }

    private:
        T data_[Size];
    };

// to construct
    FixedVector<double, 88> a{};
}

using ev = std::vector<double>; // this is just using typedef
#endif //UNTITLED_TUTE7_H
