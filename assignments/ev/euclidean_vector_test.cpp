/*

  == Explanation and rational of testing ==

 The scope of my tests are mainly concerned with ensuring the correctness of each function (constructor, overload, method) that
 I implemented. To do so I created brief tests for each function (since each part of the program I implemented is relatively simple,
 if it works for a simple case, it should work for more complicated cases too).

 Furthermore, I only need to ensure that each constructor works, and then ensure each operator/method works
 for just one type of construction. This is because once an object is successfully constructed,
 it will be treated the same by the operators/methods regardless of how it was constructed.

 Before anything else, I want to ensure that my code handles all edge cases appropriately. This includes things such as
 multiplying two vectors with different number of dimensions, calling the move assignment on a const EV, finding the norm of a zero vector, creating an empty vector
 or exception handling etc. However, I will not test some already discussed edge cases such as multiplying two 0 vectors,
 as it has been stated in the specs that that case will not be tested.

 To ensure correctness of my program, I wanted to test each constructor, operator, and method.
 For each one, I want to test it with both a const and non const Euclidean vector, to ensure that everything
 I implemented behaves normally in both cases (ensuring const correctness). However, I will not test using a const EV for
 methods/operators that need to alter the calling EV, as that will always create an error (since the calling EV shouldn't even try to
 alter itself if it is const). Some features I didn't test with the const EV include +=, -=, *=, /=,
 setting at(), list/vector type conversion

 The first few tests were all on the constructors and [] operator, which I did first because they were the most important
 to use in further testing (e.g. using the constructors and [] to efficiently test other features).

 Overall, my tests should be quite thorough and cover quite a large scope/range of scenarios. By testing each and every
 individual constructor, overload, and method I implemented, as well as their different combinations of interactions,
 I should be able to cover most use cases and scenarios. Though the examples used may not be
 overly complex (There will be few EVs that are excessively long), that should be fine because the implementation for everything
 is quite simple, and extending the length of the EVs will just make longer iterations, which shouldn't ever produce
 unexpected behaviour.

*/

#include "assignments/ev/euclidean_vector.h"

#include "catch.h"

SCENARIO("Checking that the default constructor works") {
    GIVEN("A Euclidean Vector of size 3, with each dimension having magnitude 0") {
        EuclideanVector default_ev(3);
        WHEN("You check that the vector is constructed") {
            double e1 = default_ev[0];
            double e2 = default_ev[1];
            double e3 = default_ev[2];
            THEN("The number of dimensions should be 3 and each magnitude should be 0") {
                REQUIRE(e1 == 0);
                REQUIRE(e2 == 0);
                REQUIRE(e3 == 0);
                REQUIRE(default_ev.GetNumDimensions() == 3);
            }
        }
    }
}

SCENARIO("Checking that the default constructor works using the default value 1 when not specifying a size") {
    GIVEN("A Euclidean Vector with an unspecified size") {
        EuclideanVector default_ev;
        WHEN("You check that the vector is constructed") {
            double e1 = default_ev[0];
            THEN("The number of dimensions should be 1 and each magnitude should be 0") {
                REQUIRE(e1 == 0);
                REQUIRE(default_ev.GetNumDimensions() == 1);
            }
        }
    }
}

SCENARIO("Checking that the regular constructor works") {
    GIVEN("A Euclidean Vector of size 3 with each dimension having magnitude 5") {
        EuclideanVector regular_vector(3, 5);
        WHEN("You check that the vector is constructed") {
            double e3 = regular_vector[2];
            double e2 = regular_vector[1];
            double e1 = regular_vector[0];
            THEN("The number of dimensions should be 3 and each magnitude should be 5") {
                REQUIRE(e3 == 5);
                REQUIRE(e2 == 5);
                REQUIRE(e1 == 5);
                REQUIRE(regular_vector.GetNumDimensions() == 3);
            }
        }
    }
}

SCENARIO("Checking that the Iterator Constructor works") {
    GIVEN("A vector with values {1, 2, 3}") {
        std::vector<double> v = {1, 2, 3};
        WHEN("You try to construct a Euclidean Vector using this vector and the iterator constructor") {
            EuclideanVector iterator_vector{v.begin(), v.end()};
            THEN("You should get a Euclidean Vector {1, 2, 3}") {
                REQUIRE(iterator_vector.GetNumDimensions() == 3);
                REQUIRE(iterator_vector[0] == 1);
                REQUIRE(iterator_vector[1] == 2);
                REQUIRE(iterator_vector[2] == 3);
            }
        }
    }
}

SCENARIO("Checking that the copy constructor works") {
    GIVEN("An already existing Euclidean Vector Object") {
        EuclideanVector og(3, 3);
        WHEN("You try to copy it to another Euclidean Vector") {
            EuclideanVector copy{og};
            THEN("You should successfully construct a EV with the same values as the original and original still exists") {
                REQUIRE(copy[0] == 3);
                REQUIRE(copy[1] == 3);
                REQUIRE(copy[2] == 3);
                REQUIRE(copy.GetNumDimensions() == 3);
                REQUIRE(og[0] == 3);
                REQUIRE(og[1] == 3);
                REQUIRE(og[2] == 3);
                REQUIRE(og.GetNumDimensions() == 3);
            }
        }
    }
}

