#include "CodeWritter.hpp"

// void CodeWritter::writeArithmetic(string command) {}
CodeWritter::CodeWritter() {
  this->setPopAssemblyTemplate();
  this->setPushAssemblyTemplate();
} string CodeWritter::getPushAssembly(COMMAND_TYPE commandType, string segment,
                                    int index) {

  std::cout << "hello" << std::endl;
  string pushAssembly = "";
  if (segment == "constant") {
    pushAssembly += "@" + std::to_string(index) + "\n" + "D=A" + "\n" + "@0" +
                    "\n" + "A=M" + "\n" + "M=D" + "\n" + "@0" + "\n" + "M=M+1";
    return pushAssembly;
  }

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
  pushAssembly = "@" + std::to_string(index) + "\n" + "D=A" + "\n" + "@" +
                 std::to_string(type);

  return pushAssembly;
}

void CodeWritter::setPushAssemblyTemplate(void) {
  this->pushAssemblyTemplate = std::string("##@##") + "##index##" + "\n" +
                               "D=A" + "\n" + "@0" + "\n" + "A=M" + "\n" +
                               "M=D" + "\n" + "@0" + "\n" + "M=M+1" + "\n";
}
void CodeWritter::setPopAssemblyTemplate(void) {
  this->popAssemblyTemplate =
      std::string("@0") + "\n" + "M=M+1" + "\n" + "A=M" + "\n" + "D=M" + "\n" +
      "@##var1##" + "\n" + "M=D" + "\n" + "@##arg2##" + "\n" + "D=A" + "\n" +
      "@##arg1##" + "\n" + "D=M+D" + "\n" + "@##var2##" + "\n" + "M=D" + "\n" +
      "@##var1" + "\n" + "D=M" + "\n" + "@##var2##" + "\n" + "A=M" + "\n" +
      "M=D" + "\n";
}
void CodeWritter::setArithmeticAssemblyTemplate(void) {
  string add = "";
  string sub = "";
  string neg = "";
  string eq = "";
  string gt = "";
  string lt = "";
  string _and = "";
  string _or = "";
  string _not = "";
  this->arithmeticAssemblyTemplate = "";
}
// void CodeWritter::getArithmeticAssembly(string operation){
//   if(operation==)
// }
// i am writting slower because I am trying to get use to new things such as
// using <C-[> instead of jj i am using tricks in insert mode
