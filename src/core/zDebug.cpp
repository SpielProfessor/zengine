#include "zDebug.hpp"
std::vector<std::string> splitByWhitespace(const std::string &input) {
  std::istringstream iss(input);
  std::vector<std::string> result;
  std::string word;

  while (iss >> word) {
    result.push_back(word);
  }

  return result;
}