SCENARIO("Checking that the move constructor works") {
    GIVEN("An already existing Euclidean Vector Object") {
        EuclideanVector og(3, 3);
        WHEN("You try to move it to another Euclidean Vector") {
            EuclideanVector move{std::move(og)};
            THEN("You should successfully construct a EV with the same values as the original") {
                REQUIRE(move[0] == 3);
                REQUIRE(move[1] == 3);
                REQUIRE(move[2] == 3);
                REQUIRE(move.GetNumDimensions() == 3);
                AND_THEN("The original vector should have dimensions = 0") {
                    REQUIRE(og.GetNumDimensions() == 0);
                }
            }
        }
    }
}

SCENARIO("Using subscript with an EuclideanVector") {
    GIVEN("A Euclidean Vector of 3 with magnitudes (1, 2, 3)") {
        std::vector<double> v = {1, 2, 3};
        EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the subscript operator to store the value of each element in the array in a double") {
            double e1 = ev[0];
            double e2 = ev[1];
            double e3 = ev[2];
            THEN("We the value of each double should equal its corresponding value in the EV array") {
                REQUIRE(e3 == 3);
                REQUIRE(e2 == 2);
                REQUIRE(e1 == 1);
            }
        }
    }
}

SCENARIO("Checking that the << operator works") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v = {1, 2, 3};
        EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the << operator to print out the EV") {
            std::strstream s;
            s << ev;
            THEN("The output stream should print the contents of the EV surrounded by square brackets ie. [1 2 3]") {
                REQUIRE(strcmp(s.str(), "[1 2 3]") == 0);
            }
        }
    }
}

SCENARIO("Using the copy assignment on an Euclidean Vector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("You try to use the copy assignment on it") {
            EuclideanVector copy = ev1;
            THEN("You should produce a copy of the original vector, and the original vector should still exist in the same state it was before the copy assignment") {
                REQUIRE(copy[0] == 1);
                REQUIRE(copy[1] == 2);
                REQUIRE(copy[2] == 3);
                REQUIRE(ev1[0] == 1);
                REQUIRE(ev1[1] == 2);
                REQUIRE(ev1[2] == 3);
                REQUIRE(copy.GetNumDimensions() == 3);
                REQUIRE(ev1.GetNumDimensions() == 3);
            }
        }
    }
}

SCENARIO("Using the move assignment on an Euclidean Vector") {
    GIVEN("A Euclidean vector {1,2,3}" ) {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("You try to use the move assignment on it") {
            EuclideanVector move = std::move(ev1);
            THEN("You should produce a copy of the original vector, and the original vector should no longer exist") {
                REQUIRE(move[0] == 1);
                REQUIRE(move[1] == 2);
                REQUIRE(move[2] == 3);
                REQUIRE(move.GetNumDimensions() == 3);
                REQUIRE(ev1.GetNumDimensions() == 0);
            }
        }
    }
}

SCENARIO("Using the vector addition operator on two Euclidean Vectors") {
    GIVEN("A Euclidean vector {1,2,3 and another Euclidean Vector {2,3,4}" ) {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {2, 3, 4};
        EuclideanVector ev1{v1.begin(), v1.end()};
        EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to use the vector addition operator on them to add their corresponding magnitudes") {
            EuclideanVector sum = ev1 + ev2;
            THEN("You should produce an Euclidean Vector with magnitudes equal to the corresponding sums of the magnitudes of the original two Euclidean Vectors") {
                REQUIRE(sum[0] == 3);
                REQUIRE(sum[1] == 5);
                REQUIRE(sum[2] == 7);
                REQUIRE(sum.GetNumDimensions() == 3);
            }
        }
    }
}

SCENARIO("Using the vector subtraction operator on two Euclidean Vectors") {
    GIVEN("A Euclidean vector {1,2,3 and another Euclidean Vector {2,3,4}" ) {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {2, 3, 4};
        EuclideanVector ev1{v1.begin(), v1.end()};
        EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to use the vector subtraction operator on them to subtract their corresponding magnitudes") {
            EuclideanVector diff = ev1 - ev2;
            THEN("You should produce an Euclidean Vector with magnitudes equal to the corresponding differences of the magnitudes of the original two Euclidean Vectors") {
                REQUIRE(diff[0] == -1);
                REQUIRE(diff[1] == -1);
                REQUIRE(diff[2] == -1);
                REQUIRE(diff.GetNumDimensions() == 3);
            }
        }
    }
}


SCENARIO("Using the scalar multiplication operator (*=) on an EuclideanVector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v = {1, 2, 3};
        EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the scalar multiplication operator to multiply it by 2") {
            ev*=2;
            THEN("The magnitude of each dimension should be doubled") {
                REQUIRE(ev[0] == 2);
                REQUIRE(ev[1] == 4);
                REQUIRE(ev[2] == 6);
            }
        }
    }
}


