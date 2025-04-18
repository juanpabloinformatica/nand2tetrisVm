#ifndef __UTILITIES__
#define __UTILITIES__
#include <filesystem>
#include <string>
using std::string;
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
public:
  static string getFilepath(string file);
};
// a lot of wasted memory

#endif
