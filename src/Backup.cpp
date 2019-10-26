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
  #include <windows.h>
#endif

int Copy(string source, string dest)  {
  ifstream src(source, ios::binary);
  ofstream dst(dest, ios::binary);
  dst << src.rdbuf();
  return 0;
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
    } else if (IsFile(newSource) && !CompareFiles(newSource, newDest)) {
#ifdef __linux__
      Copy(newSource, newDest);
#endif
#ifdef _WIN32
      CopyFile(newSource.c_str(), newDest.c_str(), FALSE);
#endif
      if (verbose) {
        cout << "[ " << source << " ]" << "\t";
        cout << Split(newSource, SEPERATOR[0], -1) << endl;
      }
    }
  }
  delete[] dirContent;
  delete files;
  delete dirs;
  return 0;
}
