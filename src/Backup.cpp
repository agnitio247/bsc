#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>

using namespace std;

#include "../include/Backup.h"
#include "../include/Functions.h"
#include "../include/LinkedList.h"

#ifdef __linux__
  #define SEPERATOR "/"
#endif
#ifdef _WIN32
  #define SEPERATOR "\\"
  #include <direct.h>
#endif

int Copy(string source, string dest) {
  string line;
  ifstream inFile {source};
  ofstream outFile {dest};
  if (inFile && outFile) {
    while(getline(inFile, line)) {
      outFile << line << endl;
    }
    return 0;
  }
  return 1;
}

int Backup(string source, string dest, bool verbose) {
  string output = dest + SEPERATOR + Split(source, SEPERATOR[0], -1);
  if (IsDir(source)) {
#ifdef _WIN32
    _mkdir(output.c_str());
#else
    mkdir(output.c_str(), 0700);
#endif
  } else if (IsFile(source)) {
    return Copy(source, output);
  }
  linkedList *files = new linkedList();
  linkedList *dirs = new linkedList();
  int dirContentSize;
  string *dirContent = ListDir(source, &dirContentSize);
  string newSource, newDest;
  for (int i = 0; i < dirContentSize; i++) {
    newSource = source + SEPERATOR + dirContent[i];
    newDest = output + SEPERATOR + dirContent[i];
    if (IsDir(newSource)) {
      if (Backup(newSource, output, verbose) == 0) {
        continue;
      }
      return 1;
    } else if (IsFile(newSource)) {
      Copy(newSource, newDest);
      if (verbose == 1) {
        cout << newSource << endl;
      }
    }
  }
  return 0;
}
