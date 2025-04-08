#include "Utilities.hpp"
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
