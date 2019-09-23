#include <iostream>
#include <string>

using namespace std;

#include "../include/Backup.h"
#include "../include/Functions.h"

int main(int argc, char const *argv[]) {
  Backup("test.txt", "test1.txt");
  return 0;
}
