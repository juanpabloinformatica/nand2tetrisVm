#include "CodeWritter.hpp"
#include "TestParser.hpp"
int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "Remember passing second argument, the file vm file to be "
            "translater "
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
  // std::cout << cw.getPushAssembly("local", 3, 13) << std::endl;
  // std::cout << cw.getPushAssembly("pointer", 3, 13) << std::endl;
  // std::cout <<;

  // std::cout << "CASE IS POINTER | TEMP | STATIC" << std::endl;
  // std::cout << cw.getPopAssembly(5, 6 + NOTREFMS, 13, 14) << std::endl;
  // std::cout << "CASE IS NOT POINTER | TEMP | STATIC" << std::endl;
  // std::cout << cw.getPopAssembly(0, 6, 13, 14) << std::endl;
  // cout << cw.getPushAssembly("argument", 2) << endl;
}
