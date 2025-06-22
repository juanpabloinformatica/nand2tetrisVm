#include "CodeWritter.hpp"
#include "Utilities.hpp"
#include <array>
#include <regex>

CodeWritter::CodeWritter() {
  this->setPopAssemblyTemplate();
  this->setPushAssemblyTemplate();
  this->setArithmeticAssemblyTemplate();
  this->labelCounter = 0;
}
string CodeWritter::newPushAssembly(string memorySegment,
                                    int memorySegmentIndex, int var1) {

  /*
   * [
   * @##index##
   * D=A
   * ]
   * [
   * @##index##
   * D=A
   * @13
   * M=0
   * (LOOP##labelCounter##)
   * @13
   * M=M-1
   * D=D-1
   * @LOOP##labelCounter##
   * D;JGT
   * @13
   * D=M
   * ]
   * [
   * @##m_s##
   * A=M+D
   * D=M
   * ]
   * @0
   * A=M
   * M=D
   * @0
   * M=M+1
   * */
  string pushAssemblyInstance = std::string(this->pushAssemblyTemplate);
  if (memorySegmentIndex >= 0) {
    std::regex regexOpenDelimeter = std::regex(R"(\[\n)");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexOpenDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex regexCloseDelimeter = std::regex(R"(\n\])");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexCloseDelimeter, "",
                           std::regex_constants::format_first_only);

    std::regex indexRegex = std::regex(R"(\#\#index\#\#)");
    pushAssemblyInstance = std::regex_replace(
        pushAssemblyInstance, indexRegex, std::to_string(memorySegmentIndex));

    std::regex regexDelimeter = std::regex(R"(\[(\n|.*)*?\]\n)");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexDelimeter, "",
                           std::regex_constants::format_first_only);

    /*
     *
     * @memorySegmentIndex
     * D=A
     * [
     * @##m_s##
     * A=M+D
     * D=M
     * ]
     * @0
     * A=M
     * M=D
     * @0
     * M=M+1
     * */
  } else {
    // std::cout << pushAssemblyInstance << std::endl;
    std::regex var1Regex = std::regex(R"(\#\#var1\#\#)");
    pushAssemblyInstance = std::regex_replace(pushAssemblyInstance, var1Regex,
                                              std::to_string(var1));
    std::regex regexDelimeter = std::regex(R"(\[\n@##index##\nD=A\n\]\n)");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex regexOpenDelimeter = std::regex(R"(\[)");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexOpenDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex regexCloseDelimeter = std::regex(R"(\n\])");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexCloseDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex indexRegex = std::regex(R"(\#\#index\#\#)");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, indexRegex,
                           std::to_string(-1 * memorySegmentIndex));

    std::regex labelCounterRegex = std::regex(R"(\#\#labelCounter\#\#)");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, labelCounterRegex,
                           std::to_string(this->labelCounter));
    this->labelCounter++;
    // std::cout << pushAssemblyInstance << std::endl;

    /*
     * @index
     * D=A
     * @13
     * M=0
     * (LOOPlabelCounter)
     * @13
     * M=M-1
     * D=D-1
     * @LOOPlabelCounter
     * D;JGT
     * @13
     * D=M
     * [
     * @##m_s##
     * A=M+D
     * D=M
     * ]
     * @0
     * A=M
     * M=D
     * @0
     * M=M+1
     * */
  }
  if (memorySegment == "constant") {
    std::cout << "Entering in CONSTANT" << std::endl;
    // std::cout << "here 2" << std::endl;
    std::regex regexDelimeter = std::regex(R"(\[(\n|.)*\]\n)");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexDelimeter, "",
                           std::regex_constants::format_first_only);
  } else {
    /*
     *
     * @memorySegmentIndex
     * D=A
     * [
     * @##m_s##
     * [
     * A=M+D
     * D=M
     * ]
     * [
     * D=M+D
     * ]
     * ]
     * @0
     * A=M
     * M=D
     * @0
     * M=M+1
     * */
    std::regex firstDelimeterRegex = std::regex(R"(\[\n)");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, firstDelimeterRegex, "",
                           std::regex_constants::format_first_only);
    // std::regex regexCloseDelimeter = std::regex(R"(\n\])");
    // pushAssemblyInstance =
    //     std::regex_replace(pushAssemblyInstance, regexCloseDelimeter, "",
    //                        std::regex_constants::format_first_only);
    if (memorySegment == "pointer" || memorySegment == "temp" ||
        memorySegment == "static") {
      std::cout << "IN:  POINTER | TEMP | STATIC " << std::endl;
      std::regex referencedRegex = std::regex(R"(\[\nA=M\+D\nD=M\n\]\n)");
      pushAssemblyInstance =
          std::regex_replace(pushAssemblyInstance, referencedRegex, "",
                             std::regex_constants::format_first_only);
      std::regex regexOpenDelimeter = std::regex(R"(\[\n)");
      pushAssemblyInstance =
          std::regex_replace(pushAssemblyInstance, regexOpenDelimeter, "",
                             std::regex_constants::format_first_only);
      std::regex cleanRegex = std::regex(R"(D\n\]\n\]\n)");
      // std::regex regexCloseDelimeter = std::regex(R"(\n\])");
      pushAssemblyInstance =
          std::regex_replace(pushAssemblyInstance, cleanRegex, "D\n",
                             std::regex_constants::format_first_only);
      /*
       * @memorySegmentIndex
       * D=A
       * @##m_s##
       * D=M+D
       * @0
       * A=M
       * M=D
       * @0
       * M=M+1
       *
       * */
    } else {
      /*
       *
       * @memorySegmentIndex
       * D=A
       * [
       * @##m_s##
       * [
       * A=M+D
       * D=M
       * ]
       * [
       * D=M+D
       * ]
       * ]
       * @0
       * A=M
       * M=D
       * @0
       * M=M+1
       * */
      std::cout << "IN NOT :  POINTER | TEMP | STATIC " << std::endl;
      std::regex regexOpenDelimeter = std::regex(R"(\[\n)");
      pushAssemblyInstance =
          std::regex_replace(pushAssemblyInstance, regexOpenDelimeter, "",
                             std::regex_constants::format_first_only);
      std::regex referencedRegex = std::regex(R"(\]\n\[\nD=M\+D\n\]\n\]\n)");
      pushAssemblyInstance =
          std::regex_replace(pushAssemblyInstance, referencedRegex, "",
                             std::regex_constants::format_first_only);
      std::regex memorySegmentIndexRegex = std::regex(R"(\#\#index\#\#)");
      pushAssemblyInstance =
          std::regex_replace(pushAssemblyInstance, memorySegmentIndexRegex,
                             std::to_string(memorySegmentIndex));
    }
    std::regex memorySegmentRegex = std::regex(R"(\#\#m_s\#\#)");
    pushAssemblyInstance = std::regex_replace(
        pushAssemblyInstance, memorySegmentRegex,
        std::to_string(Utility::memorySegmentMap[memorySegment]));
    // std::regex memorySegmentIndexRegex = std::regex(R"(\#\#index\#\#)");
    // pushAssemblyInstance =
    //     std::regex_replace(pushAssemblyInstance, memorySegmentIndexRegex,
    //                        std::to_string(memorySegmentIndex ));
  }
  return pushAssemblyInstance;
}
string CodeWritter::getPushAssembly(string segment, int index, int var1) {
  return newPushAssembly(segment, index, var1);
}
// i need the string in here for do that condition
string CodeWritter ::newPopAssembly(string memorySegment,
                                    int memorySegmentIndex, int var1,
                                    int var2) {

  std::regex arg1Regex = std::regex(R"(\#\#arg1\#\#)");
  std::regex arg2Regex = std::regex(R"(\#\#arg2\#\#)");
  std::regex var1Regex = std::regex(R"(\#\#var1\#\#)");
  std::regex var2Regex = std::regex(R"(\#\#var2\#\#)");
  string popAssemblyInstance = string(this->popAssemblyTemplate);
  popAssemblyInstance = std::regex_replace(
      popAssemblyInstance, arg1Regex,
      std::to_string(Utility::memorySegmentMap[memorySegment]));
  popAssemblyInstance = std::regex_replace(popAssemblyInstance, arg2Regex,
                                           std::to_string(memorySegmentIndex));
  popAssemblyInstance =
      std::regex_replace(popAssemblyInstance, var1Regex, std::to_string(var1));
  popAssemblyInstance =
      std::regex_replace(popAssemblyInstance, var2Regex, std::to_string(var2));

  if (memorySegment == "pointer" || memorySegment == "temp" ||
      memorySegment == "static") {
    std::cout << "IN:  POINTER | TEMP | STATIC " << std::endl;

    // this case i send that weird value
    // that I will change eventually
    // so impotant thing here will be
    // I sent the value when is pointer or temp or static
    // so in those cases I don't need to do D=M+D but D=A+D

    std::regex openDelimeter = std::regex(R"(\n\[)");
    popAssemblyInstance =
        std::regex_replace(popAssemblyInstance, openDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex closeDelimeter = std::regex(R"(\n\])");
    popAssemblyInstance =
        std::regex_replace(popAssemblyInstance, closeDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex dynamicRegex = std::regex(R"(\[\nD=M\+D\n\])");
    popAssemblyInstance =
        std::regex_replace(popAssemblyInstance, dynamicRegex, "",
                           std::regex_constants::format_first_only);

    // std::cout << popAssemblyInstance << std::endl;

  } else {
    std::cout << "IN NOT:  POINTER | TEMP | STATIC " << std::endl;
    std::regex dynamicRegex = std::regex(R"(\n\[\nA=A\+D\nD=A\n\])");
    popAssemblyInstance =
        std::regex_replace(popAssemblyInstance, dynamicRegex, "",
                           std::regex_constants::format_first_only);
    std::regex openDelimeter = std::regex(R"(\n\[)");
    popAssemblyInstance =
        std::regex_replace(popAssemblyInstance, openDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex closeDelimeter = std::regex(R"(\n\])");
    popAssemblyInstance =
        std::regex_replace(popAssemblyInstance, closeDelimeter, "",
                           std::regex_constants::format_first_only);
    // std::cout << popAssemblyInstance << std::endl;
  }

  // std::cout << "Checking search and replace with regex" << std::endl
  //           << popAssemblyInstance << std::endl;

  return popAssemblyInstance;
}
string CodeWritter::getPopAssembly(string memorySegmentIndex, int index,
                                   int var1, int var2) {
  return newPopAssembly(memorySegmentIndex, index, var1, var2);
}
string CodeWritter::newArithmeticAssembly(string arithmeticType) {
  string popArithmeticInstance = string(this->arithmeticAssemblyTemplate);
  if (arithmeticType == "neg" || arithmeticType == "not") {
    std::regex regexDelimeter = std::regex(R"(\n\[\n@0\nM=M-1\n\])");
    std::regex_replace(popArithmeticInstance, regexDelimeter, "");
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexDelimeter, "");
    std::cout << popArithmeticInstance << std::endl;
  } else {

    std::regex regexOpenDelimeter = std::regex(R"(\[\n)");
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexOpenDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex regexCloseDelimeter = std::regex(R"(\n\])");
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexCloseDelimeter, "",
                           std::regex_constants::format_first_only);
  }
  return popArithmeticInstance;
}
// string CodeWritter::cleanGpr() {
//   return std::string("@13") + "\n" + "M=0" + "\n" + "@14" + "\n" + "M=0" +
//          "\n" + "@15" + "\n" + "M=0" + "\n";
// }
string CodeWritter::getArithmeticAssembly(string arithmeticType) {
  return newArithmeticAssembly(arithmeticType);
}
/*
 *PUSH
 [
 @##index##
 D=A
 ]
 [
 @##index##
 D=A
 @13
 M=0
 (LOOP##labelCounter##)
 @13
 M=M-1
 D=D-1
 @LOOP##labelCounter##
 D;JGT
 @13
 D=M
 ]
 [
 @##m_s##
 [
 A=M+D
 D=M
 [
 [
 D=M+D
 ]
 ]
 @0
 A=M
 M=D
 @0
 M=M+1

 * */
void CodeWritter::setPushAssemblyTemplate(void) {
  this->pushAssemblyTemplate =
      std::string("[") + "\n" + std::string("@##index##") + "\n" + "D=A" +
      "\n" + "]" + "\n" + "[" + "\n" + "@##index##" + "\n" + +"D=A" + "\n" +
      +"@13" + "\n" + "M=0" + "\n" + "(LOOP##labelCounter##)" + "\n" + "@13" +
      "\n" + "M=M-1" + "\n" + "D=D-1" + "\n" + "@LOOP##labelCounter##" + "\n" +
      "D;JGT" + "\n" + "@13" + "\n" + "D=M" + "\n" + "]" + "\n" + "[" + "\n" +
      "@##m_s##" + "\n" + "[" + "\n" + "A=M+D" + "\n" + "D=M" + "\n" + "]" +
      "\n" + "[" + "\n" + "D=M+D" + "\n" + "]" +
      "\n"
      "]"
      "\n" +
      "@0" + "\n" + "A=M" + "\n" + "M=D" + "\n" + "@0" + "\n" + "M=M+1" + "\n";
}
/*
 * POP
 * @0
 * M=M-1
 * A=M
 * D=M
 * @##var1##
 * M=D
 * @##arg2##
 * D=A
 * @##arg1##
 * [
 * A=A+D
 * D=A
 * ]
 * [
 * D=M+D
 * ]
 * @##var2##
 * M=D
 * @##var1##
 * D=M
 * @##var2##
 * A=M
 * M=D
 * */
void CodeWritter::setPopAssemblyTemplate(void) {
  this->popAssemblyTemplate =
      std::string("@0") + "\n" + "M=M-1" + "\n" + "A=M" + "\n" + "D=M" + "\n" +
      "@##var1##" + "\n" + "M=D" + "\n" + "@##arg2##" + "\n" + "D=A" + "\n" +
      "@##arg1##" + "\n" + "[" + "\n" + "A=A+D" + "\n" + "D=A" + "\n" + "]" +
      "\n" + "[" + "\n" + "D=M+D" + "\n" + "]" + "\n" + "@##var2##" + "\n" +
      "M=D" + "\n" + "@##var1##" + "\n" + "D=M" + "\n" + "@##var2##" + "\n" +
      "A=M" + "\n" + "M=D" + "\n";
}
/*ARITHMETIC
 * @0
 * M=M-1
 * [
 * @0
 * M=M-1
 * ]
 * */
void CodeWritter::setArithmeticAssemblyTemplate(void) {
  // this->arithmeticAssemblyTemplate =
  //     std::string("@0") + "\n" + "A=M-1" + "\n" + "M=0" + "\n" + "D=A" + "\n"
  //     + "D=D-1" + "\n" + "@16" + "\n" + "A=D" + "\n" + "M=0" + "\n" + "@0" +
  //     "\n" + "M=M-1" + "\n" + "@0" + "\n" + "M=M-1" + "\n";
  this->arithmeticAssemblyTemplate = std::string("@0") + "\n" + "M=M-1" + "\n" +
                                     "[" + "\n" + "@0" + "\n" + "M=M-1" + "\n" +
                                     "]";
}
