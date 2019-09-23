#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>

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
  string line;
  ifstream inFile {source};
  ofstream outFile {dest};
  if (inFile && outFile) {
    while(getline(inFile, line)) {
      outFile << line << endl;
    }
  } else {
    return 1;
  }
}

int Backup(const char* source, const char* dest) {
  string output;
  output.append(dest);
  output.append(SEPERATOR);
  output.append(split(source, *SEPERATOR, -1));
  path sourceFilePath(source);
  path destFilePath(dest);
  if (is_directory(sourceFilePath) && !exists(destFilePath)) {
#ifdef _WIN32
    _mkdir(output);
#else
    mkdir(output, 0777);
#endif
  } else if (is_regular_file(sourceFilePath)) {
    Copy(source, output);
  }
  return 0;
}