SCENARIO("Using the scalar division operator (/=) on an EuclideanVector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v = {1, 2, 3};
        EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the scalar division operator on it to divide each magnitude by 2") {
            ev /= 2;
            THEN("The magnitude of each dimension should be halved") {
                REQUIRE(ev[0] == 0.5);
                REQUIRE(ev[1] == 1);
                REQUIRE(ev[2] == 1.5);
            }
        }
    }
}

SCENARIO("Using Vector type conversion on an EuclideanVector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v = {1, 2, 3};
        EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to cast it to a vector") {
            std::vector<double> vect = std::vector<double>{ev};
            THEN("The resulting vector should have all the same values as the original Euclidean Vector") {
                REQUIRE(vect[0] == 1);
                REQUIRE(vect[1] == 2);
                REQUIRE(vect[2] == 3);
                REQUIRE(vect.size() == 3);
            }
        }
    }
}

SCENARIO("Using List type conversion on an EuclideanVector") {
    GIVEN("A Euclidean Vector {1,2}") {
        std::vector<double> v = {1, 2};
        EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to cast it to a list") {
            std::list<double> list = std::list<double>{ev};
            THEN("The resulting vector should have all the same values as the original Euclidean Vector") {
                REQUIRE(list.front() == 1);
                REQUIRE(list.back() == 2);
                REQUIRE(list.size() == 2);
            }
        }
    }
}

SCENARIO("Using the at method to get the value of an element in an Euclidean Vector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v = {1, 2,3};
        EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the at method to find and store each element in the EV") {
            double e1 = ev.at(0);
            double e2 = ev.at(1);
            double e3 = ev.at(2);
            THEN("The value of each stored double should equal to the corresponding element in the EV") {
                REQUIRE(e1 == 1);
                REQUIRE(e2 == 2);
                REQUIRE(e3 == 3);
            }
        }
    }
}

SCENARIO("Using the at method to set the value of an element in an Euclidean Vector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v = {1, 2,3};
        EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the at method to find and set each element in the EV") {
            ev.at(0) = 2;
            ev.at(1) = 3;
            ev.at(2) = 4;
            THEN("The value of each element should equal to the corresponding value we set it to") {
                REQUIRE(ev[0] == 2);
                REQUIRE(ev[1] == 3);
                REQUIRE(ev[2] == 4);
            }
        }
    }
}

SCENARIO("Using the GetNumDimensions method to find the number of dimensions in an Euclidean Vector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v = {1, 2,3};
        EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the GetNumDimensions method to find the number of dimensions in the EV") {
            int n = ev.GetNumDimensions();
            THEN("The return value of the function should equal the number of dimensions in the EV") {
                REQUIRE(n == 3);
            }
        }
    }
}

SCENARIO("Using the GetEuclideanNorm method to find the Euclidean norm of an Euclidean Vector") {
    GIVEN("A Euclidean Vector {2, 2, 2, 2}") {
        std::vector<double> v = {2, 2, 2, 2};
        EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the GetEuclideanNorm method to find the Euclidean Norm of the EV") {
            double norm = ev.GetEuclideanNorm();
            THEN("The return value of the function should equal the square root of the sum of the squares of the magnitudes in each dimension") {
                REQUIRE(norm == 4);
            }
        }
    }
}

SCENARIO("Using the CreateUnitVector method to create the unit vector of an Euclidean Vector") {
    GIVEN("A Euclidean Vector {2, 2, 2, 2}") {
        std::vector<double> v = {2, 2, 2, 2};
        EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the CreateUnitVector method to create the unit vector of the EV") {
            EuclideanVector uvector = ev.CreateUnitVector();
            THEN("The magnitude for each dimension in the unit vector should equal the original vector's magnitude divided by the Euclidean norm") {
                REQUIRE(uvector[0] == 0.5);
                REQUIRE(uvector[1] == 0.5);
                REQUIRE(uvector[2] == 0.5);
                REQUIRE(uvector[3] == 0.5);
            }
        }
    }
}

SCENARIO("Using == to test equality of two identical EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to use the == operator to see if they are identical") {
            bool same = v1==v2;
            THEN("The result should return true") {
                REQUIRE(same == true);
            }
        }
    }
}

SCENARIO("Using == to test equality of two different EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {2,3,4}") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v3 = {2, 3, 4};
        EuclideanVector ev1{v1.begin(), v1.end()};
        EuclideanVector ev3{v3.begin(), v3.end()};
        WHEN("You try to use the == operator to see if they are not identical") {
            bool same = v1==v3;
            THEN("The result should return false") {
                REQUIRE(same == false);
            }
        }
    }
}

SCENARIO("Using != to test inequality of two identical EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to use the != operator to see if they are not identical") {
            bool same = v1!=v2;
            THEN("The result should return false") {
                REQUIRE(same == false);
            }
        }
    }
}

