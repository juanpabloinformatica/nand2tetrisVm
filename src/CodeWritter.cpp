#include "CodeWritter.hpp"
#include <array>
#include <regex>

// using std::cout;
// using std::endl;
// void CodeWritter::writeArithmetic(string command) {}
CodeWritter::CodeWritter() {
  this->setPopAssemblyTemplate();
  this->setPushAssemblyTemplate();
  this->setArithmeticAssemblyTemplate();
  this->labelCounter = 0;
}
string CodeWritter::newPushAssembly(string memorySegment,
                                    int memorySegmentIndex) {
  string pushAssemblyInstance = std::string(this->pushAssemblyTemplate);
  if (memorySegmentIndex >= 0) {
    std::regex regexOpenDelimeter = std::regex("\\[\\n");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexOpenDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex regexCloseDelimeter = std::regex("\\n\\]");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexCloseDelimeter, "",
                           std::regex_constants::format_first_only);
    // std::regex regexDelimeter = std::regex("\\[(\\n.*)*\\]\\n");
    std::regex regexDelimeter =
        std::regex("\\n\\[\\n@##index##\\nD=A\\n@16\\nM=0\\n\\(LOOP\\)\\n@"
                   "16\\nM=M-1\\nD=D-1\\n@LOOP\\nD;JGT\\n@16\\nD=M\\n\\]");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex indexRegex = std::regex("\\#\\#index\\#\\#");
    pushAssemblyInstance = std::regex_replace(
        pushAssemblyInstance, indexRegex, std::to_string(memorySegmentIndex));
  } else {
    // std::cout << pushAssemblyInstance << std::endl;
    std::regex regexDelimeter = std::regex("\\[\\n@##index##\\nD=A\\n\\]\\n");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex regexOpenDelimeter = std::regex("\\[");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexOpenDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex regexCloseDelimeter = std::regex("\\n\\]");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexCloseDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex indexRegex = std::regex("\\#\\#index\\#\\#");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, indexRegex,
                           std::to_string(-1 * memorySegmentIndex));

    std::regex labelCounterRegex = std::regex("\\#\\#labelCounter\\#\\#");
    pushAssemblyInstance = std::regex_replace(
        pushAssemblyInstance, labelCounterRegex, std::to_string(this->labelCounter));
    this->labelCounter++;
    // std::cout << pushAssemblyInstance << std::endl;
  }
  if (Utility::memorySegmentMap.at(memorySegment) == M_S_CONSTANT) {
    // std::cout << "here 2" << std::endl;
    std::regex regexDelimeter = std::regex("\\[(\\n.*)*\\]\\n");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex indexRegex = std::regex("\\#\\#index\\#\\#");
    pushAssemblyInstance = std::regex_replace(
        pushAssemblyInstance, indexRegex, std::to_string(memorySegmentIndex));
    // std::cout << pushAssemblyInstance << std::endl;
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
string CodeWritter::newArithmeticAssembly(string arithmeticType) {
  string popArithmeticInstance = string(this->arithmeticAssemblyTemplate);
  if (arithmeticType == "neg" || arithmeticType == "not") {
    std::cout << "****** type ****" << std::endl;
    std::cout << "****** " << arithmeticType << "****" << std::endl;
    std::regex regexDelimeter = std::regex("\\n\\[\\n@0\nM=M-1\\n\\]");
    std::regex_replace(popArithmeticInstance, regexDelimeter, "");
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexDelimeter, "");
    std::cout << popArithmeticInstance << std::endl;
  } else {
    std::regex regexOpenDelimeter = std::regex("\\[\\n");
    std::regex_replace(popArithmeticInstance, regexOpenDelimeter, "");
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexOpenDelimeter, "");
    std::regex regexCloseDelimeter = std::regex("\\n\\]");
    std::regex_replace(popArithmeticInstance, regexCloseDelimeter, "");
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexCloseDelimeter, "");
  }
  return popArithmeticInstance;
}
string CodeWritter::getArithmeticAssembly(string arithmeticType) {
  return newArithmeticAssembly(arithmeticType);
}

void CodeWritter::setPushAssemblyTemplate(void) {
  this->pushAssemblyTemplate =
      std::string("[") + "\n" + std::string("@##index##") + "\n" + "D=A" +
      "\n" + "]" + "\n" + "[" + "\n" + "@##index##" + "\n" + +"D=A" + "\n" +
      +"@16" + "\n" + "M=0" + "\n" + "(LOOP##labelCounter##)" + "\n" + "@16" +
      "\n" + "M=M-1" + "\n" + "D=D-1" + "\n" + "@LOOP##labelCounter##" + "\n" +
      "D;JGT" + "\n" + "@16" + "\n" + "D=M" + "\n" + "]" + "\n" + "[" + "\n" +
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
  // this->arithmeticAssemblyTemplate =
  //     std::string("@0") + "\n" + "A=M-1" + "\n" + "M=0" + "\n" + "D=A" + "\n"
  //     + "D=D-1" + "\n" + "@16" + "\n" + "A=D" + "\n" + "M=0" + "\n" + "@0" +
  //     "\n" + "M=M-1" + "\n" + "@0" + "\n" + "M=M-1" + "\n";
  this->arithmeticAssemblyTemplate = std::string("@0") + "\n" + "M=M-1" + "\n" +
                                     "[" + "\n" + "@0" + "\n" + "M=M-1" + "\n" +
                                     "]";
}
