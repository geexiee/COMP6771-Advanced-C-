#include "assignments/wl/word_ladder.h"
#include "assignments/wl/lexicon.h"

std::unordered_map<std::string, std::vector<std::string>>
GetAdjacentDict(int begin_word_length, std::unordered_set<std::string>& dict) {
  std::unordered_map<std::string, std::vector<std::string>> adjdict;
  std::vector<std::string> transformations;
  for (const auto& word : dict) {
    for (auto i = 0; i < begin_word_length; ++i) {
      std::string temp = word;
      temp[i] = '#';
      if (adjdict.find(temp) != adjdict.end()) {
        std::vector<std::string>& copy = adjdict.find(temp)->second;
        copy.emplace_back(word);
      } else {
        transformations.clear();
        transformations.emplace_back(word);
        adjdict.emplace(temp, transformations);
      }
    }
  }
  return adjdict;
}

std::unordered_set<std::string> GetDict(std::size_t& n) {
  auto lexicon = GetLexicon("assignments/wl/words.txt");
  std::unordered_set<std::string> dict;
  for (const auto& w : lexicon) {
    if (w.size() == n) {
      dict.emplace(w);
    }
  }
  return dict;
}

void PrintPath(std::vector<std::string>& path) {
  for (const auto& st : path) {
    std::cout << st << " ";
  }
  std::cout << "\n";
}

std::vector<std::vector<std::string>> GetLadders(std::string& start, std::string& end) {
  std::vector<std::vector<std::string>> master_ladder;
  int flag = 0;
  std::size_t n_letters = start.length();

  // map to store and access visited words
  std::unordered_set<std::string> visited;

  // initialising queue
  std::queue<std::vector<std::string>> q;
  std::vector<std::string> path;
  path.emplace_back(start);
  q.emplace(path);

  // initialising level tracker
  // (using "wtf" to mark end of level)
  std::vector<std::string> wtf;
  wtf.emplace_back("wtf");
  q.emplace(wtf);

  std::unordered_set<std::string> dictionary = GetDict(n_letters);
  std::unordered_map<std::string, std::vector<std::string>> real_dict =
      GetAdjacentDict(n_letters, dictionary);

  while (!q.empty()) {
    path = q.front();
    std::string& word = path.back();
    q.pop();
    visited.emplace(word);

    // if word = wtf, we've reached the end of a level
    if (word == "wtf") {
      q.emplace(wtf);
      if (q.front().front() == "wtf") {
        if (flag == 0) {
          // 2 "wtf"s in a row and flag = 0 means we've reached the end without
          // finding the word, so return empty ladder
          return master_ladder;
        }
        break;  // 2 wtfs in a row and flag = 1 means that we found the word and completed the
                // level, so can end the loop
      }
      if (flag == 1) {
        std::sort(master_ladder.begin(), master_ladder.end(),
                  std::less<std::vector<std::string>>());
        return master_ladder;
      } else {
        continue;
      }
    }

    for (auto i = 0u; i < n_letters; ++i) {
      // intermediate words
      std::string word_template = word;
      word_template[i] = '#';
      if (word_template != "") {
        std::vector<std::string> adjlist = real_dict.find(word_template)->second;
        for (const auto& adjword : adjlist) {
          if (adjword == end) {
            flag = 1;
            path.emplace_back(adjword);
            master_ladder.emplace_back(path);
          } else {
            if (visited.find(adjword) == visited.end()) {
              std::vector<std::string> new_path = path;
              new_path.emplace_back(adjword);
              q.emplace(new_path);
            }
          }
        }
      }
    }
  }
  return master_ladder;
}
