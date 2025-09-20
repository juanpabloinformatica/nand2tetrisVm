#ifndef __CONTROL__
#define __CONTROL__
#include <fstream>
#include "CodeWritter.hpp"
#include "MemoryManager.hpp"
#include "Parser.hpp"
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
class Control {
 private:
  ifstream readFile;
  ofstream writeFile;
  Parser parser;
  CodeWritter codeWritter;
  MemoryManager memoryManager;
	// I don't know if it is good to have this variables in this module
	int currentCommandLineNumber;
	string actualFunction;
	int functionReturnCounter;

 public:
  Control(string filepath);
  ~Control();
  void setReadFile(string filepath);
  ifstream& getReadFile();
  void setWriteFile(string filepath);
  ofstream& getWriteFile();
  void traverseFile();
};
#endif
