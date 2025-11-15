#ifndef __CONTROL__
#define __CONTROL__
#include "CodeWritter.hpp"
#include "MemoryManager.hpp"
#include "Parser.hpp"

#include <fstream>
#include <string>
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::filesystem::absolute;
using std::filesystem::is_directory;
using std::filesystem::is_regular_file;
using std::filesystem::path;
using std::filesystem::recursive_directory_iterator;

class Control {
  private:
    ifstream      readFile;
    ofstream      writeFile;
    string        writeFileName;
    Parser        parser;
    CodeWritter   codeWritter;
    MemoryManager memoryManager;
    int           currentCommandLineNumber;
    string        actualFunction;
    int           functionReturnCounter;
    bool          isVmFile(const string & filepath);
    void          filepathHandler(string & filepath);
    void          fileHandler(const string & filepath);
    void          directoryHandler(const string & filepath);
    void          setBoostrapToWriteFile(void);

  public:
    Control(string filepath);
    ~Control();
    void       start_control(string & filepath);
    void       setReadFile(string filepath);
    void       setWriteFileName(string writeFileName);
    ifstream & getReadFile();
    void       setWriteFile(string filepath);
    ofstream & getWriteFile();
    string &   getWriteFileName();
    void       traverseFile(void);
    void       setIsFile(void);
    void       traverseHandler(void);
};
#endif
