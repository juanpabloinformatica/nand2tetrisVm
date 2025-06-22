#ifndef __UTILITIES__
#define __UTILITIES__
#include <filesystem>
#include <map>
#include <string>
using std::map;
using std::string;
const int M_S_CONSTANT = 874;
const int NOTREFMS = 6000;
// enum M_S {
//   M_S_SP = 0,
//   M_S_LCL = 1,
//   M_S_ARG = 2,
//   M_S_THIS = 3,
//   M_S_THAT = 4,
//   M_S_CONSTANT = 5,
//
// };
enum COMMAND_TYPE {
  // C_UNDEFINED = -1,
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
public:
  static string getFilepath(string file);
  static map<string, int> memorySegmentMap;
};

#endif
