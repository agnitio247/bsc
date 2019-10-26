#include <iostream>
#include <string>
#include <sys/stat.h>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

#include "../include/LinkedList.h"

string Split(string input, char seperator, int id) {
  int inputLength = input.length();
  // get number of seperator in input string
  int seperatorCount = 0;
  for (int i = 0; i < inputLength; i++) {
    if (input[i] == seperator) {
      seperatorCount++;
    }
  }
  if (id < 0) {
    id = seperatorCount + 1 + id;
  }
  string output;
  for (int i = 0; i < inputLength; i++) {
    if (input[i] == seperator) {
      id -= 1;
      // if pass other seperator
      if (id < 0) {
        break;
      }
      continue;
    }
    // once at right place in string
    if (id == 0) {
      output.append(1, input[i]);
    }
  }
  return output;
}

bool IsDir(string path) {
  struct stat pathStat;
  stat(path.c_str(), &pathStat);
  if (S_ISDIR(pathStat.st_mode) == 0) {
    return false;
  } else {
    return true;
  }
}

bool IsFile(string path) {
  struct stat pathStat;
  stat(path.c_str(), &pathStat);
  if (S_ISREG(pathStat.st_mode) == 0) {
    return false;
  } else {
    return true;
  }
}

// TODO : fix mem leak
string* ListDir(string path, int *size) {
  linkedList *list = new linkedList();
  struct dirent *entry;
  DIR *dir = opendir(path.c_str());
  while ((entry = readdir(dir)) != NULL) {
    list->Add(entry->d_name);
  }
  list->RemoveValue("..");
  list->RemoveValue(".");
  string *output = new string[list->GetSize()];
  for (int i = 0; i < list->GetSize(); i++) {
    output[i] = list->GetValue(i);
  }
  *size = list->GetSize();
  closedir(dir);
  delete list;
  return output;
}

bool CompareFiles(string &p1, string &p2) {
  ifstream f1(p1, ifstream::binary|ifstream::ate);
  ifstream f2(p2, ifstream::binary|ifstream::ate);
  if (f1.fail() || f2.fail()) {
    return false; //file problem
  }
  if (f1.tellg() != f2.tellg()) {
    return false; //size mismatch
  }
  f1.seekg(0, ifstream::beg);
  f2.seekg(0, ifstream::beg);
  return equal(istreambuf_iterator<char>(f1.rdbuf()),
                    istreambuf_iterator<char>(),
                    istreambuf_iterator<char>(f2.rdbuf()));
}
