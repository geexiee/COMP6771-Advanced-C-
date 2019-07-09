#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// prints out all elements in a path
void PrintPath(std::vector<std::string>& path);
// creates dictionary of only words that are the same length as n
std::unordered_set<std::string> GetDict(std::size_t& n);
// gets ladders for a given start and end word
std::vector<std::vector<std::string>> GetLadders(std::string& start, std::string& end);
// gets a map of all words of given length as the keys, with their adjacent words as elements
std::unordered_map<std::string, std::vector<std::string>>
GetAdjacentDict(int begin_word_length, std::unordered_set<std::string>& dict);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
