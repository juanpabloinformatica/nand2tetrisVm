#include "Control.hpp"
#include <iostream>
Control::Control(string filepath) {
  if (filepath != "") {
    this->setReadFile(filepath);
    int indexDelimeter = filepath.find(".");
    if (std::filesystem::exists(filepath)) {
      string writeFilePath = filepath.substr(0, indexDelimeter) + ".asm";
      this->setWriteFile(writeFilePath);
    } else {
      cout << "Not working path" << endl;
      // exit(EXIT_FAILURE);
    }
  }
  this->parser = Parser();
  this->memoryManager = MemoryManager();
  this->codeWritter = CodeWritter();
}
void Control::traverseFile() {
  cout << "in here" << endl;
  string currentCommand;
  int resultPop;
  while (std::getline(this->readFile, currentCommand)) {
    currentCommand.erase(
        0, currentCommand.find_first_not_of(" \n\r\t")); // left trim
    currentCommand.erase(currentCommand.find_last_not_of("\t\n\v\f\r ") +
                         1); // right trim
    if (currentCommand.substr(0, 2) != "//" && currentCommand != "") {
      this->parser.operateCommand(currentCommand);
      switch (this->parser.getCommandType()) {
      case C_ARITHMETIC:
        // this->getWriteFile() << this->codeWritter.getPushAssembly(
        //     "constant", this->memoryManager.popStack());
        this->getWriteFile()
            << "// Setting to 0 last 2 values and then pointing to the n-1 "
               "value for putting the result in there"
            << endl;
        this->getWriteFile()
            << this->codeWritter.getArithmeticAssembly(this->parser.getArg1());
        this->getWriteFile() << endl;
        resultPop = this->memoryManager.popStack(this->parser.getArg1());
        this->memoryManager.updateStackMemory(resultPop);
        this->getWriteFile()
            << "// Finally pushing the result of the arithmetic operation"
            << endl;
        this->getWriteFile()
            << this->codeWritter.getPushAssembly("constant", resultPop);
        this->getWriteFile() << endl;
        break;
      case C_PUSH:
        this->memoryManager.updateStackMemory(this->parser.getArg2());
        this->getWriteFile()
            << "// Pushing " << std::to_string(this->parser.getArg2()) << endl;
        this->getWriteFile() << this->codeWritter.getPushAssembly(
            this->parser.getArg1(), this->parser.getArg2());
        this->getWriteFile() << endl;
        break;
      case C_POP:
        break;
      case C_LABEL:
        break;
      case C_GOTO:
        break;
      case C_IF:
        break;
      case C_FUNCTION:
        break;
      case C_RETURN:
        break;
      case C_CALL:
        break;
      default:
        break;
      }
    }
  }
}

void Control::setReadFile(string filepath) {
  if (std::filesystem::exists(filepath)) {
    this->readFile = ifstream(filepath);
  } else {
    cout << "ERROR AT READING FILE" << endl;
    exit(1);
  }
}
void Control::setWriteFile(string filepath) {
  this->writeFile = ofstream(filepath);
}
ifstream &Control::getReadFile() { return this->readFile; }
ofstream &Control::getWriteFile() { return this->writeFile; }
Control::~Control() {
  this->readFile.close();
  this->writeFile.close();
}
