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
using std::filesystem::is_regular_file;
using std::filesystem::is_directory;
using std::filesystem::recursive_directory_iterator;
using std::filesystem::absolute;
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
	bool isVmFile(const string& filepath);
	void filepathHandler(string &filepath);
	void fileHandler(const string &filepath);
	void directoryHandler(const string &filepath);

    public:
	Control(string filepath);
	~Control();
	void start_control(string &filepath);
	void setReadFile(string filepath);
	ifstream &getReadFile();
	void setWriteFile(string filepath);
	ofstream &getWriteFile();
	void traverseFile(void);
	void setIsFile(void);
	void traverseHandler(void);
};
#endif
