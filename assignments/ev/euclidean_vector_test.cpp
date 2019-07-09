/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

 To ensure correctness of my program, I wanted to throughly test each constructor, operator, and method.
 For each one, I want to test it with both a const and non const Euclidean vector, to ensure that everything
 I implemented behaves normally in both cases.

 On a deeper level, I want to test each operator with EuclideanVectors which were constructed using the move
 and copy constructor, rather than with the default constructor. This is to test for any unexpected behaviour when
 moving/copying data between constructors.



*/

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

// TODO(students): Fill this in.
