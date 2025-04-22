#include "CodeWritter.hpp"

// void CodeWritter::writeArithmetic(string command) {}
CodeWritter::CodeWritter() {}
// void CodeWritter::setWriteFile(string fileName) {
//   string filepath = Utility::getFilepath(fileName);
//   this->writeFile = ofstream(filepath);
// }
string CodeWritter::getPushAssembly(COMMAND_TYPE commandType, string segment,
                                    int index) {

  int type = -1;
  if (segment == "local") {
    type = 1;
  } else if (segment == "argument") {
    type = 2;
  } else if (segment == "this") {
    type = 3;
  } else if (segment == "that") {
    type = 4;
  }
  string pushAssembly = "@" + std::to_string(index) + "\n" + "D=A" + "\n" +
                        "@" + std::to_string();

  return pushAssembly;
}
// i am writting slower because I am trying to get use to new things such as
// using <C-[> instead of jj i am using tricks in insert mode
