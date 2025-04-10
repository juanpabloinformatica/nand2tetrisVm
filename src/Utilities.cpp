#include "Utilities.hpp"
#include <memory>
Utility::Utility() {
  this->setMapCArithmetic();
  cout << "Constructor: " << &this->mapCArithmetic << endl;
}
Utility::~Utility() { cout << "Destroying Utilitiy" << endl; }

void Utility::setMapCArithmetic() {
  this->mapCArithmetic["add"] = C_ARITHMETIC;
  this->mapCArithmetic["sub"] = C_ARITHMETIC;
  this->mapCArithmetic["neg"] = C_ARITHMETIC;
  this->mapCArithmetic["eq"] = C_ARITHMETIC;
  this->mapCArithmetic["gt"] = C_ARITHMETIC;
  this->mapCArithmetic["lt"] = C_ARITHMETIC;
  this->mapCArithmetic["and"] = C_ARITHMETIC;
  this->mapCArithmetic["or"] = C_ARITHMETIC;
  this->mapCArithmetic["not"] = C_ARITHMETIC;
  this->mapCArithmetic["push"] = C_PUSH;
  this->mapCArithmetic["pop"] = C_POP;
  this->mapCArithmetic["label"] = C_LABEL;
  this->mapCArithmetic["goto"] = C_GOTO;
  // need to check what this expresion tries to do
  // this->mapCArithmetic["if-goto"] = C_GOTO;
  this->mapCArithmetic["if"] = C_IF;
  this->mapCArithmetic["function"] = C_FUNCTION;
  this->mapCArithmetic["return"] = C_RETURN;
  this->mapCArithmetic["call"] = C_CALL;
}
const map<string, COMMAND_TYPE> &Utility::getMapCArithmetic() {
  return this->mapCArithmetic;
}
const vector<string> &Utility::getSplitCurrentCommand() {
  return this->splittCurrentCommand;
}
void Utility::setSplitCurrentCommand(string currentCommand) {
  stringstream currentCommandStream = stringstream(currentCommand);
  string word;
  while (currentCommandStream >> word) {
    this->splittCurrentCommand.push_back(word);
  }
}
void Utility::resetSplitCurrentCommand() {
  for (auto &e : this->splittCurrentCommand) {
    e = "";
  }
}
// const vector<string> &Utility::splitCurrentCommand(string currentCommand) {
//
//   std::unique_ptr<vector<string>> ptrVector;
//   // vector<string> splittedCurrentCommand;
//   stringstream currentCommandStream = stringstream(currentCommand);
//   string word;
//   while (currentCommandStream >> word) {
//     // splittedCurrentCommand.push_back(word);
//     ptrVector->push_back(word);
//   }
//   // return splittedCurrentCommand;
//   return ptrVector;
// }
