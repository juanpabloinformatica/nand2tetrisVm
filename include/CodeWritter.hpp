#ifndef __CODE_WRITTER__
#define __CODE_WRITTER__
#include "Utilities.hpp"

#include <fstream>
#include <map>
#include <regex>
using std::ofstream;
using std::string;
using std::regex_constants::format_first_only;
/*Bitmasking here should be better*/
/*
 *arithmetic
 */

const int nArNotBool = 10;
const int nArUnary   = 6;
const int nArBool    = 22;
/*
 *  pop
 */

const int nPopNotReferenceVar = 18;
const int nPopReferenceVar    = 17;

/*
 *  push
 */

const int nPushConstant        = 7;
const int nPushNotReferenceVar = 9;
const int nPushReferenceVar    = 10;

/*
 *  call
 */

/*Here is 49 and not 50 because labels doesn't count*/
const int nCall = 49;

/*
 *  function
 */
/*Here is 15 and not 16 because labels doesn't count*/
const int nFunction = 16;

/*
 *  goto
 */
const int nGoto = 2;

/*
 *  if
 */
const int nIf = 6;

/*
 *  init
 */
const int nInit = 53;

/*
 *  label
 */
/*Here is 0 and not 1 because labels doesn't count*/
const int nLabel = 0;

/*
 *  return
 */
const int nReturn = 80;

class CodeWritter {
  private:
    class PatternMgr {
      public:
        std::map<std::string, std::string> patternMap;
        std::vector<std::string>           patternInsertionTrack;
        void                               addPattern(std::string pattern, std::string replacement);
        // string getTransformedTemplate(std::string assemblyTemplate, bool firstOnly);
    };

    string pushAssemblyTemplate;
    string popAssemblyTemplate;
    string arithmeticAssemblyTemplate;
    string writeLabelTemplate;
    string writeGotoTemplate;
    string writeIfTemplate;
    string writeCallTemplate;
    string writeInitTemplate;
    string writeReturnTemplate;
    string writeFunctionTemplate;
    // should this variable be part of the control and
    // passed as args?? I think yeah
    int    labelCounter;
    int    firstLabelCounter;
    int    continueLabelCounter;
    int    globalHackInstructionCounter;
    string _arithmeticAssemblyBinary(string arithmeticType, string arithmeticAssemblyInstance);
    string _arithmeticAssemblyBinaryNotBool(string arithmeticType, string arithmeticAssemblyInstance);
    string _arithmeticAssemblyBinaryBool(string arithmeticType, string arithmeticAssemblyInstance);
    string _arithmeticAssemblyUnary(string arithmeticType, string arithmeticAssemblyInstance);

    string newPushAssembly(string mememorySegment, int memorySegmentIndex, int var1);
    string newPopAssembly(string mememorySegment, int memorySegmentIndex, int var1, int var2);
    string newArithmeticAssembly(string arithmeticType);
    string transformTemplate(PatternMgr & patternMgr, string assemblyTemplate, bool firstOnly);

    // Adding branching
    string newWriteLabel(string label);
    string newWriteGoto(string label);
    string newWriteIf(string label);
    // Adding function mechanism
    string newWriteCall(string nArgs, string functionName);
    // string newWriteFunction();
    // string newWriteReturn();
    // string newWriteInit();

    string newWriteInitAssembly(void);
    string newWriteReturnAssembly(void);
    string newWriteFunctionAssembly(string functionName, string nArgs);

  public:
    CodeWritter();
    void   setPushAssemblyTemplate(void);
    void   setPopAssemblyTemplate(void);
    void   setArithmeticAssemblyTemplate(void);
    void   setWriteLabelTemplate(void);
    void   setWriteGotoTemplate(void);
    void   setWriteIfTemplate(void);
    void   setWriteCallTemplate(void);
    void   setWriteInitTemplate(void);
    void   setWriteReturnTemplate(void);
    void   setWriteFunctionTemplate(void);
    string getPushAssembly(string segment, int index, int var1);
    string getPopAssembly(string segment, int index, int var1, int var2);
    string getArithmeticAssembly(string arithmeticType);
    string getWriteLabelTemplate(string label);
    string getWriteGotoTemplate(string label);
    string getWriteIfTemplate(string label);
    string getWriteCallTemplate(string nArgs, string functionName);
    string getWriteInitAssembly(void);
    string getWriteReturnAssembly(void);
    string getWriteFunctionAssembly(string functionName, string nArgs);
    string getTemplate(string filepath);
    /*This will be removed*/
    int    getGlobalHackInstructionCounter(void);
    void   setGlobalHackInstructionCounter(int value);
};
#endif
