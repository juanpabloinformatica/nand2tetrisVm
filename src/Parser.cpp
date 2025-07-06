#include "Parser.hpp"
#include <sstream>
Parser::Parser() {
  this->arg1 = "NONE";
  this->arg2 = -1;
  // this->commandType = C_UNDEFINED;
  this->setMapCommand();
}
Parser::~Parser() { cout << "Removing parser" << endl; }

void Parser::operateCommand(string currentCommand) {
  this->setSplitCurrentCommand(currentCommand);
  this->setCommandType(
      this->getMapCommand().at(this->getSplitCurrentCommand()[0]));
  if (this->commandType == C_ARITHMETIC) {
    this->setArg1(this->getSplitCurrentCommand()[0]);
    this->resetSplitCurrentCommand();
    return;
  }
  if (this->getCommandType() != C_RETURN) {
    this->setArg1(this->getSplitCurrentCommand()[1]);
    if (this->getCommandType() == C_PUSH || this->getCommandType() == C_POP ||
        this->getCommandType() == C_FUNCTION ||
        this->getCommandType() == C_CALL) {
      this->setArg2(stoi(this->getSplitCurrentCommand()[2]));
    }
  }
  this->resetSplitCurrentCommand();
}
void Parser::setArg1(string arg1) { this->arg1 = arg1; }
void Parser::setArg2(int arg2) { this->arg2 = arg2; }
void Parser::setCommandType(COMMAND_TYPE commandType) {
  this->commandType = commandType;
}
void Parser::setMapCommand() {
  this->mapCommand["sub"] = C_ARITHMETIC;
  this->mapCommand["add"] = C_ARITHMETIC;
  this->mapCommand["neg"] = C_ARITHMETIC;
  this->mapCommand["eq"] = C_ARITHMETIC;
  this->mapCommand["gt"] = C_ARITHMETIC;
  this->mapCommand["lt"] = C_ARITHMETIC;
  this->mapCommand["and"] = C_ARITHMETIC;
  this->mapCommand["or"] = C_ARITHMETIC;
  this->mapCommand["not"] = C_ARITHMETIC;
  this->mapCommand["push"] = C_PUSH;
  this->mapCommand["pop"] = C_POP;
  this->mapCommand["label"] = C_LABEL;
  this->mapCommand["goto"] = C_GOTO;
  this->mapCommand["if-goto"] = C_IF;
  this->mapCommand["function"] = C_FUNCTION;
  this->mapCommand["return"] = C_RETURN;
  this->mapCommand["call"] = C_CALL;
}
void Parser::resetSplitCurrentCommand() {
  this->splitCurrentCommand[0] = "";
  this->splitCurrentCommand[1] = "";
  this->splitCurrentCommand[2] = "";
}
void Parser::setSplitCurrentCommand(string currentCommand) {
  stringstream currentCommandStream = stringstream(currentCommand);
  string word;
  int i = 0;
  while (currentCommandStream >> word && word != "//") {
    this->splitCurrentCommand[i++] = word;
  }
}
const map<string, COMMAND_TYPE> &Parser::getMapCommand() {
  return this->mapCommand;
}
const array<string, ARRAY_LENGTH> &Parser::getSplitCurrentCommand() {
  return this->splitCurrentCommand;
}
string Parser::getArg1() { return this->arg1; }
int Parser::getArg2() { return this->arg2; }
COMMAND_TYPE &Parser::getCommandType() { return this->commandType; }
