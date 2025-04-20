#include "MemoryManager.hpp"
#include "TestParser.hpp"
#include "Utilities.hpp"
int main(int argc, char *argv[]) {
   if (argc != 2) {
     return EXIT_FAILURE;
   }
   string filename = argv[1];
   testParser(filename);
  MemoryManager m = MemoryManager();
}
