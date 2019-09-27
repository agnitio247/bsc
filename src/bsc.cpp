#include <iostream>
#include <string>
#include <sys/stat.h>

using namespace std;

#include "../include/Backup.h"
#include "../include/Functions.h"

int main(int argc, char const *argv[]) {
  string source = "C:\\Users\\asylv\\Documents";
  string dest = "C:\\Users\\asylv\\Desktop";
  if (Backup(source, dest, true) == 0) {
    cout << "Backup successful" << endl;
  } else {
    cout << "an error occured" << endl;
  }
  return 0;
}
