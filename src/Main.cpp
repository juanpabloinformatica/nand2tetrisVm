#include "CodeWritter.hpp"
#include "TestParser.hpp"
int main(int argc, char *argv[]) {
  // if (argc != 2) {
  //   cout
  //       << "Remember passing second argument, the file vm file to be
  //       translater"
  //       << endl;
  //   return EXIT_FAILURE;
  // }
  // string filename = argv[1];
  // Control c = Control(filename);
  // c.traverseFile();
  CodeWritter c = CodeWritter();
  c.getPushAssembly("constant", 5);
}
