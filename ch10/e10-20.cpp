#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

std::string make_plural(size_t ctr, const std::string &word,
                        const std::string &ending = "s") {
  return (ctr > 1) ? word + ending : word;
}

void elimDups(std::vector<std::string> &words) {
  std::sort(words.begin(), words.end());
  auto end_unique = std::unique(words.begin(), words.end());
  words.erase(end_unique, words.end());
}

void biggies(std::vector<std::string> words,  // use value instead of reference
             std::vector<std::string>::size_type sz) {
  elimDups(words);
  auto iter = std::partition(words.begin(), words.end(),
      [sz](const std::string &s) { return s.size() >= sz; });
  //auto count = iter - words.begin();
  auto count = std::count_if(words.begin(), words.end(),
      [sz](const std::string &s) { return s.size() >= sz; });
  std::cout << count << " " << make_plural(count, "word") << " of length "
            << sz << " or longer." << std::endl;
  std::for_each(words.begin(), iter,
      [](const std::string &s) { std::cout << s << " "; });
}

int main() {
  std::vector<std::string> words;
  for (std::string s; std::cin >> s; words.push_back(s)) {}
  biggies(words, 6);

  return 0;
}