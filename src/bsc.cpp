#include <iostream>
#include <string>
#include <sys/stat.h>

using namespace std;

#include "../include/Backup.h"
#include "../include/Functions.h"

int main(int argc, char const *argv[]) {
  int size;
  string* dirContent = ListDir("/home/alex/Documents", &size);
  for (int i = 0; i < size; i++) {
    cout << dirContent[i] << endl;
  }
  return 0;
}
