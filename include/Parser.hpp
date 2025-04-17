#ifndef __PARSER__
#define __PARSER__
#include "Utilities.hpp"
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::ifstream;
using std::stoi;
using std::string;
class Parser {
private:
  string arg1;
  int arg2;
  COMMAND_TYPE commandType;

public:
  Parser();
  ~Parser();
  void operateCommand(string currentCommand);
  void setCommandType(COMMAND_TYPE commandType);
  void setArg1(string arg1);
  void setArg2(int arg2);
  void setReadFile(string filepath);
  // std::string getCommandType();
  string getArg1();
  int getArg2();
  COMMAND_TYPE &getCommandType();
};
#endif
