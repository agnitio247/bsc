#include <iostream>
#include <string>

#define SEPERATOR '/'

using namespace std;

#include "../include/Backup.h"
#include "../include/Functions.h"

int main(int argc, char const *argv[]) {
  if (Backup("/home/alex/Documents/git/bsc/test.txt", "/home/alex/Documents/Backup") == 0) {
    cout << "Done" << endl;
  } else {
    cout << "Something went wrong" << endl;
  }
  return 0;
}
