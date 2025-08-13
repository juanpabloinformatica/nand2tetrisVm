#include "CodeWritter.hpp"
#include <array>
#include <iostream>
#include <regex>
#include "Utilities.hpp"

CodeWritter::CodeWritter() {
  this->setPopAssemblyTemplate();
  this->setPushAssemblyTemplate();
  this->setArithmeticAssemblyTemplate();
  // Adding init for branching
  this->setWriteLabelTemplate();
  this->setWriteGotoTemplate();
  this->setWriteIfTemplate();
  this->labelCounter = 0;
  std::cout << this->arithmeticAssemblyTemplate << std::endl;
  exit(0);
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
   * A=D+M
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
    if (memorySegment == "pointer" || memorySegment == "temp" ||
        memorySegment == "static") {

      pushAssemblyInstance = std::regex_replace(pushAssemblyInstance,
                                                indexRegex, std::to_string(0));
    } else {
      pushAssemblyInstance = std::regex_replace(
          pushAssemblyInstance, indexRegex, std::to_string(memorySegmentIndex));
    }

    std::regex regexDelimeter = std::regex(R"(\[(\n|.*)*?\]\n)");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexDelimeter, "",
                           std::regex_constants::format_first_only);

    /*
     *
     * @memorySegmentIndex
     *
     * D=A
     * [
     * @##m_s##
     * A=D+M
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
    if (memorySegment == "pointer" || memorySegment == "temp" ||
        memorySegment == "static") {
      pushAssemblyInstance = std::regex_replace(pushAssemblyInstance,
                                                indexRegex, std::to_string(0));
    } else {
      pushAssemblyInstance =
          std::regex_replace(pushAssemblyInstance, indexRegex,
                             std::to_string(-1 * memorySegmentIndex));
    }

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
     * A=D+M
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
     * A=D+M
     * D=M
     * ]
     * [
     * D=D+M
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
      std::regex referencedRegex = std::regex(R"(\[\nA=D\+M\nD=M\n\]\n)");
      pushAssemblyInstance =
          std::regex_replace(pushAssemblyInstance, referencedRegex, "",
                             std::regex_constants::format_first_only);
      std::regex regexOpenDelimeter = std::regex(R"(\[\n)");
      pushAssemblyInstance =
          std::regex_replace(pushAssemblyInstance, regexOpenDelimeter, "",
                             std::regex_constants::format_first_only);
      std::regex cleanRegex = std::regex(R"(M\n\]\n\]\n)");
      // std::regex regexCloseDelimeter = std::regex(R"(\n\])");
      pushAssemblyInstance =
          std::regex_replace(pushAssemblyInstance, cleanRegex, "M\n",
                             std::regex_constants::format_first_only);
      /*
       * @memorySegmentIndex
       * D=A
       * @##m_s##
       * D=D+M
       * @0
       * A=M
       * M=D
       * @0
       * M=M+1
       *
       * */
      std::regex memorySegmentRegex = std::regex(R"(\#\#m_s\#\#)");
      pushAssemblyInstance = std::regex_replace(
          pushAssemblyInstance, memorySegmentRegex,
          std::to_string(Utility::memorySegmentMap[memorySegment] +
                         memorySegmentIndex));
    } else {
      /*
       *
       * @memorySegmentIndex
       * D=A
       * [
       * @##m_s##
       * [
       * A=D+M
       * D=M
       * ]
       * [
       * D=D+M
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
      std::regex referencedRegex = std::regex(R"(\]\n\[\nD=D\+M\n\]\n\]\n)");
      pushAssemblyInstance =
          std::regex_replace(pushAssemblyInstance, referencedRegex, "",
                             std::regex_constants::format_first_only);
      std::regex memorySegmentIndexRegex = std::regex(R"(\#\#index\#\#)");
      pushAssemblyInstance =
          std::regex_replace(pushAssemblyInstance, memorySegmentIndexRegex,
                             std::to_string(memorySegmentIndex));
      std::regex memorySegmentRegex = std::regex(R"(\#\#m_s\#\#)");
      pushAssemblyInstance = std::regex_replace(
          pushAssemblyInstance, memorySegmentRegex,
          std::to_string(Utility::memorySegmentMap[memorySegment]));
    }
    // std::regex memorySegmentIndexRegex = std::regex(R"(\#\#index\#\#)");
    // pushAssemblyInstance =
    //     std::regex_replace(pushAssemblyInstance, memorySegmentIndexRegex,
    //                        std::to_string(memorySegmentIndex ));
  }
  return pushAssemblyInstance;
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
    // so in those cases I don't need to do D=D+M but D=A+D

    std::regex openDelimeter = std::regex(R"(\n\[)");
    popAssemblyInstance =
        std::regex_replace(popAssemblyInstance, openDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex closeDelimeter = std::regex(R"(\n\])");
    popAssemblyInstance =
        std::regex_replace(popAssemblyInstance, closeDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex dynamicRegex = std::regex(R"(\[\nD=D\+M\n\])");
    popAssemblyInstance =
        std::regex_replace(popAssemblyInstance, dynamicRegex, "",
                           std::regex_constants::format_first_only);

    // std::cout << popAssemblyInstance << std::endl;

  } else {
    std::cout << "IN NOT:  POINTER | TEMP | STATIC " << std::endl;
    std::regex dynamicRegex = std::regex(R"(\n\[\nA=D\+A\nD=A\n\])");
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
string CodeWritter::newArithmeticAssembly(string arithmeticType) {
  string popArithmeticInstance = string(this->arithmeticAssemblyTemplate);
  if (arithmeticType == "neg" || arithmeticType == "not") {

    std::regex regexRemoveSecondOperand = std::regex(R"(\[(.|\n)*?\]\n)");
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexRemoveSecondOperand, "",
                           std::regex_constants::format_first_only);
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexRemoveSecondOperand, "",
                           std::regex_constants::format_first_only);
    std::regex regexOpenDelimeter = std::regex(R"(\[\n)");
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexOpenDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex regexCloseDelimeter = std::regex(R"(\n\])");
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexCloseDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex operation = std::regex(R"(##operation##)");
    if (arithmeticType == "neg") {

      std::cout << "in here --------" << std::endl;
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, operation, std::string("!"),
                             std::regex_constants::format_first_only);
    } else if (arithmeticType == "not") {
      std::cout << "in here --------" << std::endl;
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, operation, std::string("-"),
                             std::regex_constants::format_first_only);
    } else {
      exit(1);
    }
    std::cout << "Right here" << std::endl;
    std::cout << popArithmeticInstance << std::endl;
    exit(0);
  } else {
    std::regex regexOpenDelimeter = std::regex(R"(\[\n)");
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexOpenDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex regexCloseDelimeter = std::regex(R"(\n\])");
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexCloseDelimeter, "",
                           std::regex_constants::format_first_only);
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexOpenDelimeter, "",
                           std::regex_constants::format_first_only);
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexCloseDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex regexUnaryDelimeter =
        std::regex(R"(\[\nD=##operation##D\n\]\n)");
    popArithmeticInstance =
        std::regex_replace(popArithmeticInstance, regexUnaryDelimeter, "",
                           std::regex_constants::format_first_only);
    std::regex operation = std::regex(R"(##operation##)");
    if (arithmeticType == "add") {
      std::cout << "in here --------" << std::endl;
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, operation, std::string("+"),
                             std::regex_constants::format_first_only);
    } else if (arithmeticType == "sub") {
      std::cout << "in here --------" << std::endl;
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, operation, std::string("-"),
                             std::regex_constants::format_first_only);

    } else if (arithmeticType == "eq") {

      std::cout << "in here --------" << std::endl;
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, operation, std::string("-"),
                             std::regex_constants::format_first_only);
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, regexOpenDelimeter, "",
                             std::regex_constants::format_first_only);
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, regexCloseDelimeter, "",
                             std::regex_constants::format_first_only);

      std::regex removeGTAndLT = std::regex(R"(\[(.|\n)*\]\n)");
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, removeGTAndLT, "",
                             std::regex_constants::format_first_only);


    } else if (arithmeticType == "gt") {

      std::cout << "in here --------" << std::endl;
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, operation, std::string("-"),
                             std::regex_constants::format_first_only);

      std::regex removeEQ = std::regex(R"(\[(.|\n)*?\]\n)");
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, removeEQ, "",
                             std::regex_constants::format_first_only);

      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, regexOpenDelimeter, "",
                             std::regex_constants::format_first_only);
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, regexCloseDelimeter, "",
                             std::regex_constants::format_first_only);

      std::regex removeLT= std::regex(R"(\[(.|\n)*?\]\n)");
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, removeLT, "",
                             std::regex_constants::format_first_only);

    } else if (arithmeticType == "lt") {

      std::cout << "in here --------" << std::endl;
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, operation, std::string("-"),
                             std::regex_constants::format_first_only);

      std::regex removeGT= std::regex(R"(\[(.|\n)*?\]\n)");
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, removeGT, "",
                             std::regex_constants::format_first_only);
      std::regex removeEQ= std::regex(R"(\[(.|\n)*?\]\n)");
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, removeEQ, "",
                             std::regex_constants::format_first_only);

      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, regexOpenDelimeter, "",
                             std::regex_constants::format_first_only);
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, regexCloseDelimeter, "",
                             std::regex_constants::format_first_only);

    } else if (arithmeticType == "and") {

      std::cout << "in here --------" << std::endl;
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, operation, std::string("&"),
                             std::regex_constants::format_first_only);
    } else if (arithmeticType == "or") {

      std::cout << "in here --------" << std::endl;
      popArithmeticInstance =
          std::regex_replace(popArithmeticInstance, operation, std::string("|"),
                             std::regex_constants::format_first_only);
    } else {
      exit(1);
    }
  }
  return popArithmeticInstance;
}
string CodeWritter::newWriteLabel(string label) {
  string writeLabelInstance = string(this->writeLabelTemplate);
  std::regex regexLabel = std::regex(R"(\#\#LABEL\#\#)");
  writeLabelInstance =
      std::regex_replace(writeLabelInstance, regexLabel, label);
  return writeLabelInstance;
}
string CodeWritter::newWriteGoto(string label) {
  string writeGotoInstance = string(this->writeGotoTemplate);
  std::regex regexLabel = std::regex(R"(\#\#LABEL\#\#)");
  writeGotoInstance = std::regex_replace(writeGotoInstance, regexLabel, label);
  return writeGotoInstance;
}
string CodeWritter::newWriteIf(string label) {
  string writeIfInstance = string(this->writeIfTemplate);
  std::regex regexLabel = std::regex(R"(\#\#LABEL\#\#)");
  writeIfInstance = std::regex_replace(writeIfInstance, regexLabel, label);
  return writeIfInstance;
}
// string CodeWritter::cleanGpr() {
//   return std::string("@13") + "\n" + "M=0" + "\n" + "@14" + "\n" + "M=0" +
//          "\n" + "@15" + "\n" + "M=0" + "\n";
// }

string CodeWritter::getPushAssembly(string segment, int index, int var1) {
  return newPushAssembly(segment, index, var1);
}
string CodeWritter::getPopAssembly(string memorySegmentIndex, int index,
                                   int var1, int var2) {
  return newPopAssembly(memorySegmentIndex, index, var1, var2);
}
string CodeWritter::getArithmeticAssembly(string arithmeticType) {
  return newArithmeticAssembly(arithmeticType);
}

string CodeWritter::getWriteLabelTemplate(string label) {
  return this->newWriteLabel(label);
}

string CodeWritter::getWriteGotoTemplate(string label) {
  return this->newWriteGoto(label);
}

string CodeWritter::getWriteIfTemplate(string label) {
  return this->newWriteIf(label);
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
 A=D+M
 D=M
 ]
 [
 D=D+M
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
      "@##m_s##" + "\n" + "[" + "\n" + "A=D+M" + "\n" + "D=M" + "\n" + "]" +
      "\n" + "[" + "\n" + "D=D+M" + "\n" + "]" +
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
 * D=D+M
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
      "@##arg1##" + "\n" + "[" + "\n" + "A=D+A" + "\n" + "D=A" + "\n" + "]" +
      "\n" + "[" + "\n" + "D=D+M" + "\n" + "]" + "\n" + "@##var2##" + "\n" +
      "M=D" + "\n" + "@##var1##" + "\n" + "D=M" + "\n" + "@##var2##" + "\n" +
      "A=M" + "\n" + "M=D" + "\n";
}
/*ARITHMETIC
  @0
  A=M-1
  D=M
  @0
  M=M-1
  @13
  M=D
  [
  @0
  A=M-1
  D=M
  @0
  M=M-1
  ]
  @13
  [
  D=D##operation##M
  ]
 ** EQ
 "[" + "\n"
 "@FIRST" + "\n"
 "D;JEQ" + "\n"
 "@SECOND" + "\n"
 "D=0" + "\n"
 "@CONTINUE" + "\n"
 "0;JMP" + "\n"
 "(FIRST)" + "\n"
 "D=-1" + "\n"
 "@CONTINUE" + "\n"
 "0;JMP" + "\n"
 "(CONTINUE)" + "\n"
 "]" + "\n"
 ** GT
 "[" + "\n"
 "@FIRST" + "\n"
 "D;JGT" + "\n"
 "@SECOND" + "\n"
 "D=0" + "\n"
 "@CONTINUE" + "\n"
 "0;JMP" + "\n"
 "(FIRST)" + "\n"
 "D=-1" + "\n"
 "@CONTINUE" + "\n"
 "0;JMP" + "\n"
 "(CONTINUE)" + "\n"
 "]" + "\n"
 "[" + "\n"
 "@FIRST" + "\n"
 "D;JLT" + "\n"
 "@SECOND" + "\n"
 "D=0" + "\n"
 "@CONTINUE" + "\n"
 "0;JMP" + "\n"
 "(FIRST)" + "\n"
 "D=-1" + "\n"
 "@CONTINUE" + "\n"
 "0;JMP" + "\n"
 "(CONTINUE)" + "\n"
 "]" + "\n"
 [
 D=##operation##D
 ]
 @0
 A=M
 M=D
 @0
 M=M+1
 * */

// "@0"+"\n" "A=M-1"+"\n" "D=M"+"\n" "@0"+"\n" "M=M-1"+"\n" "@13"+"\n" "M=D"+"\n" "["+"\n" "@0"+"\n" "A=M-1"+"\n" "D=M"+"\n" "@0"+"\n" "M=M-1"+"\n" "]"+"\n" "@13"+"\n" "["+"\n" "D=D##operation##M"+"\n" "]"+"\n" "["+"\n" "D=##operation##D"+"\n" "]"+"\n" "@0"+"\n" "A=M"+"\n" "M=D"+"\n" "@0"+"\n" "M=M+1"+"\n";
void CodeWritter::setArithmeticAssemblyTemplate(void) {
  // this->arithmeticAssemblyTemplate =
  //     std::string("@0") + "\n" + "A=M-1" + "\n" + "M=0" + "\n" + "D=A" + "\n"
  //     + "D=D-1" + "\n" + "@16" + "\n" + "A=D" + "\n" + "M=0" + "\n" + "@0" +
  //     "\n" + "M=M-1" + "\n" + "@0" + "\n" + "M=M-1" + "\n";
  // this->arithmeticAssemblyTemplate = std::string("@0") + "\n" + "M=M-1" + "\n" +
  //                                    "[" + "\n" + "@0" + "\n" + "M=M-1" + "\n" +
  //                                    "]";
  // I need to do search and replace in the operation
  // this->arithmeticAssemblyTemplate =
  //     std::string("[") + "\n" + "@0" + "\n" + "A=M-1" + "\n" + "" + "D=M" +
  //     "\n" + "@0" + "\n" + "M=M-1" + "\n" + "@13" + "\n" + "M=D" + "\n" + "@0" +
  //     "\n" + "A=M-1" + "\n" + "D=M" + "\n" + "@0" + "\n" + "M=M-1" + "\n" +
  //     "@13" + "\n" + "D=D+M" + "\n" + "@0" + "\n" + "M=D";
  // for binary operations first
  // this->arithmeticAssemblyTemplate =
  //     std::string("\n") + "@0" + "\n" + "A=M-1" + "\n" + "" + "D=M" + "\n" +
  //     "@0" + "\n" + "M=M-1" + "\n" + "@13" + "\n" + "M=D" + "\n" + "@0" + "\n" +
  //     "A=M-1" + "\n" + "D=M" + "\n" + "@0" + "\n" + "M=M-1" + "\n" + "@13" +
  //     "\n" + "D=D+M" + "\n" + "@0" + "\n" +"A=M"+ "\n"+ "M=D" +"\n"+"@0" +"\n"+ "M=M+1" ;

  this->arithmeticAssemblyTemplate = std::string("@0") + "\n" + "A=M-1" +
                                     "\n"
                                     "D=M" +
                                     "\n"
                                     "@0" +
                                     "\n"
                                     "M=M-1" +
                                     "\n"
                                     "@13" +
                                     "\n"
                                     "M=D" +
                                     "\n" + "[" +
                                     "\n"
                                     "@0" +
                                     "\n"
                                     "A=M-1" +
                                     "\n"
                                     "D=M" +
                                     "\n"
                                     "@0" +
                                     "\n"
                                     "M=M-1" +
                                     "\n"
                                     "]" +
                                     "\n"
                                     "@13" +
                                     "\n"
                                     "[" +
                                     "\n"
                                     "D=D##operation##M" +
                                     "\n"
                                     "]" +
                                     "\n"
                                     "[" +
                                     "\n"
                                     "@FIRST" +
                                     "\n"
                                     "D;JEQ" +
                                     "\n"
                                     "D=0" +
                                     "\n"
                                     "@CONTINUE" +
                                     "\n"
                                     "0;JMP" +
                                     "\n"
                                     "(FIRST)" +
                                     "\n"
                                     "D=-1" +
                                     "\n"
                                     "@CONTINUE" +
                                     "\n"
                                     "0;JMP" +
                                     "\n"
                                     "]" +
                                     "\n"
                                     "[" +
                                     "\n"
                                     "@FIRST" +
                                     "\n"
                                     "D;JGT" +
                                     "\n"
                                     "D=0" +
                                     "\n"
                                     "@CONTINUE" +
                                     "\n"
                                     "0;JMP" +
                                     "\n"
                                     "(FIRST)" +
                                     "\n"
                                     "D=-1" +
                                     "\n"
                                     "@CONTINUE" +
                                     "\n"
                                     "0;JMP" +
                                     "\n"
                                     "]" +
                                     "\n"
                                     "[" +
                                     "\n"
                                     "@FIRST" +
                                     "\n"
                                     "D;JLT" +
                                     "\n"
                                     "D=0" +
                                     "\n"
                                     "@CONTINUE" +
                                     "\n"
                                     "0;JMP" +
                                     "\n"
                                     "(FIRST)" +
                                     "\n"
                                     "D=-1" +
                                     "\n"
                                     "@CONTINUE" +
                                     "\n"
                                     "0;JMP" +
                                     "\n"
                                     "]" +
                                     "\n"
                                     "[" +
                                     "\n"
                                     "D=##operation##D" +
                                     "\n"
                                     "]" +
                                     "\n"
                                     "(CONTINUE)"
                                     "\n"
                                     "@0" +
                                     "\n"
                                     "A=M" +
                                     "\n"
                                     "M=D" +
                                     "\n"
                                     "@0" +
                                     "\n"
                                     "M=M+1";
}
void CodeWritter::setWriteLabelTemplate(void) {
  this->writeLabelTemplate = "(##LABEL##)";
}
void CodeWritter::setWriteGotoTemplate(void) {
  this->writeGotoTemplate = std::string("@##LABEL##") + "\n" + "0;JMP";
}
void CodeWritter::setWriteIfTemplate(void) {
  this->writeIfTemplate = std::string("@0") + "\n" + "M=M-1" + "\n" + "A=M" +
                          "\n" + "D=M" + "\n" + "@##LABEL##" + "\n" + "D;JGT";
}
