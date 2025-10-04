#ifndef __PARSER__
#define __PARSER__
#include "Utilities.hpp"

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#define ARRAY_LENGTH 3

using std::array;
using std::cout;
using std::endl;
using std::ifstream;
using std::map;
using std::stoi;
using std::string;
using std::stringstream;

class Parser {
  private:
    string                      arg1;
    int                         arg2;
    COMMAND_TYPE                commandType;
    array<string, ARRAY_LENGTH> splitCurrentCommand;
    map<string, COMMAND_TYPE>   mapCommand;

  public:
    Parser();
    ~Parser();
    void                                operateCommand(string currentCommand);
    void                                setCommandType(COMMAND_TYPE commandType);
    void                                setArg1(string arg1);
    void                                setArg2(int arg2);
    void                                setSplitCurrentCommand(string currentCommand);
    void                                setMapCommand();
    void                                resetSplitCurrentCommand();
    const array<string, ARRAY_LENGTH> & getSplitCurrentCommand();
    const map<string, COMMAND_TYPE> &   getMapCommand();
    string                              getArg1();
    int                                 getArg2();
    COMMAND_TYPE &                      getCommandType();
};
#endif
