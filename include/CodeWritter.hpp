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

public:
  CodeWritter();
  // string getInitAssembly(void);
  void setPushAssemblyTemplate(void);
  void setPopAssemblyTemplate(void);
  void setArithmeticAssemblyTemplate(void);
  string getPushAssembly(COMMAND_TYPE commandType, string segment, int index);
  string getPopAssembly(COMMAND_TYPE commandType, string segment, int index);
  string getArithmeticAssembly(string operation);
  // ~CodeWritter();
  // void writeArithmetic(string command);
  // void writePush(COMMAND_TYPE commandType, string segment, int index);
  // void writePop(COMMAND_TYPE commandType, string segment, int index);
  // void setWriteFile(string fileName);
  // closing the output file
  // void close
};
#endif
