#include "Parser.hpp"
#include "Utilities.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
Parser::Parser(string filepath) {
  this->arg1 = "NONE";
  this->arg2 = -1;
  this->commandType = C_UNDEFINED;
  this->readFile = ifstream(filepath);
}
Parser::~Parser() { cout << "Removing parser" << endl; }

void Parser::operateCommand(string currentCommand) {
  Utility::setSplitCurrentCommand(currentCommand);
  this->setCommandType(
      Utility::getMapCArithmetic().at(Utility::getSplitCurrentCommand()[0]));
  if (this->commandType == C_ARITHMETIC) {
    this->setArg1(Utility::getSplitCurrentCommand()[0]);
    Utility::resetSplitCurrentCommand();
    return;
  }
  if (this->getCommandType() != C_RETURN) {
    this->setArg1(Utility::getSplitCurrentCommand()[1]);
    if (this->getCommandType() == C_PUSH || this->getCommandType() == C_POP ||
        this->getCommandType() == C_FUNCTION ||
        this->getCommandType() == C_CALL)
      this->setArg2(stoi(Utility::getSplitCurrentCommand()[2]));
  }
  Utility::resetSplitCurrentCommand();
}
void Parser::setArg1(string arg1) { this->arg1 = arg1; }
void Parser::setArg2(int arg2) { this->arg2 = arg2; }
void Parser::setCommandType(COMMAND_TYPE commandType) {
  this->commandType = commandType;
}
string Parser::getArg1() { return this->arg1; }
int Parser::getArg2() { return this->arg2; }
COMMAND_TYPE &Parser::getCommandType() { return this->commandType; }
