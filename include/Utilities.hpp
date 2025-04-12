#ifndef __UTILITIES__
#define __UTILITIES__
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <vector>
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::stringstream;
using std::unique_ptr;
using std::vector;
enum COMMAND_TYPE {
  C_UNDEFINED = -1,
  C_ARITHMETIC = 1,
  C_PUSH = 2,
  C_POP = 3,
  C_LABEL = 4,
  C_GOTO = 5,
  C_IF = 6,
  C_FUNCTION = 7,
  C_RETURN = 8,
  C_CALL = 9
};
// i think is better do all of this static honestly
class Utility {
private:
  static map<string, COMMAND_TYPE> mapCArithmetic;
  static vector<string> splittCurrentCommand;

public:
  // Utility();
  // ~Utility();
  static void setMapCArithmetic();
  // const vector<string> &splitCurrentCommand(string currentCommand);
  static void setSplitCurrentCommand(string currentCommand);
  static void resetSplitCurrentCommand();
  static const vector<string> &getSplitCurrentCommand();
  static const map<string, COMMAND_TYPE> &getMapCArithmetic();
  static string getFilepath(string file);
};
// a lot of wasted memory

#endif
