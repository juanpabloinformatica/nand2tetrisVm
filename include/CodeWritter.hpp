#ifndef __CODE_WRITTER__

#define __CODE_WRITTER__
#include "Utilities.hpp"
#include <fstream>
using std::ofstream;
using std::string;
class CodeWritter {
private:
  string pushAssemblyTemplate;
  string popAssemblyTemplate;
  string arithmeticAssemblyTemplate;
  string writeLabelTemplate;
  string writeGotoTemplate;
  string writeIfTemplate;
  int labelCounter;
  string newPushAssembly(string mememorySegment, int memorySegmentIndex,
                         int var1);
  string newPopAssembly(string mememorySegment, int memorySegmentIndex,
                        int var1, int var2);
  string newArithmeticAssembly(string arithmeticType);
  // Adding branching
  string newWriteLabel(string label);
  string newWriteGoto(string label);
  string newWriteIf(string label);

public:
  CodeWritter();
  void setPushAssemblyTemplate(void);
  void setPopAssemblyTemplate(void);
  void setArithmeticAssemblyTemplate(void);
  void setWriteLabelTemplate(void);
  void setWriteGotoTemplate(void);
  void setWriteIfTemplate(void);
  string getPushAssembly(string segment, int index, int var1);
  string getPopAssembly(string segment, int index, int var1, int var2);
  string getArithmeticAssembly(string arithmeticType);
  string getWriteLabelTemplate(string label);
  string getWriteGotoTemplate(string label);
  string getWriteIfTemplate(string label);
  // ~CodeWritter();
  // void writeArithmetic(string command);
  // void writePush(COMMAND_TYPE commandType, string segment, int index);
  // void writePop(COMMAND_TYPE commandType, string segment, int index);
  // void setWriteFile(string fileName);
  // closing the output file
  // void close
};
#endif