SCENARIO("Using != to test inequality of two different EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {2,3,4}") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v3 = {2, 3, 4};
        EuclideanVector ev1{v1.begin(), v1.end()};
        EuclideanVector ev3{v3.begin(), v3.end()};
        WHEN("You try to use the != operator to see if they are not identical") {
            bool same = v1!=v3;
            THEN("The result should return true") {
                REQUIRE(same == true);
            }
        }
    }
}

SCENARIO("Using the addition operator (+) on two different EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {2,3,4}") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {2, 3, 4};
        EuclideanVector ev1{v1.begin(), v1.end()};
        EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to use the addition operator to add their magnitudes together") {
            EuclideanVector sum = ev1 + ev2;
            THEN("The values of the sum EV should equal the sum of the respective magnitudes of the original 2 EVs") {
                REQUIRE(sum[0] == 3);
                REQUIRE(sum[1] == 5);
                REQUIRE(sum[2] == 7);
            }
        }
    }
}

SCENARIO("Using the subtraction operator (-) on two different EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {2,3,4}") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {2, 3, 4};
        EuclideanVector ev1{v1.begin(), v1.end()};
        EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to use the subtraction operator to subtract their magnitudes together") {
            EuclideanVector sum = ev1 - ev2;
            THEN("The values of the sum EV should equal the difference of the respective magnitudes of the original 2 EVs") {
                REQUIRE(sum[0] == -1);
                REQUIRE(sum[1] == -1);
                REQUIRE(sum[2] == -1);
            }
        }
    }
}

SCENARIO("Using the dot product multiplication operator (*) on 2 EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {2,3,4}") {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        std::vector<double> v2 = {2, 3, 4};
        EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to multiply an the two EVs together to find the dot product") {
            double dotproduct = ev2*ev1;
            THEN("The resulting value should equal the dot product of the two EVs") {
                REQUIRE(dotproduct == 20);
            }
        }
    }
}

SCENARIO("Using the scalar multiplication operator (*) on an EuclideanVector with the scalar in front") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("You try to multiply an EV with a scalar in front") {
            EuclideanVector product = 2*ev1;
            THEN("The resulting EV should have magnitudes equal to double its original value") {
                REQUIRE(product[0] == 2);
                REQUIRE(product[1] == 4);
                REQUIRE(product[2] == 6);
            }
        }
    }
}

SCENARIO("Using the scalar multiplication operator (*) on an EuclideanVector with the scalar in the back") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("You try to multiply an EV with a scalar in the back") {
            EuclideanVector product = ev1 * 2;
            THEN("The resulting EV should have magnitudes equal to double its original value") {
                REQUIRE(product[0] == 2);
                REQUIRE(product[1] == 4);
                REQUIRE(product[2] == 6);
            }
        }
    }
}

SCENARIO("Using the division operator (/) to divide each magnitude of an Euclidean Vector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("You try to divide the EV by 2 and copy the result to another EV") {
            EuclideanVector quotient = ev1 / 2;
            THEN("The resulting EV should have magnitudes equal to half its original value") {
                REQUIRE(quotient[0] == 0.5);
                REQUIRE(quotient[1] == 1);
                REQUIRE(quotient[2] == 1.5);
            }
        }
    }
}

SCENARIO("Checking that using the + operator on 2 EVs with different number of dimensions throws the correct exception") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {1,2}") {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        std::vector<double> v2 = {1, 2};
        EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("I try to add two EVs with different number of dimensions using the + friend operator") {
            THEN("I should catch an exception with the correct message") {
                REQUIRE_THROWS_WITH(ev1 + ev2, "Dimensions of LHS(X) and RHS(Y) do not match");
            }
        }
    }
}

SCENARIO("Checking that using the += operator on 2 EVs with different number of dimensions throws the correct exception") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {1,2}") {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        std::vector<double> v2 = {1, 2};
        EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("I try to add two EVs with different number of dimensions using the += operator") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1 += ev2, "Dimensions of LHS(X) and RHS(Y) do not match");
            }
        }
    }
}

SCENARIO("Checking that using the -= operator on 2 EVs with different number of dimensions throws the correct exception") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {1,2}") {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        std::vector<double> v2 = {1, 2};
        EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("I try to subtract two EVs with different number of dimensions using the -= operator") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1 -= ev2, "Dimensions of LHS(X) and RHS(Y) do not match");
            }
        }
    }
}

SCENARIO("Checking that using the /= operator to divide an EV by 0 throws the correct exception") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("I try to divide an EV by 0 using the /= operator") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1/0, "Invalid vector division by 0");
            }
        }
    }
}

SCENARIO("Checking that using the at method at an index < 0 throws the correct exception") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("I try to use the at method at an index < 0") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1.at(-1), "Index X is not valid for this EuclideanVector object");
            }
        }
    }
}

SCENARIO("Checking that using the at method at an index greater than the number of dimensions in the EV throws the correct exception") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("I try to use the at method at an index > the number of dimensions in the EV") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1.at(6), "Index X is not valid for this EuclideanVector object");
            }
        }
    }
}

