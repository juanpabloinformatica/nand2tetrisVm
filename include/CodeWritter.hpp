#ifndef __CODE_WRITTER__

#define __CODE_WRITTER__
#include "Utilities.hpp"
#include <fstream>
#include <iostream>
using std::ofstream;
using std::string;
class CodeWritter {
private:
  ofstream writeFile;

public:
  CodeWritter();
  string getPushAssembly(COMMAND_TYPE commandType, string segment, int index);
  string getPopAssembly(COMMAND_TYPE commandType, string segment, int index);
  // ~CodeWritter();
  // void writeArithmetic(string command);
  // void writePush(COMMAND_TYPE commandType, string segment, int index);
  // void writePop(COMMAND_TYPE commandType, string segment, int index);
  // void setWriteFile(string fileName);
  // closing the output file
  // void close
};
#endif
