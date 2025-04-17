#include "TestParser.hpp"
#include "Utilities.hpp"
#include <string>
int main(int argc, char *argv[]) {
  if (argc != 2) {
    return EXIT_FAILURE;
  }
  string filename = argv[1];
  Utility::setMapCArithmetic();
  testParser(filename);
}