SCENARIO("Trying to use GetEuclideanNorm method on a vector with 0 dimensions") {
    GIVEN("A Euclidean Vector with 0 dimensions") {
        EuclideanVector test(0);
        WHEN("I try to use the GetEuclideanNorm method on the 0 vector") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(test.GetEuclideanNorm(), "EuclideanVector with no dimensions does not have a norm");
            }
        }
    }
}

SCENARIO("Trying to use CreateUnitVector method on a vector with 0 Dimensions/EuclideanNorm") {
    GIVEN("A Euclidean Vector with 0 dimensions/EuclideanNorm") {
        EuclideanVector test(0);
        WHEN("I try to use the CreateUnitVector method on the 0 vector") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(test.CreateUnitVector(), "EuclideanVector with no dimensions does not have a unit vector");
            }
        }
    }
}

SCENARIO("Trying to use - friend operator on two EVs with a different number of dimensions") {
    GIVEN("Two EVs with a different number of dimensions") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {1, 2};
        EuclideanVector ev1{v1.begin(), v1.end()};
        EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("I try to use the - operator on the two EVs") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1-ev2, "Dimensions of LHS(X) and RHS(Y) do not match");
            }
        }
    }
}

SCENARIO("Trying to use * (dot product) friend operator on two EVs with a different number of dimensions") {
    GIVEN("Two EVs with a different number of dimensions") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {1, 2};
        EuclideanVector ev1{v1.begin(), v1.end()};
        EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("I try to use the * operator to find the dot product the two EVs") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1 * ev2, "Dimensions of LHS(X) and RHS(Y) do not match");
            }
        }
    }
}

SCENARIO("Trying to divide an EV by 0") {
    GIVEN("An Euclidean Vector") {
        std::vector<double> v1 = {1, 2, 3};
        EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("I try to use the / operator to divide the EV by 0") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1/0, "Invalid vector division by 0");
            }
        }
    }
}

// REPEATING ALL PREVIOUS TESTS BUT WITH A CONST EV INSTEAD (where appropriate, I wouldn't test const on features that need to change the calling EV)

SCENARIO("Checking that the default constructor works with a const EV") {
    GIVEN("A Euclidean Vector of size 3, with each dimension having magnitude 0") {
        const EuclideanVector default_ev(3);
        WHEN("You check that the vector is constructed") {
            double e1 = default_ev[0];
            double e2 = default_ev[1];
            double e3 = default_ev[2];
            THEN("The number of dimensions should be 3 and each magnitude should be 0") {
                REQUIRE(e1 == 0);
                REQUIRE(e2 == 0);
                REQUIRE(e3 == 0);
                REQUIRE(default_ev.GetNumDimensions() == 3);
            }
        }
    }
}

SCENARIO("Checking that the regular constructor works with a const EV") {
    GIVEN("A Euclidean Vector of size 3 with each dimension having magnitude 5") {
        const EuclideanVector regular_vector(3, 5);
        WHEN("You check that the vector is constructed") {
            double e3 = regular_vector[2];
            double e2 = regular_vector[1];
            double e1 = regular_vector[0];
            THEN("The number of dimensions should be 3 and each magnitude should be 5") {
                REQUIRE(e3 == 5);
                REQUIRE(e2 == 5);
                REQUIRE(e1 == 5);
                REQUIRE(regular_vector.GetNumDimensions() == 3);
            }
        }
    }
}

SCENARIO("Checking that the Iterator Constructor works with a const EV") {
    GIVEN("A vector with values {1, 2, 3}") {
        std::vector<double> v = {1, 2, 3};
        WHEN("You try to construct a Euclidean Vector using this vector and the iterator constructor") {
            const EuclideanVector iterator_vector{v.begin(), v.end()};
            THEN("You should get a Euclidean Vector {1, 2, 3}") {
                REQUIRE(iterator_vector.GetNumDimensions() == 3);
                REQUIRE(iterator_vector[0] == 1);
                REQUIRE(iterator_vector[1] == 2);
                REQUIRE(iterator_vector[2] == 3);
            }
        }
    }
}

SCENARIO("Checking that the copy constructor works with a const EV") {
    GIVEN("An already existing Euclidean Vector Object") {
        EuclideanVector og(3, 3);
        WHEN("You try to copy it to another Euclidean Vector") {
            const EuclideanVector copy{og};
            THEN("You should successfully construct a EV with the same values as the original") {
                REQUIRE(copy[0] == 3);
                REQUIRE(copy[1] == 3);
                REQUIRE(copy[2] == 3);
                REQUIRE(copy.GetNumDimensions() == 3);
            }
        }
    }
}

