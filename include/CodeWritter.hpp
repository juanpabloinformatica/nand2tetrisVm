#ifndef __CODE_WRITTER__
#define __CODE_WRITTER__
#include "Utilities.hpp"
#include <iostream>
class CodeWritter {
public:
  CodeWritter();
  void setFileName(std::string fileName);
  void writeArithmetic(std::string command);
  void writePushPop(COMMAND_TYPE commandType, std::string segment, int index);
  // closing the output file
  // void close
  ~CodeWritter();
};
#endif
