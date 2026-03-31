/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <cstdlib>

std::string kYourName = "Ma Andy"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::unordered_set<std::string> get_applicants(std::string filename) {
  std::ifstream file(filename);
  std::string name;
  std::unordered_set<std::string> nameSet;
  while(getline(file,name,'\n')){
    nameSet.insert(name);
  }
  return nameSet;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::unordered_set<std::string>& students) {
  std::queue<const std::string*> matches;
  for(const auto &studentName:students){
    if(name[0]==studentName[0]&&name[name.find(' ')+1]==studentName[studentName.find(' ')+1]){
      matches.push(&studentName);
    }
  }
  return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  int siz=matches.size();
  if(siz==0)return "NO MATCHES FOUND.";
  srand(time(0));
  int numberToPop=random()%siz;
  for(int i=1;i<=numberToPop;i++)matches.pop();
  auto match=matches.back();
  return *match;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