SCENARIO("Checking that the move constructor works with a const EV") {
    GIVEN("An already existing Euclidean Vector Object") {
        EuclideanVector og(3, 3);
        WHEN("You try to move it to another Euclidean Vector") {
            const EuclideanVector move{std::move(og)};
            THEN("You should successfully construct a EV with the same values as the original") {
                REQUIRE(move[0] == 3);
                REQUIRE(move[1] == 3);
                REQUIRE(move[2] == 3);
                REQUIRE(move.GetNumDimensions() == 3);
                AND_THEN("The original vector should have dimensions = 0") {
                    REQUIRE(og.GetNumDimensions() == 0);
                }
            }
        }
    }
}


SCENARIO("Checking that the << operator works with a const EV") {
    GIVEN("A const Euclidean Vector of 3 with magnitudes (1, 2, 3)") {
        const std::vector<double> v = {1, 2, 3};
        const EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the << operator to print out the EV") {
            std::strstream s;
            s << ev;
            THEN("The output stream should print the contents of the EV surrounded by square brackets ie. [1 2 3]") {
                REQUIRE(strcmp(s.str(), "[1 2 3]") == 0);
            }
        }
    }
}

SCENARIO("Using the copy assignment on a const Euclidean Vector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("You try to use the copy assignment on it") {
            const EuclideanVector copy = ev1;
            THEN("You should produce a copy of the original vector, and the original vector should still exist in the same state it was before the copy assignment") {
                REQUIRE(copy[0] == 1);
                REQUIRE(copy[1] == 2);
                REQUIRE(copy[2] == 3);
                REQUIRE(ev1[0] == 1);
                REQUIRE(ev1[1] == 2);
                REQUIRE(ev1[2] == 3);
                REQUIRE(copy.GetNumDimensions() == 3);
                REQUIRE(ev1.GetNumDimensions() == 3);
            }
        }
    }
}

SCENARIO("Using the move assignment on a const Euclidean Vector") {
    GIVEN("A Euclidean vector {1,2,3}" ) {
        std::vector<double> v1 = {1, 2, 3};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("You try to use the move assignment on it") {
            EuclideanVector move = std::move(ev1);
            THEN("You should end up using the copy assignment instead (so the original will still exist)") {
                REQUIRE(move[0] == 1);
                REQUIRE(move[1] == 2);
                REQUIRE(move[2] == 3);
                REQUIRE(move.GetNumDimensions() == 3);
                REQUIRE(ev1[0] == 1);
                REQUIRE(ev1[1] == 2);
                REQUIRE(ev1[2] == 3);
                REQUIRE(ev1.GetNumDimensions() == 3);
            }
        }
    }
}

SCENARIO("Using the vector addition operator on two const Euclidean Vectors") {
    GIVEN("A Euclidean vector {1,2,3 and another Euclidean Vector {2,3,4}" ) {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {2, 3, 4};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        const EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to use the vector addition operator on them to add their corresponding magnitudes") {
            const EuclideanVector sum = ev1 + ev2;
            THEN("You should produce an Euclidean Vector with magnitudes equal to the corresponding sums of the magnitudes of the original two Euclidean Vectors") {
                REQUIRE(sum[0] == 3);
                REQUIRE(sum[1] == 5);
                REQUIRE(sum[2] == 7);
                REQUIRE(sum.GetNumDimensions() == 3);
            }
        }
    }
}

SCENARIO("Using the vector subtraction operator on two const Euclidean Vectors") {
    GIVEN("A Euclidean vector {1,2,3 and another Euclidean Vector {2,3,4}" ) {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {2, 3, 4};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        const EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to use the vector subtraction operator on them to subtract their corresponding magnitudes") {
            const EuclideanVector diff = ev1 - ev2;
            THEN("You should produce an Euclidean Vector with magnitudes equal to the corresponding differences of the magnitudes of the original two Euclidean Vectors") {
                REQUIRE(diff[0] == -1);
                REQUIRE(diff[1] == -1);
                REQUIRE(diff[2] == -1);
                REQUIRE(diff.GetNumDimensions() == 3);
            }
        }
    }
}

SCENARIO("Using Vector type conversion on a const EuclideanVector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v = {1, 2, 3};
        const EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to cast it to a vector") {
            std::vector<double> vect = std::vector<double>{ev};
            THEN("The resulting vector should have all the same values as the original Euclidean Vector") {
                REQUIRE(vect[0] == 1);
                REQUIRE(vect[1] == 2);
                REQUIRE(vect[2] == 3);
                REQUIRE(vect.size() == 3);
            }
        }
    }
}

SCENARIO("Using List type conversion on a const EuclideanVector") {
    GIVEN("A Euclidean Vector {1,2}") {
        std::vector<double> v = {1, 2};
        EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to cast it to a list") {
            std::list<double> list = std::list<double>{ev};
            THEN("The resulting vector should have all the same values as the original Euclidean Vector") {
                REQUIRE(list.front() == 1);
                REQUIRE(list.back() == 2);
                REQUIRE(list.size() == 2);
            }
        }
    }
}

