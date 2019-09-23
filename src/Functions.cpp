#include <iostream>
#include <string>

using namespace std;

const char* split(const char* input, char seperator, int id) {
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
