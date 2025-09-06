############################################
################### Test ###################
############################################

test_dir := test
tests := $(shell find ${test_dir} -type f -name "*.cpp")
test_objs := $(patsubst %,${build_dir}/%.out,${tests})
$(info aca --- ${test_objs})
TESTCFLAGS := -g -Wall -Werror
TESTCXX := g++
TESTLDFLAGS := -L /usr/lib/
TESTCFLAGS += -I./include
TESTCFLAGS += -I./test
TESTLDFLAGS += -L ${work_dir}/${build_dir}/${lib_dir}
TESTLDLIBS += -lgtest -lgtest_main -lvm
TESTLDFLAGS += -Wl,--rpath=${work_dir}/${build_dir}/${lib_dir}
test: ${test_objs} library	##		Creating test for each vm translator component
#
#
${build_dir}/${test_dir}/%.cpp.out: ${test_dir}/%.cpp
	mkdir -p ${@D}
	$(TESTCXX) $(TESTCFLAGS)  $< \
		-o $@ $(TESTLDFLAGS) $(TESTLDLIBS)
