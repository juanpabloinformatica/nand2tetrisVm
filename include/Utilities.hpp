#ifndef __UTILITIES__
#define __UTILITIES__
#include <filesystem>
#include <map>
#include <string>
using std::map;
using std::string;
const int M_S_CONSTANT = 874;
const int NOTREFMS     = 6000;

enum COMMAND_TYPE {
    C_ARITHMETIC = 1,
    C_PUSH       = 2,
    C_POP        = 3,
    C_LABEL      = 4,
    C_GOTO       = 5,
    C_IF         = 6,
    C_FUNCTION   = 7,
    C_RETURN     = 8,
    C_CALL       = 9
};

class Utility {
  public:
    static string           getFilepath(string file);
    static map<string, int> memorySegmentMap;
    static int              fileExtensionDotIndex(const string & path);
    static int              getDirectoryNameIndex(const string& dirpath);
};

#endif
