#include "CodeWritter.hpp"
#include <regex>

// using std::cout;
// using std::endl;
// void CodeWritter::writeArithmetic(string command) {}
CodeWritter::CodeWritter() {
  this->setPopAssemblyTemplate();
  this->setPushAssemblyTemplate();
  this->setArithmeticAssemblyTemplate();
}
string CodeWritter::newPushAssembly(string memorySegment,
                                    int memorySegmentIndex) {

  string pushAssemblyInstance = std::string(this->pushAssemblyTemplate);
  if (Utility::memorySegmentMap.at(memorySegment) == M_S_CONSTANT) {
    std::regex regexDelimeter = std::regex("\\[(\\n.*)*\\]\\n");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexDelimeter, "");
    std::regex indexRegex = std::regex("\\#\\#index\\#\\#");
    pushAssemblyInstance = std::regex_replace(
        pushAssemblyInstance, indexRegex, std::to_string(memorySegmentIndex));
  } else {
    std::regex regexDelimeter = std::regex("\\[\\n|\\n\\]");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexDelimeter, "");
    std::regex memorySegmentRegex = std::regex("##m_s##");
    pushAssemblyInstance = std::regex_replace(
        pushAssemblyInstance, memorySegmentRegex,
        std::to_string(Utility::memorySegmentMap.at(memorySegment)));
    std::regex memorySegmentIndexRegex = std::regex("##index##");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, memorySegmentIndexRegex,
                           std::to_string(memorySegmentIndex));
  }
  return pushAssemblyInstance;
}
string CodeWritter::getPushAssembly(string memorySegment,
                                    int memorySegmentIndex) {
  return newPushAssembly(memorySegment, memorySegmentIndex);
}
string CodeWritter ::newPopAssembly(string memorySegment,
                                    int memorySegmentIndex) {

  std::regex arg1Regex = std::regex("\\#\\#arg1\\#\\#");
  std::regex arg2Regex = std::regex("\\#\\#arg2\\#\\#");
  std::regex var1Regex = std::regex("\\#\\#var1\\#\\#");
  std::regex var2Regex = std::regex("\\#\\#var2\\#\\#");
  string popAssemblyInstance = string(this->popAssemblyTemplate);
  popAssemblyInstance =
      std::regex_replace(popAssemblyInstance, arg1Regex, memorySegment);
  popAssemblyInstance = std::regex_replace(popAssemblyInstance, arg2Regex,
                                           std::to_string(memorySegmentIndex));
  popAssemblyInstance =
      std::regex_replace(popAssemblyInstance, var1Regex, std::to_string(16));
  popAssemblyInstance =
      std::regex_replace(popAssemblyInstance, var2Regex, std::to_string(17));

  std::cout << "Checking search and replace with regex" << std::endl
            << popAssemblyInstance << std::endl;

  return popAssemblyInstance;
}
string CodeWritter::getPopAssembly(string memorySegmentIndex, int index) {
  return newPopAssembly(memorySegmentIndex, index);
}
string CodeWritter::newArithmeticAssembly() {
  return std::string(this->arithmeticAssemblyTemplate);
}
string CodeWritter::getArithmeticAssembly() { return newArithmeticAssembly(); }

void CodeWritter::setPushAssemblyTemplate(void) {
  this->pushAssemblyTemplate =
      std::string("@##index##") + "\n" + "D=A" + "\n" + "[" + "\n" +
      "@##m_s##" + "\n" + "A=M+D" + "\n" + "D=M" + "\n" +
      "]"
      "\n" +
      "@0" + "\n" + "A=M" + "\n" + "M=D" + "\n" + "@0" + "\n" + "M=M+1" + "\n";
}
void CodeWritter::setPopAssemblyTemplate(void) {
  this->popAssemblyTemplate =
      std::string("@0") + "\n" + "M=M+1" + "\n" + "A=M" + "\n" + "D=M" + "\n" +
      "@##var1##" + "\n" + "M=D" + "\n" + "@##arg2##" + "\n" + "D=A" + "\n" +
      "@##arg1##" + "\n" + "D=M+D" + "\n" + "@##var2##" + "\n" + "M=D" + "\n" +
      "@##var1##" + "\n" + "D=M" + "\n" + "@##var2##" + "\n" + "A=M" + "\n" +
      "M=D" + "\n";
}
void CodeWritter::setArithmeticAssemblyTemplate(void) {
  this->arithmeticAssemblyTemplate =
      std::string("@0") + "\n" + "A=M-1" + "\n" + "M=0" + "\n" + "D=A" + "\n" +
      "D=D-1" + "\n" + "@16" + "\n" + "A=D" + "\n" + "M=0" + "\n" + "@0" +
      "\n" + "M=M-1" + "\n" + "@0" + "\n" + "M=M-1" + "\n";
}
