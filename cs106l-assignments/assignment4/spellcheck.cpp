#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  Corpus tokenSet;
  auto tokenl=find_all(source.begin(), source.end(), 
  [](char c){ return std::isspace(static_cast<unsigned char>(c)); });
  auto tokenr=tokenl;
  tokenr.erase(tokenr.begin());
  tokenl.pop_back();
  std::transform(tokenl.begin(),tokenl.end(),tokenr.begin(),
    std::inserter(tokenSet,tokenSet.begin()),
    [&source](auto it1,auto it2){
      return Token(source,it1,it2);
    });
  std::erase_if(tokenSet,[](const Token &token){
    return token.content.contains(" ")||token.content.contains("\n")||token.content.size()==0;
  });
  return tokenSet;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv=std::ranges::views;
  auto result=source|
              rv::filter([&dictionary](const Token& token){
                return !dictionary.contains(token.content);
              })|
              rv::transform([&dictionary](const Token& token){
                auto view=dictionary|
                          rv::filter([&token](const std::string &dicToken){
                            return levenshtein(dicToken,token.content)==1;
                          });
                std::set<std::string> suggestions(view.begin(),view.end());
                return Misspelling{token,suggestions};
              })|
              rv::filter([](const Misspelling& token){
                return !token.suggestions.empty();
              });
  std::set<Misspelling>answer(result.begin(),result.end());
  return answer;
};

/* Helper methods */

#include "utils.cpp"