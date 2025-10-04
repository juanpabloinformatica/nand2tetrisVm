#include "TestParser.hpp"

#include <fstream>
#include <string>

void testParser(std::string filename) {
    Parser  p = Parser();
    Control c = Control(Utility::getFilepath(filename));
    string  text;
    //  while (std::getline(c.getReadFile(), text)) {
    //    cout << text << endl;
    //  }
    //
    //  exit(0);

    p.operateCommand("add");
    assert(p.getCommandType() == C_ARITHMETIC);
    assert(p.getArg1() == "add");
    p.operateCommand("sub");
    assert(p.getCommandType() == C_ARITHMETIC);
    assert(p.getArg1() == "sub");
    p.operateCommand("eq");
    assert(p.getCommandType() == C_ARITHMETIC);
    assert(p.getArg1() == "eq");
    p.operateCommand("gt");
    assert(p.getCommandType() == C_ARITHMETIC);
    assert(p.getArg1() == "gt");
    p.operateCommand("eq");
    assert(p.getCommandType() == C_ARITHMETIC);
    assert(p.getArg1() == "eq");
    p.operateCommand("lt");
    assert(p.getCommandType() == C_ARITHMETIC);
    assert(p.getArg1() == "lt");
    p.operateCommand("and");
    assert(p.getCommandType() == C_ARITHMETIC);
    assert(p.getArg1() == "and");
    p.operateCommand("or");
    assert(p.getCommandType() == C_ARITHMETIC);
    assert(p.getArg1() == "or");
    p.operateCommand("not");
    assert(p.getCommandType() == C_ARITHMETIC);
    assert(p.getArg1() == "not");

    p.operateCommand("pop temp 0");
    assert(p.getArg1() == "temp");
    assert(p.getArg2() == 0);
    p.operateCommand("push local 1");
    assert(p.getArg1() == "local");
    assert(p.getArg2() == 1);

    p.operateCommand("label IF_FALSE0");
    p.operateCommand("goto IF_FALSE0");

    p.operateCommand("function Array.dispose 0");
    assert(p.getArg1() == "Array.dispose");
    assert(p.getArg2() == 0);
    p.operateCommand("return");

    p.operateCommand("call Memory.deAlloc 1");
    assert(p.getArg1() == "Memory.deAlloc");
    assert(p.getArg2() == 1);
}
