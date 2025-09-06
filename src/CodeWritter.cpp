#include "CodeWritter.hpp"
#include <iostream>
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
  this->firstLabelCounter = 0;
  this->continueLabelCounter = 0;
}
string CodeWritter::newPushAssembly(string memorySegment,
                                    int memorySegmentIndex, int var1) {
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
  }
  if (memorySegment == "constant") {
    std::cout << "Entering in CONSTANT" << std::endl;
    // std::cout << "here 2" << std::endl;
    std::regex regexDelimeter = std::regex(R"(\[(\n|.)*\]\n)");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, regexDelimeter, "",
                           std::regex_constants::format_first_only);
  } else {
    std::regex firstDelimeterRegex = std::regex(R"(\[\n)");
    pushAssemblyInstance =
        std::regex_replace(pushAssemblyInstance, firstDelimeterRegex, "",
                           std::regex_constants::format_first_only);
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
      std::regex memorySegmentRegex = std::regex(R"(\#\#m_s\#\#)");
      pushAssemblyInstance = std::regex_replace(
          pushAssemblyInstance, memorySegmentRegex,
          std::to_string(Utility::memorySegmentMap[memorySegment] +
                         memorySegmentIndex));
    } else {
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
string CodeWritter::_arithmeticAssemblyUnary(
    string arithmeticType, string arithmeticAssemblyInstance) {
  std::map<std::string, std::string> test =
      std::map<std::string, std::string>();
  test[R"(\n\[)"] = "";
  test[R"(\n\])"] = "";
  test[R"(\#\#operation\#\#)"] = arithmeticType == "not" ? "!" : "-";
  test[R"(\n\])"] = "";
  test[R"(\n\[(.|\n)*\])"] = "";
  return this->transformTemplate(test, arithmeticAssemblyInstance);
}
string CodeWritter::transformTemplate(
    std::map<std::string, std::string>& patternMatchMap,
    string assemblyTemplate) {
  for (auto element : patternMatchMap) {
    assemblyTemplate =
        std::regex_replace(assemblyTemplate, std::regex(element.first),
                           element.second, format_first_only);
  }
  return assemblyTemplate;
}
string CodeWritter::_arithmeticAssemblyBinaryNotBool(
    string arithmeticType, string arithmeticAssemblyInstance) {

  std::regex replaceOperation = std::regex(R"(\#\#operation\#\#)");
  std::regex replaceOpenDelimeter = std::regex(R"(\[\n)");
  std::regex replaceCloseDelimeter = std::regex(R"(\]\n)");
  std::regex replaceUnused = std::regex(R"(\[(\n|.)*?\]\n)");
  std::regex replaceUnusedBranching = std::regex(R"(\[(\n|.)*\]\n)");
  std::string operation = "";
  arithmeticAssemblyInstance = std::regex_replace(
      arithmeticAssemblyInstance, replaceUnused, "", format_first_only);
  arithmeticAssemblyInstance = std::regex_replace(
      arithmeticAssemblyInstance, replaceOpenDelimeter, "", format_first_only);
  arithmeticAssemblyInstance = std::regex_replace(
      arithmeticAssemblyInstance, replaceCloseDelimeter, "", format_first_only);
  arithmeticAssemblyInstance = std::regex_replace(arithmeticAssemblyInstance,
                                                  replaceUnusedBranching, "");

  if (arithmeticType == "add") {
    operation = "+";
  } else if (arithmeticType == "sub") {
    operation = "-";
  } else if (arithmeticType == "and") {
    operation = "&";
  } else {
    operation = "|";
  }
  arithmeticAssemblyInstance =
      std::regex_replace(arithmeticAssemblyInstance, replaceOperation,
                         operation, format_first_only);
  return arithmeticAssemblyInstance;
}
string CodeWritter::_arithmeticAssemblyBinaryBool(
    string arithmeticType, string arithmeticAssemblyInstance) {
  std::regex replaceOperation = std::regex(R"(\#\#operation\#\#)");
  std::regex replaceOpenDelimeter = std::regex(R"(\[\n)");
  std::regex replaceCloseDelimeter = std::regex(R"(\]\n)");
  std::regex replaceCloseLastDelimeter = std::regex(R"(M\=M\+1\n\]\n)");
  std::regex replaceUnused = std::regex(R"(\[(.|\n)*?\]\n)");
  std::regex replaceContinueLabel =
      std::regex(R"(\#\#continueLabelCounter\#\#)");
  std::regex replaceFirstLabel = std::regex(R"(\#\#firstLabelCounter\#\#)");

  arithmeticAssemblyInstance = std::regex_replace(
      arithmeticAssemblyInstance, replaceUnused, "", format_first_only);
  arithmeticAssemblyInstance = std::regex_replace(
      arithmeticAssemblyInstance, replaceUnused, "", format_first_only);
  arithmeticAssemblyInstance = std::regex_replace(
      arithmeticAssemblyInstance, replaceOpenDelimeter, "", format_first_only);
  arithmeticAssemblyInstance =
      std::regex_replace(arithmeticAssemblyInstance, replaceCloseLastDelimeter,
                         "M=M+1\n", format_first_only);

  if (arithmeticType == "eq") {
    arithmeticAssemblyInstance =
        std::regex_replace(arithmeticAssemblyInstance, replaceOpenDelimeter, "",
                           format_first_only);
    arithmeticAssemblyInstance =
        std::regex_replace(arithmeticAssemblyInstance, replaceCloseDelimeter,
                           "", format_first_only);
    arithmeticAssemblyInstance = std::regex_replace(
        arithmeticAssemblyInstance, replaceUnused, "", format_first_only);
    arithmeticAssemblyInstance = std::regex_replace(
        arithmeticAssemblyInstance, replaceUnused, "", format_first_only);

  } else if (arithmeticType == "gt") {
    arithmeticAssemblyInstance = std::regex_replace(
        arithmeticAssemblyInstance, replaceUnused, "", format_first_only);
    arithmeticAssemblyInstance =
        std::regex_replace(arithmeticAssemblyInstance, replaceOpenDelimeter, "",
                           format_first_only);
    arithmeticAssemblyInstance =
        std::regex_replace(arithmeticAssemblyInstance, replaceCloseDelimeter,
                           "", format_first_only);
    arithmeticAssemblyInstance = std::regex_replace(
        arithmeticAssemblyInstance, replaceUnused, "", format_first_only);

  } else if (arithmeticType == "lt") {
    arithmeticAssemblyInstance = std::regex_replace(
        arithmeticAssemblyInstance, replaceUnused, "", format_first_only);
    arithmeticAssemblyInstance = std::regex_replace(
        arithmeticAssemblyInstance, replaceUnused, "", format_first_only);
    arithmeticAssemblyInstance =
        std::regex_replace(arithmeticAssemblyInstance, replaceOpenDelimeter, "",
                           format_first_only);
    arithmeticAssemblyInstance =
        std::regex_replace(arithmeticAssemblyInstance, replaceCloseDelimeter,
                           "", format_first_only);
  }
  arithmeticAssemblyInstance =
      std::regex_replace(arithmeticAssemblyInstance, replaceFirstLabel,
                         std::to_string(this->firstLabelCounter));
  arithmeticAssemblyInstance =
      std::regex_replace(arithmeticAssemblyInstance, replaceContinueLabel,
                         std::to_string(this->continueLabelCounter));
  this->firstLabelCounter++;
  this->continueLabelCounter++;

  if (true) {
    ofstream log = ofstream("./log/CodeWritterLog.txt");
    log << "CodeWritter:" << std::endl;
    log << arithmeticAssemblyInstance << std::endl;
    log.close();
  }

  return arithmeticAssemblyInstance;
}
string CodeWritter::_arithmeticAssemblyBinary(
    string arithmeticType, string arithmeticAssemblyInstance) {

  if (arithmeticType == "add" || arithmeticType == "sub" ||
      arithmeticType == "or" || arithmeticType == "and")
    return _arithmeticAssemblyBinaryNotBool(arithmeticType,
                                            arithmeticAssemblyInstance);
  return _arithmeticAssemblyBinaryBool(arithmeticType,
                                       arithmeticAssemblyInstance);
  return NULL;
}

string CodeWritter::newArithmeticAssembly(string arithmeticType) {
  string arithmeticAssemblyInstance = this->arithmeticAssemblyTemplate;
  std::regex replace = std::regex(R"(\#\#operation\#\#)");
  if (arithmeticType == "not" || arithmeticType == "neg")
    return _arithmeticAssemblyUnary(arithmeticType, arithmeticAssemblyInstance);
  return _arithmeticAssemblyBinary(arithmeticType, arithmeticAssemblyInstance);

  return arithmeticAssemblyInstance;
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
void CodeWritter::setPopAssemblyTemplate(void) {
  this->popAssemblyTemplate =
      std::string("@0") + "\n" + "M=M-1" + "\n" + "A=M" + "\n" + "D=M" + "\n" +
      "@##var1##" + "\n" + "M=D" + "\n" + "@##arg2##" + "\n" + "D=A" + "\n" +
      "@##arg1##" + "\n" + "[" + "\n" + "A=D+A" + "\n" + "D=A" + "\n" + "]" +
      "\n" + "[" + "\n" + "D=D+M" + "\n" + "]" + "\n" + "@##var2##" + "\n" +
      "M=D" + "\n" + "@##var1##" + "\n" + "D=M" + "\n" + "@##var2##" + "\n" +
      "A=M" + "\n" + "M=D" + "\n";
}
void CodeWritter::setArithmeticAssemblyTemplate(void) {
  std::string unaryTemplate = R"(
[
@0
M=M-1
A=M
M=##operation##M
@0
M=M+1
]
[
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
M=M##operation##D
@0
M=M+1
]
[
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
M=M-D
D=M
[
@FIRST##firstLabelCounter##
D;JEQ
D=0
@CONTINUE##continueLabelCounter##
0;JMP
(FIRST##firstLabelCounter##)
D=-1
@CONTINUE##continueLabelCounter##
0;JMP
]
[
@FIRST##firstLabelCounter##
D;JGT
D=0
@CONTINUE##continueLabelCounter##
0;JMP
(FIRST##firstLabelCounter##)
D=-1
@CONTINUE##continueLabelCounter##
0;JMP
]
[
@FIRST##firstLabelCounter##
D;JLT
D=0
@CONTINUE##continueLabelCounter##
0;JMP
(FIRST##firstLabelCounter##)
D=-1
@CONTINUE##continueLabelCounter##
0;JMP
]
(CONTINUE##continueLabelCounter##)
@0
A=M
M=D
@0
M=M+1
]
)";
  this->arithmeticAssemblyTemplate = unaryTemplate;
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
