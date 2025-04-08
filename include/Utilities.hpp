#ifndef __UTILITIES__
#define __UTILITIES__
#include <iostream>
#include <map>
using std::map;
using std::string;
using std::endl;
using std::cout;
enum COMMAND_TYPE {
  C_ARITHMETIC,
  C_PUSH,
  C_POP,
  C_LABEL,
  C_GOTO,
  C_IF,
  C_FUNCTION,
  C_RETURN,
  C_CALL
};
class Utility {
private:
  map<string, COMMAND_TYPE> mapCArithmetic;

public:
  Utility();
  ~Utility();
  void setMapCArithmetic();
  const map<string, COMMAND_TYPE> &getMapCArithmetic();
};
#endif
