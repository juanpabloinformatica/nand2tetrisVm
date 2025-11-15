#include "Control.hpp"

#include "Utilities.hpp"

#include <iostream>

Control::Control(string filepath) {
    this->parser                   = Parser();
    this->memoryManager            = MemoryManager();
    this->codeWritter              = CodeWritter();
    this->currentCommandLineNumber = 0;
    this->functionReturnCounter    = 0;
    this->actualFunction           = "";
    this->writeFileName            = "sys";
}

void Control::start_control(string & filepath) {
    this->filepathHandler(filepath);
}

/*To improve instead of using string use the class name*/
void Control::filepathHandler(string & filepath) {
    if (filepath.empty()) {
        return;
    }

    //abspath to avoid relative
    filepath = absolute(filepath);

    bool   isFile = is_regular_file(filepath) == true;
    string writeFilePath;
    int    delimeterIndex;
    delimeterIndex = filepath.find(".");

    if (isFile) {
        writeFilePath = filepath.substr(0, delimeterIndex) + ".asm";
    } else {
        int    directoryNameIndex = Utility::getDirectoryNameIndex(filepath);
        string directoryName =
            filepath.substr(directoryNameIndex, filepath.size() - 1);
        writeFilePath = filepath + directoryName + ".asm";
        cout << directoryName << endl;
        cout << writeFilePath << endl;
    }

    // this->setWriteFileName(writeFilePath);
    this->setWriteFile(writeFilePath);
    this->setBoostrapToWriteFile();

    isFile == true ? fileHandler(filepath) : directoryHandler(filepath);
}

string & Control::getWriteFileName() {
    return this->writeFileName;
}

void Control::fileHandler(const string & filepath) {
    if (!isVmFile(filepath)) {
        return;
    }

    cout << filepath << endl;

    int end   = filepath.find(".");
    int start = filepath.find_last_of("/");
    this->setWriteFileName(filepath.substr(start + 1, end - start - 1));
    this->setReadFile(filepath);
    traverseFile();
}

bool Control::isVmFile(const string & filepath) {
    string fileExt;
    int    delimeterIndex = Utility::fileExtensionDotIndex(filepath);
    fileExt               = filepath.substr(delimeterIndex, filepath.size());
    return fileExt == ".vm" ? true : false;
}

void Control::directoryHandler(const string & filepath) {
    for (const auto & dirEntry : recursive_directory_iterator(filepath)) {
        if (dirEntry.is_regular_file()) {
            this->fileHandler(dirEntry.path());
        }
    }
}

