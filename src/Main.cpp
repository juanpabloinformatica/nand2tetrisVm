#include "CodeWritter.hpp"
#include "TestParser.hpp"
int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout
        << "Remember passing second argument, the file vm file to be translater"
        << endl;
    return EXIT_FAILURE;
  }
  string filename = argv[1];
  Control c = Control(filename);
  c.traverseFile();
  // t' = push constant 3
  // t''' = push constant -3
  // t''' = push arg 3
  // CodeWritter cw = CodeWritter();
  // cw.getPushAssembly("constant", 3);
  // cout << cw.getPushAssembly("argument", 2) << endl;
}
