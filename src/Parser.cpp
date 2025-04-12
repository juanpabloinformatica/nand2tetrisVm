#include "Parser.hpp"
#include "Utilities.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
Parser::Parser() {
  this->arg1 = "NONE";
  this->arg2 = -1;
  this->commandType = C_UNDEFINED;
}
Parser::~Parser() { cout << "Removing parser" << endl; }

void Parser::operateCommand(string currentCommand) {
  // Utility u = Utility();
  Utility::setSplitCurrentCommand(currentCommand);
  cout << Utility::getMapCArithmetic().at("add") << endl;
  // this->setCommandType(
  //     Utility::getMapCArithmetic().at(Utility::getSplitCurrentCommand().at(0)));
  this->setCommandType(C_ARITHMETIC);
  // cout << this->getCommandType() << endl;
  if (this->commandType == C_ARITHMETIC) {
    this->setArg1(Utility::getSplitCurrentCommand().at(0));
    return;
  }
  if (this->getCommandType() != C_RETURN) {
    // this->setArg1(u.getSplitCurrentCommand().at(1));
    this->setArg1(Utility::getSplitCurrentCommand().at(1));
    if (this->getCommandType() == C_PUSH || this->getCommandType() == C_POP ||
        this->getCommandType() == C_FUNCTION ||
        this->getCommandType() == C_CALL)
      // this->setArg2(stoi(u.getSplitCurrentCommand().at(2)));
      this->setArg2(stoi(Utility::getSplitCurrentCommand().at(2)));
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
