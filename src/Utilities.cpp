#include "Utilities.hpp"
map<string, COMMAND_TYPE> Utility::mapCArithmetic;

vector<string> Utility::splittCurrentCommand;

void Utility::setMapCArithmetic() {
  mapCArithmetic["sub"] = C_ARITHMETIC;
  mapCArithmetic["add"] = C_ARITHMETIC;
  mapCArithmetic["neg"] = C_ARITHMETIC;
  mapCArithmetic["eq"] = C_ARITHMETIC;
  mapCArithmetic["gt"] = C_ARITHMETIC;
  mapCArithmetic["lt"] = C_ARITHMETIC;
  mapCArithmetic["and"] = C_ARITHMETIC;
  mapCArithmetic["or"] = C_ARITHMETIC;
  mapCArithmetic["not"] = C_ARITHMETIC;
  mapCArithmetic["push"] = C_PUSH;
  mapCArithmetic["pop"] = C_POP;
  mapCArithmetic["label"] = C_LABEL;
  mapCArithmetic["goto"] = C_GOTO;
  // need to check what this expresion tries to do
  // this->mapCArithmetic["if-goto"] = C_GOTO;
  mapCArithmetic["if"] = C_IF;
  mapCArithmetic["function"] = C_FUNCTION;
  mapCArithmetic["return"] = C_RETURN;
  mapCArithmetic["call"] = C_CALL;
}
const map<string, COMMAND_TYPE> &Utility::getMapCArithmetic() {
  return mapCArithmetic;
}
const vector<string> &Utility::getSplitCurrentCommand() {
  return splittCurrentCommand;
}
void Utility::setSplitCurrentCommand(string currentCommand) {
  stringstream currentCommandStream = stringstream(currentCommand);
  string word;
  while (currentCommandStream >> word) {
    splittCurrentCommand.push_back(word);
  }
}
void Utility::resetSplitCurrentCommand() {
  for (auto &e : splittCurrentCommand) {
    e = "";
  }
}
string Utility::getFilepath(string file) {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string filepath =
      cwd.string() + std::string("/") + "testFiles" + std::string("/") + file;
  return filepath;
}
