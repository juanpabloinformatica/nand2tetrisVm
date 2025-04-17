#include "Control.hpp"
#include <iostream>
Control::Control(string filepath) {
  this->setReadFile(filepath);
  int indexDelimeter = filepath.find(".");
  string writeFilePath = filepath.substr(0, indexDelimeter) + ".hack";
  this->setWriteFile(writeFilePath);
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
