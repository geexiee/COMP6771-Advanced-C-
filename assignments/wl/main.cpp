#include <iostream>
#include <string>
#include <vector>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

int main() {
  std::string start, end;

  std::cout << "Enter start word (RETURN to quit):";
  std::getline(std::cin, start);
  if (start.length() == 0)
    return 0;
  std::cout << "Enter destination word:";
  std::getline(std::cin, end);
  if (end.length() == 0)
    return 0;

  std::vector<std::vector<std::string>> master_ladder = GetLadders(start, end);
  if (master_ladder.begin() != master_ladder.end()) {
    std::cout << "Found Ladder: ";
    for (std::vector<std::string>& path : master_ladder) {
      PrintPath(path);
    }
  } else {
    std::cout << "No ladder found."
              << "\n";
  }
  return 0;
}
