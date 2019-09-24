#include <iostream>
#include <string>

using namespace std;

#include "../include/Backup.h"
#include "../include/Functions.h"

int main(int argc, char const *argv[]) {
  if (Backup("/home/alex/Documents/git", "/home/alex/Documents/Backup"))
  return 0;
}
