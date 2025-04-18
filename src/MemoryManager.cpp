#include "MemoryManager.hpp"
#include <cassert>
#include <iostream>

MemoryManager::MemoryManager() {
  this->setConstantMemorySegment();
  this->setTempMemorySegment();
  this->setPointerMemorySegment();
}
MemoryManager::~MemoryManager() {}
void MemoryManager::setConstantMemorySegment(void) {
  for (int i = 0; i < CONSTANT_MEMORY_LENGTH; i++) {
    this->constantMemorySegment[i] = i;
  }
  assert(this->constantMemorySegment.at(0) == 0);
  assert(this->constantMemorySegment.at(CONSTANT_MEMORY_LENGTH - 1) ==
         CONSTANT_MEMORY_LENGTH - 1);
}
void MemoryManager::setPointerMemorySegment(void) {
  for (int i = 0; i < POINTER_MEMORY_LENGTH - 1; i++) {
    this->constantMemorySegment[i] = 0;
  }
}
void MemoryManager::setTempMemorySegment(void) {
  for (int i = 0; i < TEMP_MEMORY_LENGTH - 1; i++) {
    this->constantMemorySegment[i] = 0;
  }
}
void MemoryManager::setRamMemorySegment(void) {
  // if size() giving the top
  // using defautl stack or vector???
  this->ramMemory.at(0) = stackMemory.size();
  this->ramMemory.at(1) = localMemorySegment.pointer;
  this->ramMemory.at(2) = argumentMemorySegment.pointer;
  this->ramMemory.at(3) = thisMemorySegment.pointer;
  this->ramMemory.at(4) = thatMemorySegment.pointer;
}
