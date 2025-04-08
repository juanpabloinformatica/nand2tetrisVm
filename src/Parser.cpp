#include "Parser.hpp"
Parser::Parser() {
  this->arg1 = "";
  this->arg2 = -1;
}
Parser::~Parser() { cout << "Removing parser" << endl; }

void Parser::setArg1(string arg1) { this->arg1 = arg1; }
void Parser::setArg2(int arg2) { this->arg2 = arg2; }
