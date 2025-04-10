#include "Parser.hpp"
#include "Utilities.hpp"
int main() {
  Utility util = Utility();
  // cout << " from Main Reference:" << &util.getMapCArithmetic() << endl;
  // for (auto &[k, value] : util.getMapCArithmetic()) {
  //   cout << "Key: " << k << "Value: " << value << endl;
  // }
  Parser p = Parser();
  p.operateCommand("add");
  cout << "add" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("sub");
  cout << "sub" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("eq");
  cout << "eq" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("gt");
  cout << "gt" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("eq");
  cout << "eq" << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("lt");
  cout << "lt" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("and");
  cout << "and" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("or");
  cout << "or" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("not");
  cout << "not" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("pop temp 0");
  cout << "pop temp 0" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("push local 1");
  cout << "push local 1" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("label IF_FALSE0");
  cout << "label IF_FALSE0" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("goto IF_FALSE0");
  cout << "goto IF_FALSE0" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("function Array.dispose 0");
  cout << "function Array.dispose 0" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("return");
  cout << "function Array.dispose 0" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;

  p.operateCommand("call Memory.deAlloc 1");
  cout << "call Memory.deAlloc 1" << endl;
  cout << p.getCommandType() << endl;
  cout << p.getArg1() << endl;
  cout << p.getArg2() << endl;
}

// Constructor: 0x7ffe0ed35f20
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// add
// 1
// add
// -1
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// sub
// 1
// sub
// -1
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// eq
// 1
// eq
// -1
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// gt
// 1
// gt
// -1
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// eq
// eq
// -1
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// lt
// 1
// lt
// -1
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// and
// 1
// and
// -1
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// or
// 1
// or
// -1
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// not
// 1
// not
// -1
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// pop temp 0
// 3
// temp
// 0
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// push local 1
// 2
// local
// 1
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// label IF_FALSE0
// 4
// IF_FALSE0
// 1
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// goto IF_FALSE0
// 5
// IF_FALSE0
// 1
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// function Array.dispose 0
// 7
// Array.dispose
// 0
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// function Array.dispose 0
// 8
// Array.dispose
// 0
// Constructor: 0x7ffe0ed35df0
// Destroying Utilitiy
// call Memory.deAlloc 1
// 9
// Memory.deAlloc
// 1
// Removing parser
// Destroying Utilitiy