SCENARIO("Using subscript with a const EuclideanVector") {
    GIVEN("A Euclidean Vector of 3 with magnitudes (1, 2, 3)") {
       std::vector<double> v = {1, 2, 3};
       const EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the subscript operator to store the value of each element in the array in a double") {
            double e1 = ev[0];
            double e2 = ev[1];
            double e3 = ev[2];
            THEN("We the value of each double should equal its corresponding value in the EV array") {
                REQUIRE(e3 == 3);
                REQUIRE(e2 == 2);
                REQUIRE(e1 == 1);
            }
        }
    }
}


SCENARIO("Using the at method to get the value of an element in a const Euclidean Vector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v = {1, 2,3};
        const EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the at method to find and store each element in the EV") {
            double e1 = ev.at(0);
            double e2 = ev.at(1);
            double e3 = ev.at(2);
            THEN("The value of each stored double should equal to the corresponding element in the EV") {
                REQUIRE(e1 == 1);
                REQUIRE(e2 == 2);
                REQUIRE(e3 == 3);
            }
        }
    }
}

SCENARIO("Using the GetNumDimensions method to find the number of dimensions in a const Euclidean Vector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v = {1, 2,3};
        const EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the GetNumDimensions method to find the number of dimensions in the EV") {
            int n = ev.GetNumDimensions();
            THEN("The return value of the function should equal the number of dimensions in the EV") {
                REQUIRE(n == 3);
            }
        }
    }
}


SCENARIO("Using the GetEuclideanNorm method to find the Euclidean norm of a const Euclidean Vector") {
    GIVEN("A Euclidean Vector {2, 2, 2, 2}") {
        std::vector<double> v = {2, 2, 2, 2};
        const EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the GetEuclideanNorm method to find the Euclidean Norm of the EV") {
            double norm = ev.GetEuclideanNorm();
            THEN("The return value of the function should equal the square root of the sum of the squares of the magnitudes in each dimension") {
                REQUIRE(norm == 4);
            }
        }
    }
}

SCENARIO("Using the CreateUnitVector method to create the unit vector of a const Euclidean Vector") {
    GIVEN("A Euclidean Vector {2,2,2,2}") {
        std::vector<double> v = {2, 2, 2, 2};
        const EuclideanVector ev{v.begin(), v.end()};
        WHEN("You try to use the CreateUnitVector method to create the unit vector of the EV") {
            EuclideanVector uvector = ev.CreateUnitVector();
            THEN("The magnitude for each dimension in the unit vector should equal the original vector's magnitude divided by the Euclidean norm") {
                REQUIRE(uvector[0] == 0.5);
                REQUIRE(uvector[1] == 0.5);
                REQUIRE(uvector[2] == 0.5);
                REQUIRE(uvector[3] == 0.5);
            }
        }
    }
}

SCENARIO("Using == to test equality of two identical const EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {1, 2, 3};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        const EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to use the == operator to see if they are identical") {
            bool same = v1==v2;
            THEN("The result should return true") {
                REQUIRE(same == true);
            }
        }
    }
}

SCENARIO("Using == to test equality of two different const EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {2,3,4}") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v3 = {2, 3, 4};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        const EuclideanVector ev3{v3.begin(), v3.end()};
        WHEN("You try to use the == operator to see if they are identical") {
            bool same = v1==v3;
            THEN("The result should return false") {
                REQUIRE(same == false);
            }
        }
    }
}

SCENARIO("Using != to test inequality of two identical const EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {1, 2, 3};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        const EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to use the != operator to see if they are not identical") {
            bool same = v1!=v2;
            THEN("The result should return false") {
                REQUIRE(same == false);
            }
        }
    }
}

SCENARIO("Using != to test inequality of two different const EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {2,3,4}") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v3 = {2, 3, 4};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        const EuclideanVector ev3{v3.begin(), v3.end()};
        WHEN("You try to use the != operator to see if they are not identical") {
            bool same = v1!=v3;
            THEN("The result should return true") {
                REQUIRE(same == true);
            }
        }
    }
}

SCENARIO("Using the addition operator (+) on two different const EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {2,3,4}") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {2, 3, 4};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        const EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to use the addition operator to add their magnitudes together") {
            EuclideanVector sum = ev1 + ev2;
            THEN("The values of the sum EV should equal the sum of the respective magnitudes of the original 2 EVs") {
                REQUIRE(sum[0] == 3);
                REQUIRE(sum[1] == 5);
                REQUIRE(sum[2] == 7);
            }
        }
    }
}

SCENARIO("Using the subtraction operator (-) on two different const EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {2,3,4}") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {2, 3, 4};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        const EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to use the subtraction operator to subtract their magnitudes together") {
            EuclideanVector sum = ev1 - ev2;
            THEN("The values of the sum EV should equal the difference of the respective magnitudes of the original 2 EVs") {
                REQUIRE(sum[0] == -1);
                REQUIRE(sum[1] == -1);
                REQUIRE(sum[2] == -1);
            }
        }
    }
}

