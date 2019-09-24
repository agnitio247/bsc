#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>

using namespace std;

#include "../include/Backup.h"
#include "../include/Functions.h"

#ifdef __linux__
  #define SEPERATOR "/"
#endif
#ifdef _WIN32
  #define SEPERATOR "\\"
#endif

int Copy(const char* source, const char* dest) {
  cout << dest << endl;
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

int Backup(const char* source, const char* dest) {
  string output;
  output.append(dest);
  output.append(SEPERATOR);
  output.append(Split(source, *SEPERATOR, -1));
  if (IsDir(source)) {
#ifdef _WIN32
    _mkdir(output.c_str());
#else
    mkdir(output.c_str(), 0700);
    cout << "created dir" << endl;
#endif
  } else if (IsFile(source)) {
    return Copy(source, output.c_str());
  }
  return 0;
}
