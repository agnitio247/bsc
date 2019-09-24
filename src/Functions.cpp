#include <iostream>
#include <string>
#include <sys/stat.h>

using namespace std;

const char* Split(const char* input, char seperator, int id) {
  int inputLength = 0;
  // get length of input string
  while (input[inputLength] != '\0') {
    inputLength++;
  }
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
  string tempOutput;
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
      tempOutput.append(1, input[i]);
    }
  }
  const char* output = tempOutput.c_str();
  return output;
}

bool IsDir(const char* path) {
  struct stat pathStat;
  stat(path, &pathStat);
  if (S_ISDIR(pathStat.st_mode) == 0) {
    return false;
  } else {
    return true;
  }
}

bool IsFile(const char* path) {
  struct stat pathStat;
  stat(path, &pathStat);
  if (S_ISREG(pathStat.st_mode) == 0) {
    return false;
  } else {
    return true;
  }
}