SCENARIO("Using the dot product multiplication operator (*) on 2 const EuclideanVectors") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {2,3,4}") {
        std::vector<double> v1 = {1, 2, 3};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        std::vector<double> v2 = {2, 3, 4};
        const EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("You try to multiply an the two EVs together to find the dot product") {
            double dot_product = ev2*ev1;
            THEN("The resulting value should equal the dot product of the two EVs") {
                REQUIRE(dot_product == 20);
            }
        }
    }
}

SCENARIO("Using the scalar multiplication operator (*) on a const EuclideanVector with the scalar in front") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("You try to multiply an EV with a scalar in front") {
            EuclideanVector product = 2*ev1;
            THEN("The resulting EV should have magnitudes equal to double its original value") {
                REQUIRE(product[0] == 2);
                REQUIRE(product[1] == 4);
                REQUIRE(product[2] == 6);
            }
        }
    }
}

SCENARIO("Using the scalar multiplication operator (*) on a const EuclideanVector with the scalar in the back") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("You try to multiply an EV with a scalar in the back") {
            EuclideanVector product = ev1 * 2;
            THEN("The resulting EV should have magnitudes equal to double its original value") {
                REQUIRE(product[0] == 2);
                REQUIRE(product[1] == 4);
                REQUIRE(product[2] == 6);
            }
        }
    }
}

SCENARIO("Using the division operator (/) to divide each magnitude of a const Euclidean Vector") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("You try to divide the EV by 2 and copy the result to another EV") {
            EuclideanVector quotient = ev1 / 2;
            THEN("The resulting EV should have magnitudes equal to half its original value") {
                REQUIRE(quotient[0] == 0.5);
                REQUIRE(quotient[1] == 1);
                REQUIRE(quotient[2] == 1.5);
            }
        }
    }
}

SCENARIO("Checking that using the + operator on 2 const EVs with different number of dimensions throws the correct exception") {
    GIVEN("A Euclidean Vector {1,2,3} and another Euclidean Vector {1,2}") {
        std::vector<double> v1 = {1, 2, 3};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        std::vector<double> v2 = {1, 2};
        const EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("I try to add two EVs with different number of dimensions using the + friend operator") {
            THEN("I should catch an exception with the correct message") {
                REQUIRE_THROWS_WITH(ev1 + ev2, "Dimensions of LHS(X) and RHS(Y) do not match");
            }
        }
    }
}

SCENARIO("Checking that using the at method at an index < 0 on a const EV throws the correct exception") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("I try to use the at method at an index < 0") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1.at(-1), "Index X is not valid for this EuclideanVector object");
            }
        }
    }
}

SCENARIO("Checking that using the at method at an index greater than the number of dimensions in the const EV throws the correct exception") {
    GIVEN("A Euclidean Vector {1,2,3}") {
        std::vector<double> v1 = {1, 2, 3};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("I try to use the at method at an index > the number of dimensions in the EV") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1.at(6), "Index X is not valid for this EuclideanVector object");
            }
        }
    }
}

SCENARIO("Trying to use GetEuclideanNorm method on a const Euclidean vector with 0 dimensions") {
    GIVEN("A Euclidean Vector with 0 dimensions") {
        const EuclideanVector test(0);
        WHEN("I try to use the GetEuclideanNorm method on the 0 vector") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(test.GetEuclideanNorm(), "EuclideanVector with no dimensions does not have a norm");
            }
        }
    }
}

SCENARIO("Trying to use CreateUnitVector method on a const Euclidean vector with 0 Dimensions/EuclideanNorm") {
    GIVEN("A Euclidean Vector with 0 dimensions/EuclideanNorm") {
        const EuclideanVector test(0);
        WHEN("I try to use the CreateUnitVector method on the 0 vector") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(test.CreateUnitVector(), "EuclideanVector with no dimensions does not have a unit vector");
            }
        }
    }
}

SCENARIO("Trying to use - friend operator on two const EVs with a different number of dimensions") {
    GIVEN("Two EVs with a different number of dimensions") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {1, 2};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        const EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("I try to use the - operator on the two EVs") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1-ev2, "Dimensions of LHS(X) and RHS(Y) do not match");
            }
        }
    }
}

SCENARIO("Trying to use * (dot product) friend operator on two const EVs with a different number of dimensions") {
    GIVEN("Two EVs with a different number of dimensions") {
        std::vector<double> v1 = {1, 2, 3};
        std::vector<double> v2 = {1, 2};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        const EuclideanVector ev2{v2.begin(), v2.end()};
        WHEN("I try to use the * operator to find the dot product the two EVs") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1 * ev2, "Dimensions of LHS(X) and RHS(Y) do not match");
            }
        }
    }
}

SCENARIO("Trying to divide a const EV by 0") {
    GIVEN("A const EV") {
        std::vector<double> v1 = {1, 2, 3};
        const EuclideanVector ev1{v1.begin(), v1.end()};
        WHEN("I try to use the / operator to divide the EV by 0") {
            THEN("I should catch an exception") {
                REQUIRE_THROWS_WITH(ev1/0, "Invalid vector division by 0");
            }
        }
    }
}