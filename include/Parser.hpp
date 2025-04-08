#ifndef __PARSER__
#define __PARSER__
#include "Utilities.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::string;
class Parser {
private:
  string arg1;
  int arg2;

public:
  Parser();
  ~Parser();
  void setArg1(string arg1);
  void setArg2(int arg2);
  std::string getCommandType();
  std::string getArg1();
  int getArg2();
};
#endif
