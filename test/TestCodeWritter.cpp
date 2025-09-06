#include "TestCodeWritter.hpp"
#include <string>
#include "CodeWritter.hpp"
#include "gtest/gtest.h"

void TestCodeWritter::SetUp() {
  this->cw = CodeWritter();
}

TEST_F(TestCodeWritter, HandleGetArithmeticAssemblyUnary) {
  /*Case not || neg*/
  string resultNotTemplate = R"(
@0
M=M-1
A=M
M=!M
@0
M=M+1
)";
  ASSERT_STREQ(resultNotTemplate.c_str(),
               this->cw.getArithmeticAssembly("not").c_str());
  string resultNegTemplate = R"(
@0
M=M-1
A=M
M=-M
@0
M=M+1
)";
  ASSERT_STREQ(resultNegTemplate.c_str(),
               this->cw.getArithmeticAssembly("neg").c_str());
}

TEST_F(TestCodeWritter, HandleGetArithmeticAssemblyBinaryNotBool) {
  /*Case not || neg*/
  string resultAddTemplate = R"(
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
M=M+D
@0
M=M+1
)";
  ASSERT_STREQ(resultAddTemplate.c_str(),
               this->cw.getArithmeticAssembly("add").c_str());
  string resultSubTemplate = R"(
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
M=M-D
@0
M=M+1
)";
  ASSERT_STREQ(resultSubTemplate.c_str(),
               this->cw.getArithmeticAssembly("sub").c_str());
  string resultAndTemplate = R"(
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
M=M&D
@0
M=M+1
)";
  ASSERT_STREQ(resultAndTemplate.c_str(),
               this->cw.getArithmeticAssembly("and").c_str());
  string resultOrTemplate = R"(
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
M=M|D
@0
M=M+1
)";
  ASSERT_STREQ(resultOrTemplate.c_str(),
               this->cw.getArithmeticAssembly("or").c_str());
}
TEST_F(TestCodeWritter, HandleGetArithmeticAssemblyBinaryBool) {
  /*Case not || neg*/
  string resultEqTemplate = R"(
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
M=M-D
D=M
@FIRST0
D;JEQ
D=0
@CONTINUE0
0;JMP
(FIRST0)
D=-1
@CONTINUE0
0;JMP
(CONTINUE0)
@0
A=M
M=D
@0
M=M+1
)";
  ASSERT_STREQ(resultEqTemplate.c_str(),
               this->cw.getArithmeticAssembly("eq").c_str());
  string resultGTTemplate = R"(
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
M=M-D
D=M
@FIRST1
D;JGT
D=0
@CONTINUE1
0;JMP
(FIRST1)
D=-1
@CONTINUE1
0;JMP
(CONTINUE1)
@0
A=M
M=D
@0
M=M+1
)";
  ASSERT_STREQ(resultGTTemplate.c_str(),
               this->cw.getArithmeticAssembly("gt").c_str());
  string resultLTTemplate = R"(
@0
M=M-1
A=M
D=M
@0
M=M-1
A=M
M=M-D
D=M
@FIRST2
D;JLT
D=0
@CONTINUE2
0;JMP
(FIRST2)
D=-1
@CONTINUE2
0;JMP
(CONTINUE2)
@0
A=M
M=D
@0
M=M+1
)";
  ASSERT_STREQ(resultLTTemplate.c_str(),
               this->cw.getArithmeticAssembly("lt").c_str());
}
// TEST_F(TestCodeWritter, HandleGetPopAssembly) {}
// TEST_F(TestCodeWritter, HandleGetArithmeticAssembly) {}
// TEST_F(TestCodeWritter, HandleGetWriteLabelTemplate) {}
// TEST_F(TestCodeWritter, HandleGetWriteGotoTemplate) {}
// TEST_F(TestCodeWritter, HandleGetWriteIfTemplate) {}
