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

int Backup(string source, string dest) {
  string output;
  output.append(dest);
  output.append(SEPERATOR);
  output.append(Split(source, SEPERATOR[0], -1));
  if (IsDir(source)) {
#ifdef _WIN32
    _mkdir(output.c_str());
#else
    mkdir(output.c_str(), 0700);
#endif
  } else if (IsFile(source)) {
    return Copy(source, output);
  }
  return 0;
}
