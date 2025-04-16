#include "Control.hpp"
Control::Control(string filepath) {
  this->setReadFile(filepath);
  int indexDelimeter = filepath.find(".");
  string writeFilePath = filepath.substr(0, indexDelimeter) + ".hack";
  this->setWriteFile(writeFilePath);
}
const ifstream &Control::getReadFile() { return this->readFile; }

void Control::setReadFile(string filepath) {
  this->readFile = ifstream(filepath);
}
void Control::setWriteFile(string filepath) {
  this->writeFile = ofstream(filepath);
}
Control::~Control() {
  this->readFile.close();
  this->writeFile.close();
}
