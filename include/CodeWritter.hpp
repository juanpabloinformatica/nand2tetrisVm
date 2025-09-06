#ifndef __CODE_WRITTER__
#define __CODE_WRITTER__
#include <fstream>
#include <map>
#include <regex>
#include "Utilities.hpp"
using std::ofstream;
using std::string;
using std::regex_constants::format_first_only;
class CodeWritter {
 private:
  string pushAssemblyTemplate;
  string popAssemblyTemplate;
  string arithmeticAssemblyTemplate;
  string writeLabelTemplate;
  string writeGotoTemplate;
  string writeIfTemplate;
  int labelCounter;
  int firstLabelCounter;
  int continueLabelCounter;
  string _arithmeticAssemblyBinary(string arithmeticType,
                                   string arithmeticAssemblyInstance);
  string _arithmeticAssemblyBinaryNotBool(string arithmeticType,
                                          string arithmeticAssemblyInstance);
  string _arithmeticAssemblyBinaryBool(string arithmeticType,
                                       string arithmeticAssemblyInstance);
  string _arithmeticAssemblyUnary(string arithmeticType,
                                  string arithmeticAssemblyInstance);

  string newPushAssembly(string mememorySegment, int memorySegmentIndex,
                         int var1);
  string newPopAssembly(string mememorySegment, int memorySegmentIndex,
                        int var1, int var2);
  string newArithmeticAssembly(string arithmeticType);
  string transformTemplate(std::map<std::string, std::string>& patternMatchMap,
                           string assemblyTemplate);

  // Adding branching
  string newWriteLabel(string label);
  string newWriteGoto(string label);
  string newWriteIf(string label);

 public:
  CodeWritter();
  void setPushAssemblyTemplate(void);
  void setPopAssemblyTemplate(void);
  void setArithmeticAssemblyTemplate(void);
  void setWriteLabelTemplate(void);
  void setWriteGotoTemplate(void);
  void setWriteIfTemplate(void);
  string getPushAssembly(string segment, int index, int var1);
  string getPopAssembly(string segment, int index, int var1, int var2);
  string getArithmeticAssembly(string arithmeticType);
  string getWriteLabelTemplate(string label);
  string getWriteGotoTemplate(string label);
  string getWriteIfTemplate(string label);
};
#endif
