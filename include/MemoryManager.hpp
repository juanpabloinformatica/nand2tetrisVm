#ifndef __MEMORY_MANAGER__
#define __MEMORY_MANAGER__
#include <array>
#include <map>
#include <stack>
#include <string>
#include <vector>
#define CONSTANT_MEMORY_LENGTH 32768
#define POINTER_MEMORY_LENGTH 2
#define TEMP_MEMORY_LENGTH 8
#define RAM_MEMORY_LENGTH 24575
const int NOT_DYN_MEMORY_SEGMENT_MIN_INDEX = 0;
const int NOT_DYN_MEMORY_SEGMENT_MAX_INDEX = 4;
const int POINTER_MEMORY_SEGMENT_MIN_INDEX = 3;
const int POINTER_MEMORY_SEGMENT_MAX_INDEX = 4;
const int TEMP_MEMORY_SEGMENT_MIN_INDEX = 5;
const int TEMP_MEMORY_SEGMENT_MAX_INDEX = 12;
const int STATIC_MEMORY_SEGMENT_MIN_INDEX = 16;
const int STATIC_MEMORY_SEGMENT_MAX_INDEX = 256;
const int GPR_MIN_INDEX = 13;
const int GPR_MAX_INDEX = 15;
using std::array;
using std::map;
using std::stack;
using std::string;
using std::vector;
class MemoryManager {
private:
  stack<int> stackMemory;
  int staticIndex{16};
  int tempIndex{5};
  int pointerIndex{3};
  map<string, int> memorySegmentMap{{"stack", 0},
                                    {"local", 1},
                                    {"argument", 2},
                                    {"this", 3},
                                    {"that", 4},
                                    {"pointer", pointerIndex},
                                    {"temp", tempIndex},
                                    // {"constant", 5},
                                    {"static", staticIndex},
                                    {"constant", 874}};
  vector<int> MSLocal;
  vector<int> MSArgument;
  vector<int> MSThis;
  vector<int> MSThat;
  vector<int> MSStatic;
  vector<int> MSPointer;
  vector<int> MSTemp;

public:
  MemoryManager();
  ~MemoryManager();
  int getMemorySegmentMap(string _memorySegmentMap, int memorySegmentIndex = 0);
  vector<int> &getMSLocal(void);
  vector<int> &getMSArgument(void);
  vector<int> &getMSThis(void);
  vector<int> &getMSThat(void);
  vector<int> &getMSStatic(void);
  vector<int> &getMSPointer(void);
  vector<int> &getMSTemp(void);
  void updateMSLocal(int index, int value);
  void updateMSArgument(int index, int value);
  void updateMSThis(int index, int value);
  void updateMSThat(int index, int value);
  void updateMSConstant(int index, int value);
  void updateMSStatic(int index, int value);
  void updateMSPointer(int index, int value);
  void updateMSTemp(int index, int value);
  void updateStackMemory(int value);
  // if is not push is pop
  void updateMemorySegmentMap(string _memorySegmentMap, bool isPush);
  int popStack(string type = "null");
  int getMSLocal(int index);
  int getMSArgument(int index);
  int getMSThis(int index);
  int getMSThat(int index);
  int getMSConstant(int index);
  int getMSStatic(int index);
  int getMSPointer(int index);
  int getMSTemp(int index);
  void initMSegments();
  void showStack();
  void showMS(vector<int> &memorySegment);
};
#endif
