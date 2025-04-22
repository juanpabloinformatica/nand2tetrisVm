#include "Control.hpp"
#include <iostream>
Control::Control(string filepath) {
  this->setReadFile(filepath);
  int indexDelimeter = filepath.find(".");
  string writeFilePath = filepath.substr(0, indexDelimeter) + ".hack";
  this->setWriteFile(writeFilePath);
  this->parser = Parser();
  // learning about error of having the destructor
  this->codeWritter = CodeWritter();
  this->memoryManager = MemoryManager();

  MemoryManager memoryManager;
}
void Control::traverseFile() {
  string currentCommand;
  while (std::getline(this->readFile, currentCommand)) {
    this->parser.operateCommand(currentCommand);
    switch (this->parser.getCommandType()) {
    case C_ARITHMETIC:
      break;
    case C_PUSH:
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

    // if (this->parser.getCommandType() == C_ARITHMETIC) {
    //
    // } else if (this->parser.getCommandType() == C_PUSH) {
    // }
  }
}

void Control::setReadFile(string filepath) {
  this->readFile = ifstream(filepath);
  std::cout << "checking if file exist and assigned" << std::endl;
  std::cout << this->readFile.good() << std::endl;
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
