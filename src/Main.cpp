#include "CodeWritter.hpp"
#include "TestParser.hpp"
int main(int argc, char* argv[]) {
  if (argc != 2) {
      cout << "Remember passing second argument, the file vm file to be "
              "translater "
           << endl;
      return EXIT_FAILURE;
  }
  string filename = argv[1];
  Control c       = Control (filename);
  c.traverseFile ();
  // t' = push constant 3
  // t''' = push constant -3
  // t''' = push arg 3
  // CodeWritter cw = CodeWritter();

  // std::cout << cw.getArithmeticAssembly("not") << std::endl;
  // std::cout << cw.getArithmeticAssembly("neg") << std::endl;
  // std::cout << cw.getArithmeticAssembly("lt") << std::endl;
  //
  // std::cout << cw.getWriteIfTemplate("LOOP")<<std::endl;
  // std::cout << cw.getWriteGotoTemplate("LOOP")<<std::endl;

  // std::cout << "RUNNING EQ:"<< std::endl;
  // std::cout << cw.getArithmeticAssembly("eq") << std::endl;
  // std::cout << "RUNNING GT:"<< std::endl;
  // std::cout << cw.getArithmeticAssembly("gt") << std::endl;
  // std::cout << "RUNNING LT:"<< std::endl;
  // std::cout << cw.getArithmeticAssembly("lt") << std::endl;
  // std::cout <<;

  // std::cout << "CASE IS POINTER | TEMP | STATIC" << std::endl;
  // std::cout << cw.getPopAssembly(5, 6 + NOTREFMS, 13, 14) << std::endl;
  // std::cout << "CASE IS NOT POINTER | TEMP | STATIC" << std::endl;
  // std::cout << cw.getPopAssembly(0, 6, 13, 14) << std::endl;
  // cout << cw.getPushAssembly("argument", 2) << endl;
}
