#include "MemoryManager.hpp"

#include <cassert>
#include <iostream>

MemoryManager::MemoryManager() {
    initMSegments();
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
}

MemoryManager::~MemoryManager() {}

void MemoryManager::updateStackMemory(int value) {
    this->stackMemory.push(value);
}

int MemoryManager::popStack(string type) {
    int result = this->stackMemory.top();
    this->stackMemory.pop();
    if (type == "null") {
        return result;
    }
    if (type == "not") {
        return ~result;
    }
    if (type == "neg") {
        return result * -1;
    }
    if (type == "add") {
        result += this->stackMemory.top();
    } else if (type == "sub") {
        result = this->stackMemory.top() - result;
    } else if (type == "eq") {
        result = (result == this->stackMemory.top()) ? -1 : 0;
    } else if (type == "gt") {
        result = (this->stackMemory.top() > result) ? -1 : 0;
    } else if (type == "lt") {
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
    return this->memorySegmentMap[_memorySegmentMap];
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
