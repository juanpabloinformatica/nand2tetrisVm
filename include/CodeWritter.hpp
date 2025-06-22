#ifndef __CODE_WRITTER__

#define __CODE_WRITTER__
#include "Utilities.hpp"
#include <fstream>
#include <iostream>
using std::ofstream;
using std::string;
class CodeWritter {
private:
  string pushAssemblyTemplate;
  string popAssemblyTemplate;
  string arithmeticAssemblyTemplate;
  int labelCounter;
  // i could do this oop but not  now
  string newPushAssembly(string mememorySegment, int memorySegmentIndex, int var1);
  string newPopAssembly(string mememorySegment, int memorySegmentIndex, int var1,
                        int var2);
  string newArithmeticAssembly(string arithmeticType);

public:
  CodeWritter();
  // string getInitAssembly(void);
  void setPushAssemblyTemplate(void);
  void setPopAssemblyTemplate(void);
  void setArithmeticAssemblyTemplate(void);
  string getPushAssembly(string segment, int index, int var1);
  string getPopAssembly(string segment, int index, int var1, int var2);
  string getArithmeticAssembly(string arithmeticType);
  string cleanGpr(void);

  // ~CodeWritter();
  // void writeArithmetic(string command);
  // void writePush(COMMAND_TYPE commandType, string segment, int index);
  // void writePop(COMMAND_TYPE commandType, string segment, int index);
  // void setWriteFile(string fileName);
  // closing the output file
  // void close
};
#endif
