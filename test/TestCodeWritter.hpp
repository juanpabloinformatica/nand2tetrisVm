#include "CodeWritter.hpp"

#include <gtest/gtest.h>
using std::cout;
using std::endl;

using testing::Test;

class TestCodeWritter : public Test {

  protected:
    CodeWritter cw;
    void        SetUp() override;
    void        getTemplate();
};
