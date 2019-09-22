#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

#include "../include/Backup.h"

#ifdef __linux__
  #define SEPERATOR "/"
#endif
#ifdef _WIN32
  #define SEPERATOR "\\"
#endif

int copy(const char* source, const char* dest) {
  int seperatorCount = 0;
  for (int i = 0; i < source.size(); i++) {
    if (source[i] == SEPERATOR) {
      seperatorCount ++;
    }
  }
  path sourceFilePath(source);
  path destFilePath(dest);
  if (is_directory(sourceFilePath) && !exists(destFilePath)) {
#ifdef _WIN32
    _mkdir(outputDir);
#else
    mkdir(outputDir, 0777);
#endif
  } else if (is_regular_file(sourceFilePath)) {

  }

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
  return 0;
}
