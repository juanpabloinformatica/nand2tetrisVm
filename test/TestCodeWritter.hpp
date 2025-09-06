#include <gtest/gtest.h>
#include "CodeWritter.hpp"
using std::cout;
using std::endl;

using testing::Test;
class TestCodeWritter : public Test {
  // Sets up the test fixture.

 protected:
	CodeWritter cw;
  void SetUp() override;
  // Tears down the test fixture.
  void getTemplate();
};
