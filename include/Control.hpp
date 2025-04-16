#ifndef __CONTROL__
#define __CONTROL__
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::string;
class Control {
private:
  ifstream readFile;
  ofstream writeFile;

public:
  Control(string filepath);
  ~Control();
  void setReadFile(string filepath);
  const ifstream &getReadFile();
  void setWriteFile(string filepath);
  const ofstream &getWriteFile();
};
#endif
