#ifndef __UTILITIES__
#define __UTILITIES__
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
class Utility {
private:
  map<string, COMMAND_TYPE> mapCArithmetic;
  vector<string> splittCurrentCommand;

public:
  Utility();
  ~Utility();
  void setMapCArithmetic();
  // const vector<string> &splitCurrentCommand(string currentCommand);
  void setSplitCurrentCommand(string currentCommand);
  void resetSplitCurrentCommand();
  const vector<string> &getSplitCurrentCommand();
  const map<string, COMMAND_TYPE> &getMapCArithmetic();
};
#endif
