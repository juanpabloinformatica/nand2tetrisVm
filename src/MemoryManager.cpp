#include "MemoryManager.hpp"

#include <cassert>
#include <iostream>

MemoryManager::MemoryManager() {
    initMSegments();

    // this->setTempMemorySegment();
    // this->setPointerMemorySegment();
    // this->setRamMemorySegment();
}

void MemoryManager::initMSegments() {
    for (int i = 0; i < 200; i++) {
        this->MSLocal.push_back(0);
        this->MSArgument.push_back(0);
        this->MSThat.push_back(0);
        this->MSThis.push_back(0);
        this->MSStatic.push_back(0);
        this->MSPointer.push_back(0);
        this->MSTemp.push_back(0);
    }
    // this->MSArgument[0] = 3;
    // this->MSArgument[1] = 3000;
}

MemoryManager::~MemoryManager() {}

// void MemoryManager::setPointerMemorySegment(void) {
//   for (int i = 0; i < POINTER_MEMORY_LENGTH - 1; i++) {
//     this->pointerMemorySegment[i] = 0;
//   }
// }
// void MemoryManager::setTempMemorySegment(void) {
//   for (int i = 0; i < TEMP_MEMORY_LENGTH - 1; i++) {
//     this->tempMemorySegment[i] = 0;
//   }
// }
// void MemoryManager::setRamMemorySegment(void) {
//   // if size() giving the top
//   // using defautl stack or vector??
//   this->ramMemory.at(0) = stackMemory.size();
//   this->ramMemory.at(1) = this->localMemorySegment.pointer;
//   this->ramMemory.at(2) = this->argumentMemorySegment.pointer;
//   this->ramMemory.at(3) = this->thisMemorySegment.pointer;
//   this->ramMemory.at(4) = this->thatMemorySegment.pointer;
//   this->ramMemory.at(5) = this->tempMemorySegment.at(0);
//   this->ramMemory.at(6) = this->tempMemorySegment.at(1);
// ""  this->ramMemory.at(7) = this->tempMemorySegment.at(2);
//   this->ramMemory.at(8) = this->tempMemorySegment.at(3);
//   this->ramMemory.at(9) = this->tempMemorySegment.at(4);
//   this->ramMemory.at(10) = this->tempMemorySegment.at(5);
//   this->ramMemory.at(11) = this->tempMemorySegment.at(6);
//   this->ramMemory.at(12) = this->tempMemorySegment.at(7);
//   // this->ramMemory.at(13) = 0;
//   // this->ramMemory.at(14) = 0;
//   // this->ramMemory.at(15) = 0;
// }
void MemoryManager::updateStackMemory(int value) {
    this->stackMemory.push(value);
}

// i need to check the order it means if for example
// gt is used is checking a > b or b > a??
int MemoryManager::popStack(string type) {
    int result = this->stackMemory.top();
    this->stackMemory.pop();
    if (type == "null") {
        return result;
    }
    // unary operations
    if (type == "not") {
        return ~result;
    }
    if (type == "neg") {
        return result * -1;
    }
    // binary operations
    if (type == "add") {
        result += this->stackMemory.top();
    } else if (type == "sub") {
        result = this->stackMemory.top() - result;
    } else if (type == "eq") {
        result = (result == this->stackMemory.top()) ? -1 : 0;
    } else if (type == "gt") {
        // result = (result > this->stackMemory.top()) ? -1 : 0;
        result = (this->stackMemory.top() > result) ? -1 : 0;
    } else if (type == "lt") {
        // result = (result < this->stackMemory.top()) ? -1 : 0;
        result = (this->stackMemory.top() < result) ? -1 : 0;
    } else if (type == "and") {
        result &= this->stackMemory.top();
    } else if (type == "or") {
        result |= this->stackMemory.top();
    }
    this->stackMemory.pop();
    return result;
}

void MemoryManager::showStack(void) {
    std::stack temp{ this->stackMemory };
    std::cout << "STACK" << std::endl;
    std::cout << "[" << std::endl;
    std::string toShow = "";
    while (temp.size()) {
        std::cout << " - " << temp.top() << '\n';
        temp.pop();
    }
    std::cout << "]" << std::endl;
}

string MemoryManager::showStack2(void) {
    std::stack temp{ this->stackMemory };
    string     result = std::string("//");
    result += "STACK";
    result += "\n";
    result += "[";
    while (temp.size()) {
        result += " - ";
        result += temp.top();
        result += "\n";
        temp.pop();
    }
    result += "]";
    return result;
}

int MemoryManager::getMemorySegmentMap(string _memorySegmentMap, int memorySegmentIndex) {
    // std::cout <<this->memorySegmentMap[_memorySegmentMap] + memorySegmentIndex
    // <<std::endl;
    return this->memorySegmentMap[_memorySegmentMap];
    // return this->memorySegmentMap[_memorySegmentMap];
}

void MemoryManager::updateMSLocal(int index, int value) {
    this->MSLocal[index] = value;
}

void MemoryManager::updateMSArgument(int index, int value) {
    this->MSArgument[index] = value;
}

void MemoryManager::updateMSThis(int index, int value) {
    this->MSThis[index] = value;
}

void MemoryManager::updateMSThat(int index, int value) {
    this->MSThat[index] = value;
}

void MemoryManager::updateMSStatic(int index, int value) {
    this->MSStatic[index] = value;
}

void MemoryManager::updateMSPointer(int index, int value) {
    this->MSPointer[index] = value;
}

void MemoryManager::updateMSTemp(int index, int value) {
    this->MSTemp[index] = value;
}

int MemoryManager::getMSLocal(int index) {
    return this->MSLocal[index];
}

int MemoryManager::getMSArgument(int index) {
    return this->MSArgument[index];
}

int MemoryManager::getMSThis(int index) {
    return this->MSThis[index];
}

int MemoryManager::getMSThat(int index) {
    return this->MSThat[index];
}

int MemoryManager::getMSStatic(int index) {
    return this->MSStatic[index];
}

int MemoryManager::getMSPointer(int index) {
    return this->MSPointer[index];
}

int MemoryManager::getMSTemp(int index) {
    return this->MSTemp[index];
}

// void MemoryManager::showMS(vector<int> &memorySegment) {
//   std::cout << "[" << std::endl;
//   for (int i = 0; i < memorySegment.size(); i++) {
//     std::cout << memorySegment[i] << std::endl;
//   }
//   std::cout << "]" << std::endl;
// }
