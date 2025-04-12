#include "CodeWritter.hpp"

CodeWritter::CodeWritter() {}
void CodeWritter::setFileName(string fileName) {
  string filepath = Utility::getFilepath(fileName);
  this->writeFile = ofstream(filepath);
}
// i am writting slower because I am trying to get use to new things such as
// using <C-[> instead of jj i am using tricks in insert mode
