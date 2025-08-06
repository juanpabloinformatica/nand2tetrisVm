#include "Control.hpp"
#include <iostream>
#include "Utilities.hpp"
Control::Control(string filepath) {
  if (filepath != "") {
    this->setReadFile(filepath);
    int indexDelimeter = filepath.find(".");
    if (std::filesystem::exists(filepath)) {
      string writeFilePath = filepath.substr(0, indexDelimeter) + ".asm";
      this->setWriteFile(writeFilePath);
    } else {
      cout << "Not working path" << endl;
      exit(EXIT_FAILURE);
    }
  }
  this->parser = Parser();
  this->memoryManager = MemoryManager();
  this->codeWritter = CodeWritter();
}
void Control::traverseFile() {
  string currentCommand;
  int resultPop;
  while (std::getline(this->readFile, currentCommand)) {
    currentCommand.erase(
        0, currentCommand.find_first_not_of(" \n\r\t"));  // left trim
    currentCommand.erase(currentCommand.find_last_not_of("\t\n\v\f\r ") +
                         1);  // right trim
    if (currentCommand.substr(0, 2) != "//" && currentCommand != "") {
      this->parser.operateCommand(currentCommand);
      switch (this->parser.getCommandType()) {

        case C_ARITHMETIC:

          cout << currentCommand << endl;
          this->getWriteFile()
              << "// Setting to 0 last 2 values and then pointing to the n-1 "
                 "value for putting the result in there\n"
              << "//" << currentCommand << endl;
          this->getWriteFile() << this->codeWritter.getArithmeticAssembly(
              this->parser.getArg1());
          this->getWriteFile() << endl;
          resultPop = this->memoryManager.popStack(this->parser.getArg1());
          this->memoryManager.updateStackMemory(resultPop);
          // this->getWriteFile()
          //     << "// Finally pushing the result of the arithmetic operation\n"
          //     << endl;
          // this->getWriteFile()
          //     << this->codeWritter.getPushAssembly("constant", resultPop, 13);
          // if (this->parser.getArg1() != "not" ||
          //     this->parser.getArg1() != "neg") {
          //   std::cout << "Popped twice" << std::endl;
          // } else {
          //   std::cout << "Popped once" << std::endl;
          // }
          this->memoryManager.showStack();
          // this->getWriteFile () << "Stack\n"
          //<< this->memoryManager.showStack2 () << endl;
          break;
        case C_PUSH:
          cout << currentCommand << endl;
          int valueToPush;
          if (this->parser.getArg1() == "constant") {
            valueToPush = this->parser.getArg2();
            // this->memoryManager.updateStackMemory(valueToPush);
          } else if (this->parser.getArg1() == "local") {
            valueToPush =
                this->memoryManager.getMSLocal(this->parser.getArg2());
          } else if (this->parser.getArg1() == "argument") {
            valueToPush =
                this->memoryManager.getMSArgument(this->parser.getArg2());
          } else if (this->parser.getArg1() == "this") {
            valueToPush = this->memoryManager.getMSThis(this->parser.getArg2());
          } else if (this->parser.getArg1() == "that") {
            valueToPush = this->memoryManager.getMSThat(this->parser.getArg2());
          } else if (this->parser.getArg1() == "static") {
            valueToPush =
                this->memoryManager.getMSStatic(this->parser.getArg2());
          } else if (this->parser.getArg1() == "pointer") {
            valueToPush =
                this->memoryManager.getMSPointer(this->parser.getArg2());
          } else if (this->parser.getArg1() == "temp") {
            valueToPush = this->memoryManager.getMSTemp(this->parser.getArg2());
          } else {
            valueToPush = 0;
            std::cout << ".vm file incorrect" << std::endl;
            exit(0);
          }
          this->memoryManager.updateStackMemory(valueToPush);
          this->getWriteFile() << "//" << currentCommand << endl;
          this->getWriteFile()
              << this->codeWritter.getPushAssembly(this->parser.getArg1(),
                                                   this->parser.getArg2(), 13)
              << endl;
          std::cout << "Pushing Once" << std::endl;
          this->memoryManager.showStack();
          // this->getWriteFile () << "Stack\n"
          //<< this->memoryManager.showStack2 () << endl;
          break;
        case C_POP:
          cout << currentCommand << endl;
          this->getWriteFile() << "//" << currentCommand << endl;
          resultPop = this->memoryManager.popStack();
          if (this->parser.getArg1() == "local") {
            this->memoryManager.updateMSLocal(this->parser.getArg2(),
                                              resultPop);
          } else if (this->parser.getArg1() == "argument") {
            this->memoryManager.updateMSArgument(this->parser.getArg2(),
                                                 resultPop);
          } else if (this->parser.getArg1() == "this") {
            this->memoryManager.updateMSThis(this->parser.getArg2(), resultPop);
          } else if (this->parser.getArg1() == "that") {
            this->memoryManager.updateMSThat(this->parser.getArg2(), resultPop);
          } else if (this->parser.getArg1() == "static") {
            this->memoryManager.updateMSStatic(this->parser.getArg2(),
                                               resultPop);
          } else if (this->parser.getArg1() == "pointer") {
            this->memoryManager.updateMSPointer(this->parser.getArg2(),
                                                resultPop);
          } else if (this->parser.getArg1() == "temp") {
            this->memoryManager.updateMSTemp(this->parser.getArg2(), resultPop);
          } else {
            std::cout << ".vm file incorrect" << std::endl;
            exit(0);
          }
          this->getWriteFile()
              << this->codeWritter.getPopAssembly(
                     this->parser.getArg1(), this->parser.getArg2(), 13, 14)
              << endl;

          // this->memoryManager.popStack();
          this->memoryManager.showStack();
          // this->getWriteFile () << "Stack\n"
          //<< this->memoryManager.showStack2 () << endl;
          break;
        case C_LABEL:
          cout << currentCommand << endl;
          this->getWriteFile() << "//" << currentCommand << endl;
          cout << "________________" << endl;
          cout << this->parser.getArg1() << endl;
          this->getWriteFile()
              << this->codeWritter.getWriteLabelTemplate(this->parser.getArg1())
              << endl;
          cout << "________________" << endl;
          // this->getWriteFile () << "Stack\n"
          //<< this->memoryManager.showStack2 () << endl;
          // this->getWriteFile () << "Stack\n"
          //<< this->memoryManager.showStack2 () << endl;
          break;
        case C_GOTO:
          cout << currentCommand << endl;
          this->getWriteFile() << "//" << currentCommand << endl;
          cout << "________________" << endl;
          cout << this->parser.getArg1() << endl;
          this->getWriteFile()
              << this->codeWritter.getWriteGotoTemplate(this->parser.getArg1())
              << endl;
          cout << "________________" << endl;
          // this->getWriteFile () << "Stack\n"
          //<< this->memoryManager.showStack2 () << endl;
          break;
        case C_IF:
          cout << currentCommand << endl;
          // parser is working?????
          this->getWriteFile() << "//" << currentCommand << endl;
          cout << "________________" << endl;
          this->memoryManager.popStack();
          cout << this->parser.getArg1() << endl;
          this->getWriteFile()
              << this->codeWritter.getWriteIfTemplate(this->parser.getArg1())
              << endl;
          cout << "________________" << endl;
          // this->getWriteFile () << "Stack\n"
          //<< this->memoryManager.showStack2 () << endl;
          break;
        case C_FUNCTION:
          break;
        case C_RETURN:
          break;
        case C_CALL:
          break;
        default:
          break;
      }
    }
  }
}

void Control::setReadFile(string filepath) {
  if (std::filesystem::exists(filepath)) {
    this->readFile = ifstream(filepath);
  } else {
    cout << "ERROR AT READING FILE" << endl;
    exit(1);
  }
}
void Control::setWriteFile(string filepath) {
  this->writeFile = ofstream(filepath);
}
ifstream& Control::getReadFile() {
  return this->readFile;
}
ofstream& Control::getWriteFile() {
  return this->writeFile;
}
Control::~Control() {
  this->readFile.close();
  this->writeFile.close();
}
