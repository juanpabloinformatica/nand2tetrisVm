#include "CodeWritter.hpp"

// void CodeWritter::writeArithmetic(string command) {}
CodeWritter::CodeWritter() {
  this->setPopAssemblyTemplate();
  this->setPushAssemblyTemplate();
  this->setArithmeticAssemblyTemplate();
}
string CodeWritter::newPushAssembly(string memorySegment,
                                    int memorySegmentIndex) {
  // i will improve this code
  string pushAssemblyInstance = "";
  if (Utility::memorySegmentMap.at(memorySegment) == M_S_CONSTANT) {
    pushAssemblyInstance = string(this->pushAssemblyTemplate);
    std::cout << this->pushAssemblyTemplate << std::endl;
    // I will organize this code after
    int indexOpenDelimeter = pushAssemblyInstance.find("[");
    int indexEndDelimeter = pushAssemblyInstance.find("]");
    pushAssemblyInstance =
        pushAssemblyInstance.substr(0, indexOpenDelimeter - 1);
    pushAssemblyInstance += this->pushAssemblyTemplate.substr(
        indexEndDelimeter + 1,
        this->pushAssemblyTemplate.length() - indexEndDelimeter);
    int templateVarLength = string("##index##").length();
    int indexTemplateVar = pushAssemblyTemplate.find("#");
    pushAssemblyInstance.replace(indexTemplateVar, templateVarLength,
                                 std::to_string(memorySegmentIndex));

  } else {

  }
  std::cout << pushAssemblyInstance << std::endl;
  exit(EXIT_SUCCESS);
  return pushAssemblyInstance;
}
string CodeWritter::getPushAssembly(string memorySegment,
                                    int memorySegmentIndex) {
  // int memorySegmentValue = Utility::memorySegmentMap.at(memorySegment);
  return newPushAssembly(memorySegment, memorySegmentIndex);

  // string interpolation_1 = "##@##";
  // int index_interpolation_1 =
  // this->pushAssemblyTemplate.find(interpolation_1);
  // this->pushAssemblyTemplate.replace(index_interpolation_1,
  //                                    interpolation_1.length(),
  //                                    std::to_string(memorySegmentValue));

  return "";
}
string CodeWritter::getPopAssembly(string memorySegmentIndex, int index) {
  return "";
}
string CodeWritter::getArithmeticAssembly(string operation) { return ""; }

void CodeWritter::setPushAssemblyTemplate(void) {
  this->pushAssemblyTemplate =
      std::string("@##index##") + "\n" + "D=A" + "\n" + "[" +
      "\n"
      "@##m_s##" +
      "\n" + "A=M+D" + "\n" + "D=M" + "\n" +
      "]"
      "\n" +
      "@0" + "\n" + "A=M" + "\n" + "M=D" + "\n" + "@0" + "\n" + "M=M+1" + "\n";
  // this->pushAssemblyTemplate = "{}{}\nD=A\n@0\nA=M\nM=D\n@0\nM=M+1\n";
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
  this->arithmeticAssemblyTemplate =
      std::string("@0") + "\n" + "A=M-1" + "\n" + "M=0" + "\n" + "D=A" + "\n" +
      "D=D-1" + "\n" + "@16" + "\n" + "A=D" + "\n" + "M=0" + "\n" + "@0" +
      "\n" + "M=M-1" + "\n" + "@0" + "\n" + "M=M-1" + "\n";
}
