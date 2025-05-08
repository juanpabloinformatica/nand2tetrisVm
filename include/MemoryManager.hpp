#ifndef __MEMORY_MANAGER__
#define __MEMORY_MANAGER__
#include <array>
#include <stack>
#include <string>
#include <vector>
#define CONSTANT_MEMORY_LENGTH 32768
#define POINTER_MEMORY_LENGTH 2
#define TEMP_MEMORY_LENGTH 8
#define RAM_MEMORY_LENGTH 24575
using std::array;
using std::stack;
using std::string;
using std::vector;
class MemoryManager {
private:
  // class MemorySegment {
  // public:
  //   MemorySegment() : segment{}, pointer(0) {};
  //   vector<int> segment;
  //   int pointer;
  // };
  // I think will desiggn this better :)))))))
  stack<int> stackMemory;
  // vector<int> staticMemorySegment;
  // vector<int> argumentMemorySegment;
  // MemorySegment argumentMemorySegment;
  // vector<int> localMemorySegment;
  // MemorySegment localMemorySegment;
  // MemorySegment thisMemorySegment;
  // vector<int> thisMemorySegment;
  // MemorySegment thatMemorySegment;
  // vector<int> thatMemorySegment;
  // array<int, CONSTANT_MEMORY_LENGTH> constantMemorySegment;
  // array<int, POINTER_MEMORY_LENGTH> pointerMemorySegment;
  // array<int, TEMP_MEMORY_LENGTH> tempMemorySegment;
  // everything will be passed to this
  // this could be better by doing it inmediately I could do it like that as
  // well
  // array<int, RAM_MEMORY_LENGTH> ramMemory;

public:
  MemoryManager();
  ~MemoryManager();
  // void setPointerMemorySegment(void);
  // void setTempMemorySegment(void);
  // void setRamMemorySegment(void);
  void updateStackMemory(int value);
  int popStack(string type);
};
#endif