void Control::traverseFile() {
    int numberOfInstructions =
        this->codeWritter.getGlobalHackInstructionCounter();
    string currentCommand;
    int    resultPop;
    while (std::getline(this->readFile, currentCommand)) {
        currentCommand.erase(
            0, currentCommand.find_first_not_of(" \n\r\t"));  // left trim
        currentCommand.erase(currentCommand.find_last_not_of("\t\n\v\f\r ") +
                             1);                              // right trim
        if (currentCommand.substr(0, 2) != "//" && currentCommand != "") {
            this->parser.operateCommand(currentCommand);
            switch (this->parser.getCommandType()) {
                case C_ARITHMETIC:

                    cout << currentCommand << endl;
                    this->getWriteFile()
                        << "// Setting to 0 last 2 values and then pointing to "
                           "the n-1 "
                           "value for putting the result in there\n"
                        << endl
                        << "//" << currentCommand << endl;
                    this->getWriteFile()
                        << this->codeWritter.getArithmeticAssembly(
                               this->parser.getArg1());
                    this->getWriteFile() << endl;
                    resultPop =
                        this->memoryManager.popStack(this->parser.getArg1());
                    this->memoryManager.updateStackMemory(resultPop);
                    this->memoryManager.showStack();
                    break;
                case C_PUSH:
                    cout << currentCommand << endl;
                    int valueToPush;
                    if (this->parser.getArg1() == "constant") {
                        valueToPush = this->parser.getArg2();
                    } else if (this->parser.getArg1() == "local") {
                        valueToPush = this->memoryManager.getMSLocal(
                            this->parser.getArg2());
                    } else if (this->parser.getArg1() == "argument") {
                        valueToPush = this->memoryManager.getMSArgument(
                            this->parser.getArg2());
                    } else if (this->parser.getArg1() == "this") {
                        valueToPush = this->memoryManager.getMSThis(
                            this->parser.getArg2());
                    } else if (this->parser.getArg1() == "that") {
                        valueToPush = this->memoryManager.getMSThat(
                            this->parser.getArg2());
                    } else if (this->parser.getArg1() == "static") {
                        valueToPush = this->memoryManager.getMSStatic(
                            this->parser.getArg2());
                    } else if (this->parser.getArg1() == "pointer") {
                        valueToPush = this->memoryManager.getMSPointer(
                            this->parser.getArg2());
                    } else if (this->parser.getArg1() == "temp") {
                        valueToPush = this->memoryManager.getMSTemp(
                            this->parser.getArg2());
                    } else {
                        valueToPush = 0;
                        std::cout << ".vm file incorrect" << std::endl;
                        exit(0);
                    }
                    this->memoryManager.updateStackMemory(valueToPush);
                    this->getWriteFile() << endl
                                         << "//" << currentCommand << endl;
                    this->getWriteFile()
                        << this->codeWritter.getPushAssembly(
                               this->writeFileName, this->parser.getArg1(),
                               this->parser.getArg2(), 13)
                        << endl;
                    std::cout << "Pushing Once" << std::endl;
                    this->memoryManager.showStack();
                    break;
                case C_POP:
                    cout << currentCommand << endl;
                    this->getWriteFile() << endl
                                         << "//" << currentCommand << endl;
                    resultPop = this->memoryManager.popStack();
                    if (this->parser.getArg1() == "local") {
                        this->memoryManager.updateMSLocal(
                            this->parser.getArg2(), resultPop);
                    } else if (this->parser.getArg1() == "argument") {
                        this->memoryManager.updateMSArgument(
                            this->parser.getArg2(), resultPop);
                    } else if (this->parser.getArg1() == "this") {
                        this->memoryManager.updateMSThis(this->parser.getArg2(),
                                                         resultPop);
                    } else if (this->parser.getArg1() == "that") {
                        this->memoryManager.updateMSThat(this->parser.getArg2(),
                                                         resultPop);
                    } else if (this->parser.getArg1() == "static") {
                        this->memoryManager.updateMSStatic(
                            this->parser.getArg2(), resultPop);
                    } else if (this->parser.getArg1() == "pointer") {
                        this->memoryManager.updateMSPointer(
                            this->parser.getArg2(), resultPop);
                    } else if (this->parser.getArg1() == "temp") {
                        this->memoryManager.updateMSTemp(this->parser.getArg2(),
                                                         resultPop);
                    } else {
                        std::cout << ".vm file incorrect" << std::endl;
                        exit(0);
                    }
                    this->getWriteFile()
                        << this->codeWritter.getPopAssembly(
                               this->writeFileName, this->parser.getArg1(),
                               this->parser.getArg2(), 13, 14)
                        << endl;

                    this->memoryManager.showStack();
                    break;
                case C_LABEL:
                    cout << currentCommand << endl;
                    this->getWriteFile() << endl
                                         << "//" << currentCommand << endl;
                    cout << "________________" << endl;
                    cout << this->parser.getArg1() << endl;
                    this->getWriteFile()
                        << this->codeWritter.getWriteLabelTemplate(
                               this->parser.getArg1())
                        << endl;
                    cout << "________________" << endl;
                    break;
                case C_GOTO:
                    /*To check*/
                    cout << currentCommand << endl;
                    this->getWriteFile() << endl
                                         << "//" << currentCommand << endl;
                    cout << "________________" << endl;
                    cout << this->parser.getArg1() << endl;
                    this->getWriteFile()
                        << this->codeWritter.getWriteGotoTemplate(
                               this->parser.getArg1())
                        << endl;
                    cout << "________________" << endl;
                    break;
                case C_IF:
                    cout << currentCommand << endl;
                    this->getWriteFile() << endl
                                         << "//" << currentCommand << endl;
                    cout << "________________" << endl;
                    this->memoryManager.popStack();
                    cout << this->parser.getArg1() << endl;
                    this->getWriteFile()
                        << this->codeWritter.getWriteIfTemplate(
                               this->parser.getArg1())
                        << endl;
                    cout << "________________" << endl;
                    break;
                case C_FUNCTION:
                    //this will updated and gott the name from the function
                    cout << currentCommand << endl;
                    this->getWriteFile() << endl
                                         << "//" << currentCommand << endl;
                    cout << "________________" << endl;
                    cout << this->parser.getArg1() << endl;

                    this->getWriteFile()
                        << this->codeWritter.getWriteFunctionAssembly(
                               this->parser.getArg1(),
                               std::to_string(this->parser.getArg2()));

                    break;
                case C_RETURN:
                    cout << currentCommand << endl;
                    this->getWriteFile() << endl
                                         << "//" << currentCommand << endl;
                    cout << "________________" << endl;
                    cout << this->parser.getArg1() << endl;
                    this->getWriteFile()
                        << this->codeWritter.getWriteReturnAssembly() << endl;
                    break;
                case C_CALL:
                    this->actualFunction = this->parser.getArg1();
                    // this->setWriteFileName(this->parser.getArg1().substr(
                    //     0, parser.getArg1().find(".")));
                    cout << "delimeter" << endl;
                    cout << "IN CALL COMMAND\n"
                         << currentCommand << "\nFilename:\t"
                         << this->writeFileName << endl;
                    cout << "delimeter" << endl;
                    cout << currentCommand << endl;
                    this->getWriteFile() << endl
                                         << "//" << currentCommand << endl;
                    cout << "________________" << endl;
                    cout << this->parser.getArg1() << endl;
                    this->getWriteFile()
                        << this->codeWritter.getWriteCallTemplate(
                               std::to_string(this->parser.getArg2()),
                               this->actualFunction)
                        << endl;
                    cout << "________________" << endl;
                    break;
                default:
                    break;
            }
            this->currentCommandLineNumber++;
        }
        if (!std::regex_match(currentCommand, std::regex(R"(^\/\/.*|^\s*$)"))) {
            this->getWriteFile()
                << "//instructions:\t"
                << this->codeWritter.getGlobalHackInstructionCounter() -
                       numberOfInstructions;
        }
        numberOfInstructions =
            this->codeWritter.getGlobalHackInstructionCounter();
    }
    /*This will be removed*/
    this->getWriteFile() << "// TOTAL LINES:"
                         << this->codeWritter.getGlobalHackInstructionCounter()
                         << endl;
    this->getWriteFile() << "//END OF FILE" << endl;
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
    /*
     * Initialised with boostrap code
     * */
    cout << "IN SET WRITE FILE" << endl;
    cout << filepath << endl;
    this->writeFile = ofstream(filepath);
}

void Control::setBoostrapToWriteFile(void) {
    cout << "Entering in boostrap" << endl;
    this->getWriteFile() << this->codeWritter.getWriteInitAssembly() << endl;
}

void Control::setWriteFileName(string filepath) {
    // int indexSeparator     = filePath.size() - 1;
    // int indexFileExtension = filePath.size() - 1;
    // for (; indexSeparator > 0 && filePath.at(indexSeparator) != '/';
    //      indexSeparator--)
    //     ;
    // for (; indexFileExtension > 0 && filePath.at(indexFileExtension) != '.';
    //      indexFileExtension--)
    //     ;
    // this->writeFileName =
    //     (indexFileExtension > 0 && indexSeparator > 0) ?
    //         filePath.substr(indexSeparator + 1,
    //                         indexFileExtension - indexSeparator - 1) :
    //         NULL;
    // cout << "FILE NAME:\t" << this->writeFileName << endl;
    this->writeFileName = filepath;
}

ifstream & Control::getReadFile() {
    return this->readFile;
}

ofstream & Control::getWriteFile() {
    return this->writeFile;
}

Control::~Control() {
    this->readFile.close();
    this->writeFile.close();
}
