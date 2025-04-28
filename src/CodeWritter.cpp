#include "CodeWritter.hpp"
#include <regex>

using std::cout;
using std::endl;
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
  int indexOpenDelimeter = this->pushAssemblyTemplate.find("[");
  int indexEndDelimeter = this->pushAssemblyTemplate.find("]");
  if (Utility::memorySegmentMap.at(memorySegment) == M_S_CONSTANT) {
    //+1 for skipping the delimeter
    pushAssemblyInstance +=
        this->pushAssemblyTemplate.substr(0, indexOpenDelimeter - 1);
    pushAssemblyInstance += this->pushAssemblyTemplate.substr(
        indexEndDelimeter + 1,
        this->pushAssemblyTemplate.length() - indexEndDelimeter);
    int templateVarLength = string("##index##").length();
    int indexTemplateVar = pushAssemblyTemplate.find("#");
    pushAssemblyInstance.replace(indexTemplateVar, templateVarLength,
                                 std::to_string(memorySegmentIndex));
  } else {
    //+1 for skipping the delimeter
    pushAssemblyInstance +=
        this->pushAssemblyTemplate.substr(0, indexOpenDelimeter);
    // std::cout << "First delimeter else" << std::endl;
    // std::cout << pushAssemblyInstance << std::endl;
    // i add +2 because I want to skipp delimeter(]) + /n
    // the diff between indexEnd and indexOpen
    // will give the #units or chars between that interval
    // but as we decalate the start position 2 units it will give 2 extra
    // chars
    // -one is also situated to skip \n before delimeter
    pushAssemblyInstance += this->pushAssemblyTemplate.substr(
        indexOpenDelimeter + 2,
        (indexEndDelimeter - indexOpenDelimeter) -
            3); //
                // i wil do this with regex instead

    pushAssemblyInstance += this->pushAssemblyTemplate.substr(
        indexEndDelimeter + 1,
        this->pushAssemblyTemplate.length() - indexEndDelimeter - 1);
    int templateVarLength = string("##index##").length();
    int indexTemplateVar = pushAssemblyTemplate.find("#");
    pushAssemblyInstance.replace(indexTemplateVar, templateVarLength,
                                 std::to_string(memorySegmentIndex));
    templateVarLength = string("##m_s##").length();
    indexTemplateVar = pushAssemblyInstance.find("#");
    pushAssemblyInstance.replace(
        indexTemplateVar, templateVarLength,
        std::to_string(Utility::memorySegmentMap.at(memorySegment)));
  }
  return pushAssemblyInstance;
}
// string CodeWritter::newPushAssembly(string memorySegment,
//                                     int memorySegmentIndex) {
//
//   string pushAssemblyInstance = std::string(this->pushAssemblyTemplate);
//   if (Utility::memorySegmentMap.at(memorySegment) == M_S_CONSTANT) {
//     cout << "in here" << endl;
//     std::regex regexDelimeter = std::regex("\\[(\\d|\\w|\\n)*\\]");
//     pushAssemblyInstance =
//         std::regex_replace(pushAssemblyInstance, regexDelimeter, "");
//     cout << pushAssemblyInstance << endl;
//   } else {
//   }
//   return pushAssemblyInstance;
// }
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
string CodeWritter::getArithmeticAssembly(string operation) { return ""; }

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
